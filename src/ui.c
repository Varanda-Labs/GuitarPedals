/***************************************************************
 *
 *                 This code is part of GuitarPedals
 *
 * Copyrights 2022 - Varanda Labs Inc.
 *
 * License:
 *   Creative Commons: CC BY-NC-SA 4.0
 *   Attribution-NonCommercial-ShareAlike 4.0 International
 *   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
 *
 *   Note: for purchasing a commertial license contact:
 *     m@varanda.ca
 *
 ***************************************************************
 */

#include "ui.h"
#include "ui_helpers.h"
#include "lv_style.h"
#include "log.h"

#include "pedal.h"

#define USE_DISPLAY_BACKGROUND
#define DEFAULT_BG_R_COLOR     0x12
#define DEFAULT_BG_G_COLOR     0x45
#define DEFAULT_BG_B_COLOR     0x55

#define DEFAULT_FG_R_COLOR     0x47
#define DEFAULT_FG_G_COLOR     0xdf
#define DEFAULT_FG_B_COLOR     0xff


///////////////////// VARIABLES ////////////////////

bool    lock_screen_swipe = false;
lv_color_t g_default_bg_color;  // global background color
lv_color_t g_default_fg_color;  // global foreground color

lv_obj_t * ui_ScreenBoards;
lv_obj_t * ui_labelPadels;
lv_obj_t * ui_LabelBoard;
lv_obj_t * ui_RightTopPanelContainer;
lv_obj_t * ui_LeftArrowPadels;
lv_obj_t * ui_LeftArrowBoard;
lv_obj_t * ui_RightArrowPedals;
lv_obj_t * ui_RightArrowBoard;
lv_obj_t * ui_BoardCounter;
lv_obj_t * ui_BoardContainer;

pedal_board_t boards[NUM_MAX_BOARDS];
pedal_t available_pedals[NUM_AVAILABLE_PADALS];

lv_obj_t * ui_RightBottomPanelContainer;
lv_obj_t * ui_BtBoardUp;
lv_obj_t * ui_BtBoardDown;
lv_obj_t * ui_BoardIcon;

lv_obj_t * ui_AvailableContainer;
lv_obj_t * ui_AvailableHContainer;

// --- Volume Pedal ---
lv_obj_t * ScreenVolume;
lv_obj_t * VolumeLabel;
lv_obj_t * VolumeSlider;
lv_obj_t * VolumeCloseButton;

extern lv_indev_t * global_indev;

void load_screen_up(lv_obj_t * screen);
void load_screen_down(lv_obj_t * screen);

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
static void OnRightTopPanelContainerScrollBegin(lv_event_t * event)
{
    static int start_y = -1;
    lv_point_t point;
    int e = lv_event_get_code(event);

    switch(e)
    {
    case LV_EVENT_PRESSED:             /**< The object has been pressed*/
        lv_indev_get_vect(global_indev, &point);
        LOG("OnRightTopPanelContainerScrollBegin Pressed %d", point.y);
        start_y = 0;
        break;
    case LV_EVENT_PRESSING:
        lv_indev_get_vect(global_indev, &point);
        start_y += point.y;
        LOG("OnRightTopPanelContainerScrollBegin Position %d", start_y);
        if (lock_screen_swipe) break;
        if (start_y > 5) {
            start_y = 0;
            load_screen_up(ScreenVolume);
            lock_screen_swipe = true;
        }
        if (start_y < -5) {
            start_y = 0;
            load_screen_up(ScreenVolume);
            lock_screen_swipe = true;
        }
        break;
    case LV_EVENT_RELEASED:
        LOG("OnRightTopPanelContainerScrollBegin Released");
        start_y = -1;
        lock_screen_swipe = false;
        break;

    default:
        break;
    }
}

#define Y_OFFSET_ACROSS_BOARDS 89
static int board_idx = 0;

const void * numbers[10] = {
    &ui_img_number_0_png,
    &ui_img_number_1_png,
    &ui_img_number_2_png,
    &ui_img_number_3_png,
    &ui_img_number_4_png,
    &ui_img_number_5_png,
    &ui_img_number_6_png,
    &ui_img_number_7_png,
    &ui_img_number_8_png,
    &ui_img_number_9_png,

};

static void update_board_counter(int pos)
{
    int idx = (pos + Y_OFFSET_ACROSS_BOARDS/2) / Y_OFFSET_ACROSS_BOARDS;
    if (idx >= NUM_MAX_BOARDS - 1) idx = NUM_MAX_BOARDS -1;
    LOG("idx = %d", idx);
    if (idx != board_idx) {
        lv_img_set_src(ui_BoardCounter, numbers[idx + 1]);
        board_idx = idx;
    }
}
static void OnRightBottomPanelContainerScrollBegin(lv_event_t * event)
{
    static int start_y = -1;
    lv_point_t point;
    int e = lv_event_get_code(event);

    switch(e)
    {
    case LV_EVENT_PRESSED:             /**< The object has been pressed*/
        lv_indev_get_vect(global_indev, &point);
        LOG("OnRightBottomPanelContainerScrollBegin Pressed %d", point.y);
        break;
    case LV_EVENT_PRESSING:
        lv_indev_get_vect(global_indev, &point);
        start_y -= point.y;
        int pos= lv_obj_get_scroll_top(ui_BoardContainer);
        LOG("OnRightBottomPanelContainerScrollBegin Position %d, pos %d", start_y, pos);
        lv_obj_scroll_to_y(ui_BoardContainer, start_y, LV_ANIM_OFF);
        update_board_counter(pos);

        break;
    case LV_EVENT_RELEASED:
        lv_obj_update_snap(ui_BoardContainer, LV_ANIM_ON);
        start_y = lv_obj_get_scroll_top(ui_BoardContainer);
        LOG("OnRightBottomPanelContainerScrollBegin Released, pos = %d", start_y);
        update_board_counter(start_y);
        break;

    default:
        break;
    }
}

static void init_available_pedals(void)
{
    int i;

    ui_AvailableHContainer = lv_obj_create(ui_AvailableContainer);

    lv_obj_set_width(ui_AvailableHContainer, 345);
    lv_obj_set_height(ui_AvailableHContainer, 89);

    lv_obj_set_x(ui_AvailableHContainer, 18);
    lv_obj_set_y(ui_AvailableHContainer, 0);

    lv_obj_set_align(ui_AvailableHContainer, LV_ALIGN_LEFT_MID);

    lv_obj_set_scrollbar_mode(ui_AvailableHContainer, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui_AvailableHContainer, LV_DIR_HOR);

    lv_obj_set_style_bg_color(ui_AvailableHContainer, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_AvailableHContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_AvailableHContainer, lv_color_hex(0x003460), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_AvailableHContainer, 70, LV_PART_MAIN | LV_STATE_DEFAULT);

    pedal_init_available_compressor(&available_pedals[0]);
    pedal_init_available_distortion(&available_pedals[1]);
    pedal_init_available_echo(&available_pedals[2]);
    pedal_init_available_volume(&available_pedals[3]);
    pedal_init_available_fuzz(&available_pedals[4]);

    for (i=0; i < NUM_AVAILABLE_PADALS; i++)
    {
        pedal_t * p = &available_pedals[i];
        p->widget = lv_img_create(ui_AvailableHContainer);
        lv_img_set_src(p->widget, p->normal_img);

        lv_obj_set_width(p->widget, LV_SIZE_CONTENT);
        lv_obj_set_height(p->widget, LV_SIZE_CONTENT);

        lv_obj_set_x(p->widget, (i * X_OFFSET_PEDAL) + X_OFFSET_FIRST_PEDAL);
        lv_obj_set_y(p->widget, 0);

        lv_obj_set_align(p->widget, LV_ALIGN_LEFT_MID);

        lv_obj_add_flag(p->widget, LV_OBJ_FLAG_ADV_HITTEST);
        lv_obj_clear_flag(p->widget, LV_OBJ_FLAG_SCROLLABLE);
    }
}

///////////////////// SCREENS ////////////////////
void ui_ScreenBoards_screen_init(void)
{

    // ui_ScreenBoards

    ui_ScreenBoards = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_ScreenBoards, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_ScreenBoards, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenBoards, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_labelPadels

    ui_labelPadels = lv_img_create(ui_ScreenBoards);
    lv_img_set_src(ui_labelPadels, &ui_img_padels_label_png);

    lv_obj_set_width(ui_labelPadels, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_labelPadels, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_labelPadels, 108);
    lv_obj_set_y(ui_labelPadels, 10);

    lv_obj_add_flag(ui_labelPadels, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_labelPadels, LV_OBJ_FLAG_SCROLLABLE);

    // ui_LabelBoard

    ui_LabelBoard = lv_img_create(ui_ScreenBoards);
    lv_img_set_src(ui_LabelBoard, &ui_img_board_label_png);

    lv_obj_set_width(ui_LabelBoard, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelBoard, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelBoard, 129);
    lv_obj_set_y(ui_LabelBoard, 144);

    lv_obj_add_flag(ui_LabelBoard, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_LabelBoard, LV_OBJ_FLAG_SCROLLABLE);

    // ui_RightTopPanelContainer

    ui_RightTopPanelContainer = lv_obj_create(ui_ScreenBoards);

    lv_obj_set_width(ui_RightTopPanelContainer, 51);
    lv_obj_set_height(ui_RightTopPanelContainer, 116);

    lv_obj_set_x(ui_RightTopPanelContainer, 425);
    lv_obj_set_y(ui_RightTopPanelContainer, 19);

    //lv_obj_clear_flag(ui_RightTopPanelContainer, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui_RightTopPanelContainer, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_RightTopPanelContainer, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_bg_opa(ui_RightTopPanelContainer, 64, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RightTopPanelContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_border_color(ui_RightTopPanelContainer, lv_color_hex(0x003460), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_border_opa(ui_RightTopPanelContainer, 70, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_RightTopPanelContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_RightTopPanelContainer, OnRightTopPanelContainerScrollBegin, LV_EVENT_ALL, NULL);   /*Assign an event callback*/



    // ui_LeftArrowPadels

    ui_LeftArrowPadels = lv_img_create(ui_ScreenBoards);
    lv_img_set_src(ui_LeftArrowPadels, &ui_img_left_arrow_png);

    lv_obj_set_width(ui_LeftArrowPadels, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LeftArrowPadels, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LeftArrowPadels, 11);
    lv_obj_set_y(ui_LeftArrowPadels, 43);

    lv_obj_add_flag(ui_LeftArrowPadels, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_LeftArrowPadels, LV_OBJ_FLAG_SCROLLABLE);

    // ui_LeftArrowBoard

    ui_LeftArrowBoard = lv_img_create(ui_ScreenBoards);
    lv_img_set_src(ui_LeftArrowBoard, &ui_img_left_arrow_png);

    lv_obj_set_width(ui_LeftArrowBoard, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LeftArrowBoard, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LeftArrowBoard, 13);
    lv_obj_set_y(ui_LeftArrowBoard, 177);

    lv_obj_add_flag(ui_LeftArrowBoard, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_LeftArrowBoard, LV_OBJ_FLAG_SCROLLABLE);

    // ui_RightArrowPedals

    ui_RightArrowPedals = lv_img_create(ui_ScreenBoards);
    lv_img_set_src(ui_RightArrowPedals, &ui_img_right_arrow_png);

    lv_obj_set_width(ui_RightArrowPedals, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_RightArrowPedals, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_RightArrowPedals, 394);
    lv_obj_set_y(ui_RightArrowPedals, 43);

    lv_obj_add_flag(ui_RightArrowPedals, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_RightArrowPedals, LV_OBJ_FLAG_SCROLLABLE);

    // ui_RightArrowBoard

    ui_RightArrowBoard = lv_img_create(ui_ScreenBoards);
    lv_img_set_src(ui_RightArrowBoard, &ui_img_right_arrow_png);

    lv_obj_set_width(ui_RightArrowBoard, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_RightArrowBoard, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_RightArrowBoard, 394);
    lv_obj_set_y(ui_RightArrowBoard, 177);

    lv_obj_add_flag(ui_RightArrowBoard, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_RightArrowBoard, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardCounter

    ui_BoardCounter = lv_img_create(ui_ScreenBoards);
    lv_img_set_src(ui_BoardCounter, &ui_img_number_1_png);

    lv_obj_set_width(ui_BoardCounter, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardCounter, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardCounter, 58);
    lv_obj_set_y(ui_BoardCounter, 17);

    lv_obj_set_align(ui_BoardCounter, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_BoardCounter, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardCounter, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardContainer

    ui_BoardContainer = lv_obj_create(ui_ScreenBoards);

    lv_obj_set_width(ui_BoardContainer, 414);
    lv_obj_set_height(ui_BoardContainer, 89);

    lv_obj_set_x(ui_BoardContainer, 6);
    lv_obj_set_y(ui_BoardContainer, 167);

    lv_obj_clear_flag(ui_BoardContainer, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(ui_BoardContainer, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui_BoardContainer, LV_DIR_VER);

    lv_obj_set_style_bg_color(ui_BoardContainer, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BoardContainer, 64, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BoardContainer, lv_color_hex(0x003460), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BoardContainer, 70, LV_PART_MAIN | LV_STATE_DEFAULT);

    // MV:
    lv_obj_set_scroll_snap_y(ui_BoardContainer, LV_SCROLL_SNAP_CENTER);

    // ui_BoardPedalIndex13

    int i, p_idx;
    for (i = 0; i < NUM_MAX_BOARDS; i++) {
        pedal_board_t * board = &boards[i];
        board->ui_BoardHContainer =  lv_obj_create(ui_BoardContainer);
        lv_obj_set_width(board->ui_BoardHContainer, 345);
        lv_obj_set_height(board->ui_BoardHContainer, 89);

        lv_obj_set_x(board->ui_BoardHContainer, 18);
        lv_obj_set_y(board->ui_BoardHContainer, i * Y_OFFSET_BOARD_ROWS);

        lv_obj_set_align(board->ui_BoardHContainer, LV_ALIGN_LEFT_MID);

        lv_obj_set_scrollbar_mode(board->ui_BoardHContainer, LV_SCROLLBAR_MODE_OFF);
        lv_obj_set_scroll_dir(board->ui_BoardHContainer, LV_DIR_HOR);

        lv_obj_set_style_bg_color(board->ui_BoardHContainer, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(board->ui_BoardHContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(board->ui_BoardHContainer, lv_color_hex(0x003460), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(board->ui_BoardHContainer, 70, LV_PART_MAIN | LV_STATE_DEFAULT);

        for (p_idx = 0; p_idx < BOARD_MAX_NUM_PEDALS; p_idx++) {
            pedal_t * pedal = &board->pedals[p_idx];

            pedal->normal_img = &ui_img_pedal_empty_png;
            pedal->widget = lv_img_create(board->ui_BoardHContainer);
            lv_img_set_src(pedal->widget, pedal->normal_img);

            lv_obj_set_width(pedal->widget, LV_SIZE_CONTENT);
            lv_obj_set_height(pedal->widget, LV_SIZE_CONTENT);

            lv_obj_set_x(pedal->widget, (p_idx * X_OFFSET_PEDAL) + X_OFFSET_FIRST_PEDAL);
            lv_obj_set_y(pedal->widget, 0);

            lv_obj_set_align(pedal->widget, LV_ALIGN_LEFT_MID);

            lv_obj_add_flag(pedal->widget, LV_OBJ_FLAG_ADV_HITTEST);
            lv_obj_clear_flag(pedal->widget, LV_OBJ_FLAG_SCROLLABLE);
        }
    }

    // ui_ScreenIcon


    // ui_RightBottomPanelContainer

    ui_RightBottomPanelContainer = lv_obj_create(ui_ScreenBoards);

    lv_obj_set_width(ui_RightBottomPanelContainer, 51);
    lv_obj_set_height(ui_RightBottomPanelContainer, 116);

    lv_obj_set_x(ui_RightBottomPanelContainer, 425);
    lv_obj_set_y(ui_RightBottomPanelContainer, 150);

    lv_obj_clear_flag(ui_RightBottomPanelContainer, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_RightBottomPanelContainer, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RightBottomPanelContainer, 64, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_RightBottomPanelContainer, lv_color_hex(0x003460), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_RightBottomPanelContainer, 70, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_RightBottomPanelContainer, OnRightBottomPanelContainerScrollBegin, LV_EVENT_ALL, NULL);   /*Assign an event callback*/

    // ui_BtBoardUp

//    ui_BtBoardUp = lv_btn_create(ui_ScreenBoards);
    ui_BtBoardUp = lv_img_create(ui_ScreenBoards);
    lv_obj_set_width(ui_BtBoardUp, 44);
    lv_obj_set_height(ui_BtBoardUp, 50);

    lv_obj_set_x(ui_BtBoardUp, 210);
    lv_obj_set_y(ui_BtBoardUp, 32);

    lv_obj_set_align(ui_BtBoardUp, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_BtBoardUp, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_BtBoardUp, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_BtBoardUp, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BtBoardUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_BtBoardUp, &ui_img_arrows_up_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BtBoardUp, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BtBoardUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_BtBoardUp, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_BtBoardUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_BtBoardUp, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_BtBoardUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_BtBoardDown

//    ui_BtBoardDown = lv_btn_create(ui_ScreenBoards);
    ui_BtBoardDown = lv_img_create(ui_ScreenBoards);

    lv_obj_set_width(ui_BtBoardDown, 44);
    lv_obj_set_height(ui_BtBoardDown, 50);

    lv_obj_set_x(ui_BtBoardDown, 210);
    lv_obj_set_y(ui_BtBoardDown, 112);

    lv_obj_set_align(ui_BtBoardDown, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_BtBoardDown, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_BtBoardDown, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_BtBoardDown, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BtBoardDown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_BtBoardDown, &ui_img_arrows_down_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BtBoardDown, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BtBoardDown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_BtBoardDown, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_BtBoardDown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_BtBoardDown, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_BtBoardDown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_BoardIcon

    ui_BoardIcon = lv_img_create(ui_ScreenBoards);
    lv_img_set_src(ui_BoardIcon, &ui_img_boards_icon_png);

    lv_obj_set_width(ui_BoardIcon, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardIcon, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardIcon, 210);
    lv_obj_set_y(ui_BoardIcon, 72);

    lv_obj_set_align(ui_BoardIcon, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_BoardIcon, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardIcon, LV_OBJ_FLAG_SCROLLABLE);

    // ui_AvailableContainer

    ui_AvailableContainer = lv_obj_create(ui_ScreenBoards);

    lv_obj_set_width(ui_AvailableContainer, 414);
    lv_obj_set_height(ui_AvailableContainer, 89);

    lv_obj_set_x(ui_AvailableContainer, 6);
    lv_obj_set_y(ui_AvailableContainer, 34);

    lv_obj_clear_flag(ui_AvailableContainer, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_scrollbar_mode(ui_AvailableContainer, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui_AvailableContainer, LV_DIR_VER);

    lv_obj_set_style_bg_color(ui_AvailableContainer, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_AvailableContainer, 64, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_AvailableContainer, lv_color_hex(0x003460), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_AvailableContainer, 70, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_AvailableHContainer
    init_available_pedals();


}

static void ui_event_CloseButton(lv_event_t * e)
{
//    lv_event_code_t event = lv_event_get_code(e);
//    lv_obj_t * ta = lv_event_get_target(e);
    if (e->code == LV_EVENT_CLICKED) {
       load_screen_down(ui_ScreenBoards);
    }
    //
}

//--- to move to volume file:
void ScreenVolume_screen_init(void)
{
    // ScreenVolume

    ScreenVolume = lv_obj_create(NULL);


    lv_obj_clear_flag(ScreenVolume, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ScreenVolume, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ScreenVolume, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // VolumeLabel

    VolumeLabel = lv_label_create(ScreenVolume);

    lv_obj_set_width(VolumeLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(VolumeLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(VolumeLabel, -166);
    lv_obj_set_y(VolumeLabel, -97);

    lv_obj_set_align(VolumeLabel, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(VolumeLabel, g_default_fg_color, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_opa(VolumeLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_label_set_text(VolumeLabel, "Plug-in: Volume\nVersion: 0.0.1\nBy: Varanda Labs");

    // VolumeSlider

    VolumeSlider = lv_slider_create(ScreenVolume);

    static lv_style_t style_main;

    lv_slider_set_range(VolumeSlider, 0, 100);

    lv_obj_set_width(VolumeSlider, 397);
    lv_obj_set_height(VolumeSlider, 10);

    lv_obj_set_x(VolumeSlider, 0);
    lv_obj_set_y(VolumeSlider, 0);

    lv_obj_set_align(VolumeSlider, LV_ALIGN_CENTER);

    // CloseButton
    VolumeCloseButton = lv_btn_create(ScreenVolume);
    static lv_style_t style_btn;
    lv_style_set_bg_color(&style_btn, g_default_bg_color);
    lv_obj_add_style(VolumeCloseButton, &style_btn, 0);

    lv_obj_set_width(VolumeCloseButton, 100);
    lv_obj_set_height(VolumeCloseButton, 50);

    lv_obj_set_x(VolumeCloseButton, 167);
    lv_obj_set_y(VolumeCloseButton, 89);

    lv_obj_set_align(VolumeCloseButton, LV_ALIGN_CENTER);

    lv_obj_add_flag(VolumeCloseButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(VolumeCloseButton, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(VolumeCloseButton, ui_event_CloseButton, LV_EVENT_ALL, NULL);
    lv_obj_t * label = lv_label_create(VolumeCloseButton);
    lv_obj_set_style_text_color(label, g_default_fg_color, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_label_set_text(label, "Return");
    lv_obj_set_align(label, LV_ALIGN_CENTER);
}

void load_screen_up(lv_obj_t * screen)
{
    lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_MOVE_TOP, 500, 0, 0);
}

void load_screen_down(lv_obj_t * screen)
{
    lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 500, 0, 0);
}

bool add_pedal(pedal_type_t type, pedal_board_t * board)
{
    if (board->num_pedals >= BOARD_MAX_NUM_PEDALS) {
        LOG_E("Board is full");
        return false;
    }

    pedal_t* pedal = &board->pedals[board->num_pedals];

    switch(type) {
    case PEDAL_TYPE__COMPRESSOR:
        pedal_init_available_compressor(pedal);
        break;
    case PEDAL_TYPE__VOLUME:
        pedal_init_available_volume(pedal);
        break;
    case PEDAL_TYPE__DISTORTION:
        pedal_init_available_distortion(pedal);
        break;
    case PEDAL_TYPE__ECHO:
        pedal_init_available_echo(pedal);
        break;
    case PEDAL_TYPE__FUZZ:
        pedal_init_available_fuzz(pedal);
        break;
    default:
        LOG_E("unexpected type %d", type);
        return false;
    }
    pedal->pedal_new_context_func_t(pedal);
    lv_img_set_src(pedal->widget, pedal->normal_img);

    board->num_pedals++;

    return true;
}

void ui_init(void)
{
    memset(boards, 0, sizeof(boards));
    memset(available_pedals, 0, sizeof(available_pedals));

    g_default_bg_color = lv_color_make(DEFAULT_BG_R_COLOR, DEFAULT_BG_G_COLOR, DEFAULT_BG_B_COLOR);
    g_default_fg_color = lv_color_make(DEFAULT_FG_R_COLOR, DEFAULT_FG_G_COLOR, DEFAULT_FG_B_COLOR);

    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_CYAN), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);    
    lv_disp_set_theme(dispp, theme);

    lv_disp_set_bg_image(dispp, &ui_img_disp_background_png);
    lv_disp_set_bg_opa(dispp, 255);

    ui_ScreenBoards_screen_init();
    ScreenVolume_screen_init();

    lv_disp_load_scr(ui_ScreenBoards);

    // init pre-defined boards
    add_pedal(PEDAL_TYPE__DISTORTION, &boards[0]);
    add_pedal(PEDAL_TYPE__VOLUME, &boards[0]);

    // init pre-defined boards
    add_pedal(PEDAL_TYPE__DISTORTION, &boards[1]);
    add_pedal(PEDAL_TYPE__FUZZ, &boards[1]);
    add_pedal(PEDAL_TYPE__ECHO, &boards[1]);
    add_pedal(PEDAL_TYPE__VOLUME, &boards[2]);

    add_pedal(PEDAL_TYPE__DISTORTION, &boards[2]);
    add_pedal(PEDAL_TYPE__ECHO, &boards[2]);
    add_pedal(PEDAL_TYPE__VOLUME, &boards[2]);
}


