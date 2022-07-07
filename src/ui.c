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
#include "generic_props_ctl.h"

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

lv_obj_t * ui_draggerObj;
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
//lv_obj_t * ui_Screen1;
lv_obj_t * ui_diaCheck;
lv_obj_t * ui_DialogPanel;
lv_obj_t * ui_diaProps;
lv_obj_t * ui_diaMoveRight;
lv_obj_t * ui_diaMoveLeft;
lv_obj_t * ui_diaRemove;
lv_obj_t * ui_diaEnable;
lv_obj_t * ui_diaClose;

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

pedal_t * active_pedal = NULL;

extern lv_indev_t * global_indev;

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

void load_screen_up(lv_obj_t * screen);
void load_screen_down(lv_obj_t * screen);
bool insert_pedal(pedal_type_t type, int x);
bool remove_pedal(int idx);
void reset_panels_idx_positions();
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
static void show(lv_obj_t * widget)
{
    lv_obj_clear_flag(widget, LV_OBJ_FLAG_HIDDEN);
}

static void hide(lv_obj_t * widget)
{
    lv_obj_add_flag(widget, LV_OBJ_FLAG_HIDDEN);
}

static void dialog_show()
{
    lv_obj_clear_flag(ui_DialogPanel, LV_OBJ_FLAG_HIDDEN);
}

static void dialog_hide()
{
    lv_obj_add_flag(ui_DialogPanel, LV_OBJ_FLAG_HIDDEN);
}

#define PRESSED_COLOR 0x72C250
#define RELEASED_COLOR 0x47DFFF
#define DRAG_BAD_AREA_COLOR 0xff0000
#define DRAG_GOOD_AREA_COLOR 0x00ff00

enum {
    DIA_BT__PROPS,
    DIA_BT__MOVE_RIGHT,
    DIA_BT__MOVE_LEFT,
    DIA_BT__REMOVE,
    DIA_BT__ENABLE,
    DIA_BT__CLOSE,
};

static void actionDiaProps(void)
{
    LOG("actionDiaProps");
    set_generic_props_ctl(&active_pedal->props.volume->generic_props);
    load_screen_up(ui_genericPropScreen);
}

static void actionDiaMoveRight(void)
{
    LOG("actionDiaMoveRight");
}

static void actionDiaMoveLeft(void)
{
    LOG("actionDiaMoveLeft");
}

static void actionDiaRemove(void)
{
    LOG("OnDiaRemove");
    if ( ! active_pedal) {
        LOG_E("no active pedal");
        return;
    }
    remove_pedal(active_pedal->pos_idx);
}

static void actionDiaEnable(void)
{
    LOG("OnDiaEnable");
}

static void actionDiaClose(void)
{
    LOG("OnDiaClose");
    active_pedal = NULL;
    dialog_hide();
}

static void OnDiaEvent(lv_event_t * event)
{

    switch(event->code) {

    case LV_EVENT_PRESSED:
        lv_obj_set_style_img_recolor_opa(event->target, 255, 0);
        lv_obj_set_style_img_recolor(event->target, lv_color_hex(PRESSED_COLOR), 0);
        break;

    case LV_EVENT_RELEASED:
        lv_obj_set_style_img_recolor_opa(event->target, 0, 0);
        lv_obj_set_style_img_recolor(event->target, lv_color_hex(PRESSED_COLOR), 0);
        LOG("OnDiaProps: Released");

        switch((int) event->user_data) {
        case DIA_BT__PROPS:         actionDiaProps();       break;
        case DIA_BT__MOVE_RIGHT:    actionDiaMoveRight();   break;
        case DIA_BT__MOVE_LEFT:     actionDiaMoveLeft();    break;
        case DIA_BT__REMOVE:        actionDiaRemove();      break;
        case DIA_BT__ENABLE:        actionDiaEnable();      break;
        case DIA_BT__CLOSE:         actionDiaClose();       break;
        default:
            LOG_E("Unexpected dialog button %d", (int) event->user_data);
            break;
        }
        active_pedal = NULL;
        dialog_hide();
        break;

    default: break;
    }
}

#define AVAILABLE_CONTAINER_X_OFFSET 18
#define AVAILABLE_CONTAINER_Y_OFFSET 34
#define PEDAL_WIDTH

#define GOOD_DRAG_AREA_Y    100

#define DRAG_POS_X_OFFSET (AVAILABLE_CONTAINER_X_OFFSET + 41) // 41 is pedal image 82/2
#define DRAG_POS_Y_OFFSET (AVAILABLE_CONTAINER_Y_OFFSET + 41 - 22)

static void OnAvailablePanelEvent(lv_event_t * event)
{
    static bool dragging = false;
    static lv_point_t acc_point = {0,0};
    static bool in_good_area = false;
    lv_point_t current_point;
    pedal_t * pedal =  (pedal_t *) event->user_data;

    switch(event->code) {
    case LV_EVENT_LONG_PRESSED:
        LOG("OnAvailablePanelEvent: Pressed long");
        lv_obj_set_style_img_recolor_opa(event->target, 64, 0);
        lv_obj_set_style_img_recolor(event->target, lv_color_hex(PRESSED_COLOR), 0);

        dragging = true;
        lv_indev_get_vect(global_indev, &acc_point);
        lv_obj_clear_flag(ui_AvailableHContainer, LV_OBJ_FLAG_SCROLLABLE);

        lv_img_set_src(ui_draggerObj, pedal->normal_img);
        lv_obj_set_style_img_recolor_opa(ui_draggerObj, 128, 0);
        lv_obj_set_style_img_recolor(ui_draggerObj, lv_color_hex(DRAG_BAD_AREA_COLOR), 0);
        in_good_area = false;
        show(ui_draggerObj);
        break;

    case LV_EVENT_PRESSING:
        if (dragging) {
            lv_indev_get_vect(global_indev, &current_point);
            acc_point.x += current_point.x;
            acc_point.y += current_point.y;
            lv_obj_set_x(ui_draggerObj, acc_point.x + lv_obj_get_x(event->target) + DRAG_POS_X_OFFSET);
            lv_obj_set_y(ui_draggerObj, acc_point.y + lv_obj_get_y(event->target) + DRAG_POS_Y_OFFSET);

            if (acc_point.y > GOOD_DRAG_AREA_Y && boards[board_idx].num_pedals < BOARD_MAX_NUM_PEDALS) {
                if (! in_good_area) {
                    in_good_area = true;
                    lv_obj_set_style_img_recolor(ui_draggerObj, lv_color_hex(DRAG_GOOD_AREA_COLOR), 0);
                }
            } else {
                if (in_good_area) {
                    in_good_area = false;
                    lv_obj_set_style_img_recolor(ui_draggerObj, lv_color_hex(DRAG_BAD_AREA_COLOR), 0);
                }
            }

        }

        break;

    case LV_EVENT_RELEASED:
        LOG("Pressed pedal type: %d, props: %p", pedal->type, pedal->props.compressor);
        lv_obj_set_style_img_recolor_opa(event->target, 0, 0);
        hide(ui_draggerObj);
        lv_obj_add_flag(ui_AvailableHContainer, LV_OBJ_FLAG_SCROLLABLE);

        if (in_good_area) {
            insert_pedal(pedal->type, lv_obj_get_x(ui_draggerObj));
        }

        lv_obj_set_x(ui_draggerObj, -90);
        lv_obj_set_y(ui_draggerObj, -90);

        dragging = false;

        break;

    default: break;
    }
}

static void OnPedalEvent(lv_event_t * event)
{
    pedal_t * pedal =  (pedal_t *) event->user_data;
    static lv_coord_t h_scroll = 0;

    switch(event->code) {
    case LV_EVENT_CLICKED:
        LOG("Clicked pedal type: %d, props: %p", pedal->type, pedal->props.compressor);

//        if (pedal->props.compressor) {
//            active_pedal = pedal;
//            dialog_show();
//        }
        break;

//    case LV_EVENT_LONG_PRESSED:
//        LOG("Long Pressed pedal type: %d, props: %p", pedal->type, pedal->props.compressor);
//        if (pedal->props.compressor) {
//            active_pedal = pedal;
//            dialog_show();
//        }
//        break;

    case LV_EVENT_PRESSED:
        h_scroll = lv_obj_get_scroll_left(boards[board_idx].ui_BoardHContainer);
        lv_obj_set_style_img_recolor_opa(event->target, 64, 0);
        lv_obj_set_style_img_recolor(event->target, lv_color_hex(PRESSED_COLOR), 0);
        h_scroll = lv_obj_get_scroll_left(boards[board_idx].ui_BoardHContainer);
        lv_obj_set_style_img_recolor(pedal->widget, lv_color_hex(PRESSED_COLOR), 0);
        break;

    case LV_EVENT_RELEASED:
        h_scroll = h_scroll - lv_obj_get_scroll_left(boards[board_idx].ui_BoardHContainer);
        if (h_scroll < 0) h_scroll = -h_scroll;

        if (h_scroll > 5) {
            LOG("ignore click as we had H scroll");
            lv_obj_set_style_img_recolor_opa(event->target, 0, 0);
            break;
        }

        LOG("Pressed pedal type: %d, props: %p, h_scroll = %d", pedal->type, pedal->props.compressor, h_scroll);
        lv_obj_set_style_img_recolor_opa(event->target, 0, 0);
        if (pedal->props.compressor) {
            active_pedal = pedal;
            dialog_show();
        }
        else {
            LOG("pedal not initialized");
        }
        break;

    default: break;
    }
}

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
        lv_obj_set_style_bg_color(ui_RightBottomPanelContainer, lv_color_hex(PRESSED_COLOR), LV_PART_MAIN | LV_STATE_PRESSED);
        break;

    case LV_EVENT_PRESSING:
        lv_indev_get_vect(global_indev, &point);
        start_y -= point.y;
        int pos= lv_obj_get_scroll_top(ui_BoardContainer);
        lv_obj_scroll_to_y(ui_BoardContainer, start_y, LV_ANIM_OFF);
        LOG("OnRightBottomPanelContainerScrollBegin Position %d, pos %d", start_y, pos);
        update_board_counter(pos);
        break;

    case LV_EVENT_RELEASED:
        lv_obj_update_snap(ui_BoardContainer, LV_ANIM_ON);
        start_y = lv_obj_get_scroll_top(ui_BoardContainer);
        LOG("OnRightBottomPanelContainerScrollBegin Released, pos = %d", start_y);
        update_board_counter(start_y);
        lv_obj_set_style_img_recolor_opa(ui_BoardContainer, 0, 0);
        lv_obj_set_style_bg_color(ui_RightBottomPanelContainer, lv_color_hex(RELEASED_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);

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

    lv_obj_set_x(ui_AvailableHContainer, AVAILABLE_CONTAINER_X_OFFSET);
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

        lv_obj_add_flag(p->widget, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(p->widget, OnAvailablePanelEvent, LV_EVENT_ALL, p);
    }

    // init ui_draggerObj
    ui_draggerObj = lv_img_create(ui_ScreenBoards);
    lv_img_set_src(ui_draggerObj, &ui_img_pedal_empty_png);

    lv_obj_set_width(ui_draggerObj, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_draggerObj, LV_SIZE_CONTENT);


    lv_obj_set_x(ui_draggerObj, -90);
    lv_obj_set_y(ui_draggerObj, -90);

    lv_obj_set_align(ui_draggerObj, LV_ALIGN_OUT_LEFT_TOP);

    lv_obj_add_flag(ui_draggerObj, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_draggerObj, LV_OBJ_FLAG_SCROLLABLE);
    hide(ui_draggerObj);
}

///////////////////// SCREENS ////////////////////
void init_ScreenBoards(void)
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

    lv_obj_set_style_bg_opa(ui_RightTopPanelContainer, 64, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui_RightTopPanelContainer, lv_color_hex(PRESSED_COLOR), LV_PART_MAIN | LV_STATE_PRESSED);

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
            pedal->pos_idx = p_idx;

            lv_obj_set_width(pedal->widget, LV_SIZE_CONTENT);
            lv_obj_set_height(pedal->widget, LV_SIZE_CONTENT);

            lv_obj_set_x(pedal->widget, (p_idx * X_OFFSET_PEDAL) + X_OFFSET_FIRST_PEDAL);
            lv_obj_set_y(pedal->widget, 0);

            lv_obj_set_align(pedal->widget, LV_ALIGN_LEFT_MID);

            lv_obj_add_flag(pedal->widget, LV_OBJ_FLAG_ADV_HITTEST);
            lv_obj_clear_flag(pedal->widget, LV_OBJ_FLAG_SCROLLABLE);

            //lv_obj_set_click(pedal->widget, true);
            lv_obj_add_flag(pedal->widget, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_add_event_cb(pedal->widget, OnPedalEvent, LV_EVENT_ALL, pedal);   /*Assign an event callback*/
            //lv_obj_add_event_cb(pedal->widget, OnPedalLongClicked, LV_EVENT_LONG_PRESSED, (void *) p_idx);   /*Assign an event callback*/



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
    lv_obj_set_y(ui_AvailableContainer, AVAILABLE_CONTAINER_Y_OFFSET);

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
    reset_panels_idx_positions();
    return true;
}

#define PEDAL_OFFSET_IN_BOARD -10

void shift_pedals_right(int idx)
{
    pedal_board_t * board = &boards[board_idx];
    int move_to = board->num_pedals;
    int move_from = move_to - 1;
    lv_obj_t * save_widget;
    int save_pos_idx;

    while(move_to > idx) {
        LOG("pedals[%d] = pedals[%d]", move_to, move_from);
        save_widget = board->pedals[move_to].widget;
        save_pos_idx = board->pedals[move_to].pos_idx;
        memcpy(&board->pedals[move_to], &board->pedals[move_from], sizeof(pedal_t));
        board->pedals[move_to].widget = save_widget;
        board->pedals[move_to].pos_idx = save_pos_idx;
        lv_img_set_src(board->pedals[move_to].widget, board->pedals[move_to].normal_img);
        move_to--;
        move_from--;
    }
    board->num_pedals++;
}

void reset_panels_idx_positions()
{
    pedal_board_t * board = &boards[board_idx];
    for (int i = 0; i<BOARD_MAX_NUM_PEDALS; i++)
        board->pedals[i].pos_idx = i;
}

bool remove_pedal(int idx)
{
    LOG("remove_pedal idx: %d", idx);
    pedal_board_t * board = &boards[board_idx];
    if (idx >= board->num_pedals) {
        LOG_E("pedal not found");
        return false;
    }
    if (board->pedals[idx].pedal_delete_context_func_t) {
        board->pedals[idx].pedal_delete_context_func_t(&board->pedals[idx]);
    }

    // if need to shift left
    if (idx < board->num_pedals - 1) {
        int move_from = idx + 1;
        int move_to = idx;
        lv_obj_t * save_widget;
        int save_pos_idx;
        while(move_to < board->num_pedals - 1) {
            LOG("pedals[%d] = pedals[%d]", move_to, move_from);
            save_widget = board->pedals[move_to].widget;
            save_pos_idx = board->pedals[move_to].pos_idx;
            memcpy(&board->pedals[move_to], &board->pedals[move_from], sizeof(pedal_t));
            board->pedals[move_to].widget = save_widget;
            board->pedals[move_to].pos_idx = save_pos_idx;
            lv_img_set_src(board->pedals[move_to].widget, board->pedals[move_to].normal_img);
            move_to++;
            move_from++;
        }
        LOG("Wipe pedal %d", board->num_pedals-1);
        board->pedals[board->num_pedals-1].props.compressor = 0;
        //board->pedals[board->num_pedals-1].
        lv_img_set_src(board->pedals[board->num_pedals-1].widget, &ui_img_pedal_empty_png);
        board->pedals[board->num_pedals-1].normal_img = &ui_img_pedal_empty_png;
    }
    else {
        lv_img_set_src(board->pedals[idx].widget, &ui_img_pedal_empty_png);
        board->pedals[idx].normal_img = &ui_img_pedal_empty_png;
    }
    board->num_pedals--;
    LOG("num_pedals = %d", board->num_pedals);
    reset_panels_idx_positions();
    return true;
}

bool insert_pedal(pedal_type_t type, int x)
{
    pedal_board_t * board = &boards[board_idx];
    if (board->num_pedals >= BOARD_MAX_NUM_PEDALS) {
        LOG_E("Board is full");
        return false;
    }

    int idx = (x - PEDAL_OFFSET_IN_BOARD + lv_obj_get_scroll_left(boards[board_idx].ui_BoardHContainer)) / 82; // 82 is pedal width
    if (idx >= BOARD_MAX_NUM_PEDALS) idx = BOARD_MAX_NUM_PEDALS - 1;
    LOG("insert_pedal x = %d, idx = %d", x, idx);

    if (idx < board->num_pedals) {
        LOG("shift pedals right");
        shift_pedals_right(idx);
    }
    else {
        idx = board->num_pedals;
    }

    pedal_t* pedal = &board->pedals[idx];

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
    reset_panels_idx_positions();
    return true;
}
void ui_Dialog_init(void)
{
    // ui_DialogPanel

    ui_DialogPanel = lv_obj_create(ui_ScreenBoards);

    lv_obj_set_width(ui_DialogPanel, 192);
    lv_obj_set_height(ui_DialogPanel, 269);

    lv_obj_set_x(ui_DialogPanel, 0);
    lv_obj_set_y(ui_DialogPanel, 0);

    lv_obj_set_align(ui_DialogPanel, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_DialogPanel, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_DialogPanel, lv_color_hex(0x001622), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DialogPanel, 240, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_diaProps

    ui_diaProps = lv_img_create(ui_DialogPanel);
    lv_img_set_src(ui_diaProps, &ui_img_sel_props_png);

    lv_obj_set_width(ui_diaProps, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_diaProps, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_diaProps, -2);
    lv_obj_set_y(ui_diaProps, -113);

    lv_obj_set_align(ui_diaProps, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_diaProps, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_diaProps, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui_diaProps, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui_diaProps, OnDiaEvent, LV_EVENT_ALL, (void *) DIA_BT__PROPS);


    // ui_diaMoveRight

    ui_diaMoveRight = lv_img_create(ui_DialogPanel);
    lv_img_set_src(ui_diaMoveRight, &ui_img_sel_move_right_png);

    lv_obj_set_width(ui_diaMoveRight, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_diaMoveRight, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_diaMoveRight, 6);
    lv_obj_set_y(ui_diaMoveRight, -68);

    lv_obj_set_align(ui_diaMoveRight, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_diaMoveRight, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_diaMoveRight, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui_diaMoveRight, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_add_event_cb(ui_diaMoveRight, OnDiaEvent, LV_EVENT_ALL, (void *) DIA_BT__MOVE_RIGHT);

    // ui_diaMoveLeft

    ui_diaMoveLeft = lv_img_create(ui_DialogPanel);
    lv_img_set_src(ui_diaMoveLeft, &ui_img_sel_move_left_png);

    lv_obj_set_width(ui_diaMoveLeft, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_diaMoveLeft, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_diaMoveLeft, -2);
    lv_obj_set_y(ui_diaMoveLeft, -21);

    lv_obj_set_align(ui_diaMoveLeft, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_diaMoveLeft, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_diaMoveLeft, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui_diaMoveLeft, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui_diaMoveLeft, OnDiaEvent, LV_EVENT_ALL, (void *) DIA_BT__MOVE_LEFT);

    // ui_diaRemove

    ui_diaRemove = lv_img_create(ui_DialogPanel);
    lv_img_set_src(ui_diaRemove, &ui_img_sel_remove_png);

    lv_obj_set_width(ui_diaRemove, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_diaRemove, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_diaRemove, -3);
    lv_obj_set_y(ui_diaRemove, 22);

    lv_obj_set_align(ui_diaRemove, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_diaRemove, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_diaRemove, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui_diaRemove, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_add_event_cb(ui_diaRemove, OnDiaEvent, LV_EVENT_ALL, (void *) DIA_BT__REMOVE);


    // ui_diaEnable

    ui_diaEnable = lv_img_create(ui_DialogPanel);
    lv_img_set_src(ui_diaEnable, &ui_img_sel_enable_png);

    lv_obj_set_width(ui_diaEnable, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_diaEnable, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_diaEnable, -7);
    lv_obj_set_y(ui_diaEnable, 68);

    lv_obj_set_align(ui_diaEnable, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_diaEnable, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_diaEnable, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui_diaEnable, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_add_event_cb(ui_diaEnable, OnDiaEvent, LV_EVENT_ALL, (void *) DIA_BT__ENABLE);


    // ui_diaClose

    ui_diaClose = lv_img_create(ui_DialogPanel);
    lv_img_set_src(ui_diaClose, &ui_img_sel_close_png);

    lv_obj_set_width(ui_diaClose, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_diaClose, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_diaClose, -5);
    lv_obj_set_y(ui_diaClose, 112);

    lv_obj_set_align(ui_diaClose, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_diaClose, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_diaClose, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui_diaClose, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_add_event_cb(ui_diaClose, OnDiaEvent, LV_EVENT_ALL, (void *) DIA_BT__CLOSE);

    // ui_diaCheck

    ui_diaCheck = lv_img_create(ui_DialogPanel);
    lv_img_set_src(ui_diaCheck, &ui_img_sel_check_png);

    lv_obj_set_width(ui_diaCheck, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_diaCheck, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_diaCheck, -45);
    lv_obj_set_y(ui_diaCheck, 69);

    lv_obj_set_align(ui_diaCheck, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_diaCheck, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_diaCheck, LV_OBJ_FLAG_SCROLLABLE);

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

    init_ScreenBoards();
    ScreenVolume_screen_init();
    ui_genericPropScreen_screen_init();

    lv_disp_load_scr(ui_ScreenBoards);

    // init pre-defined boards
    add_pedal(PEDAL_TYPE__DISTORTION, &boards[0]);
    add_pedal(PEDAL_TYPE__VOLUME, &boards[0]);

    // init pre-defined boards
    add_pedal(PEDAL_TYPE__DISTORTION, &boards[1]);
    add_pedal(PEDAL_TYPE__FUZZ, &boards[1]);
    add_pedal(PEDAL_TYPE__ECHO, &boards[1]);
    add_pedal(PEDAL_TYPE__COMPRESSOR, &boards[1]);
    add_pedal(PEDAL_TYPE__ECHO, &boards[1]);
    add_pedal(PEDAL_TYPE__VOLUME, &boards[1]);

    add_pedal(PEDAL_TYPE__DISTORTION, &boards[2]);
    add_pedal(PEDAL_TYPE__ECHO, &boards[2]);
    add_pedal(PEDAL_TYPE__VOLUME, &boards[2]);

    // just test
    ui_Dialog_init();
    dialog_hide();
}


