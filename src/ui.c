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

///////////////////// VARIABLES ////////////////////
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
lv_obj_t * ui_BoardHContainer00;
lv_obj_t * ui_BoardPedalIndex0000;
lv_obj_t * ui_BoardPedalIndex0001;
lv_obj_t * ui_BoardPedalIndex0002;
lv_obj_t * ui_BoardPedalIndex0003;
lv_obj_t * ui_BoardPedalIndex0004;
lv_obj_t * ui_BoardPedalIndex0005;
lv_obj_t * ui_BoardHContainer01;
lv_obj_t * ui_BoardPedalIndex2;
lv_obj_t * ui_BoardPedalIndex3;
lv_obj_t * ui_BoardHContainer02;
lv_obj_t * ui_BoardPedalIndex13;
lv_obj_t * ui_BoardPedalIndex14;
lv_obj_t * ui_BoardPedalIndex15;
lv_obj_t * ui_BoardPedalIndex16;
lv_obj_t * ui_BoardPedalIndex17;
lv_obj_t * ui_BoardPedalIndex18;
lv_obj_t * ui_ScreenIcon;
lv_obj_t * ui_BtScreenUp;
lv_obj_t * ui_BtScreenDown;
lv_obj_t * ui_RightBottomPanelContainer;
lv_obj_t * ui_BtBoardUp;
lv_obj_t * ui_BtBoardDown;
lv_obj_t * ui_BoardIcon;

lv_obj_t * ui_AvailableContainer;
lv_obj_t * ui_BoardHContainer1;
lv_obj_t * ui_BoardPedalIndex10;
lv_obj_t * ui_BoardPedalIndex11;
lv_obj_t * ui_BoardPedalIndex12;
lv_obj_t * ui_BoardPedalIndex7;
lv_obj_t * ui_BoardPedalIndex8;
lv_obj_t * ui_BoardPedalIndex9;



extern lv_indev_t * global_indev;

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
        break;
    case LV_EVENT_RELEASED:
        LOG("OnRightTopPanelContainerScrollBegin Released");
        start_y = -1;
        break;

    default:
        break;
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
    lv_obj_set_style_bg_img_src(ui_ScreenBoards, &ui_img_guitar_background_01_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_ScreenBoards, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_ScreenBoards, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_ScreenBoards, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_ScreenBoards, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_blend_mode(ui_ScreenBoards, LV_BLEND_MODE_NORMAL, LV_PART_MAIN | LV_STATE_DEFAULT);

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
    lv_obj_set_style_bg_opa(ui_RightTopPanelContainer, 64, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_RightTopPanelContainer, lv_color_hex(0x003460), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_RightTopPanelContainer, 70, LV_PART_MAIN | LV_STATE_DEFAULT);

    //lv_obj_add_event_cb(ui_RightTopPanelContainer, OnRightTopPanelContainerScrollBegin, LV_EVENT_SCROLL_BEGIN, NULL);   /*Assign an event callback*/
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

    lv_obj_set_scrollbar_mode(ui_BoardContainer, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui_BoardContainer, LV_DIR_VER);

    lv_obj_set_style_bg_color(ui_BoardContainer, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BoardContainer, 64, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BoardContainer, lv_color_hex(0x003460), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BoardContainer, 70, LV_PART_MAIN | LV_STATE_DEFAULT);

    // MV:
    lv_obj_set_scroll_snap_y(ui_BoardContainer, LV_SCROLL_SNAP_CENTER);

    // ui_BoardPedalIndex13

    // ui_BoardHContainer00

    ui_BoardHContainer00 = lv_obj_create(ui_BoardContainer);

    lv_obj_set_width(ui_BoardHContainer00, 345);
    lv_obj_set_height(ui_BoardHContainer00, 89);

    lv_obj_set_x(ui_BoardHContainer00, 18);
    lv_obj_set_y(ui_BoardHContainer00, 0);

    lv_obj_set_align(ui_BoardHContainer00, LV_ALIGN_LEFT_MID);

    lv_obj_set_scrollbar_mode(ui_BoardHContainer00, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui_BoardHContainer00, LV_DIR_HOR);

    lv_obj_set_style_bg_color(ui_BoardHContainer00, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BoardHContainer00, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BoardHContainer00, lv_color_hex(0x003460), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BoardHContainer00, 70, LV_PART_MAIN | LV_STATE_DEFAULT);

    // MV:
    lv_obj_set_scroll_snap_x(ui_BoardHContainer00, LV_SCROLL_SNAP_NONE);

    // ui_BoardPedalIndex0000

    ui_BoardPedalIndex0000 = lv_img_create(ui_BoardHContainer00);
    lv_img_set_src(ui_BoardPedalIndex0000, &ui_img_pedal_echo_png);

    lv_obj_set_width(ui_BoardPedalIndex0000, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex0000, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex0000, -18);
    lv_obj_set_y(ui_BoardPedalIndex0000, 0);

    lv_obj_set_align(ui_BoardPedalIndex0000, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex0000, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex0000, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex0001

    ui_BoardPedalIndex0001 = lv_img_create(ui_BoardHContainer00);
    lv_img_set_src(ui_BoardPedalIndex0001, &ui_img_pedal_dist_png);

    lv_obj_set_width(ui_BoardPedalIndex0001, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex0001, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex0001, 69);
    lv_obj_set_y(ui_BoardPedalIndex0001, 0);

    lv_obj_set_align(ui_BoardPedalIndex0001, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex0001, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex0001, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex0002

    ui_BoardPedalIndex0002 = lv_img_create(ui_BoardHContainer00);
    lv_img_set_src(ui_BoardPedalIndex0002, &ui_img_pedal_volume_png);

    lv_obj_set_width(ui_BoardPedalIndex0002, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex0002, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex0002, 156);
    lv_obj_set_y(ui_BoardPedalIndex0002, 0);

    lv_obj_set_align(ui_BoardPedalIndex0002, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex0002, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex0002, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex0003

    ui_BoardPedalIndex0003 = lv_img_create(ui_BoardHContainer00);
    lv_img_set_src(ui_BoardPedalIndex0003, &ui_img_pedal_empty_png);

    lv_obj_set_width(ui_BoardPedalIndex0003, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex0003, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex0003, 243);
    lv_obj_set_y(ui_BoardPedalIndex0003, 0);

    lv_obj_set_align(ui_BoardPedalIndex0003, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex0003, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex0003, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex0004

    ui_BoardPedalIndex0004 = lv_img_create(ui_BoardHContainer00);
    lv_img_set_src(ui_BoardPedalIndex0004, &ui_img_pedal_empty_png);

    lv_obj_set_width(ui_BoardPedalIndex0004, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex0004, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex0004, 330);
    lv_obj_set_y(ui_BoardPedalIndex0004, 1);

    lv_obj_set_align(ui_BoardPedalIndex0004, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex0004, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex0004, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex0005

    ui_BoardPedalIndex0005 = lv_img_create(ui_BoardHContainer00);
    lv_img_set_src(ui_BoardPedalIndex0005, &ui_img_pedal_empty_png);

    lv_obj_set_width(ui_BoardPedalIndex0005, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex0005, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex0005, 417);
    lv_obj_set_y(ui_BoardPedalIndex0005, 1);

    lv_obj_set_align(ui_BoardPedalIndex0005, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex0005, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex0005, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardHContainer01

    ui_BoardHContainer01 = lv_obj_create(ui_BoardContainer);

    lv_obj_set_width(ui_BoardHContainer01, 345);
    lv_obj_set_height(ui_BoardHContainer01, 89);

    lv_obj_set_x(ui_BoardHContainer01, 18);
    lv_obj_set_y(ui_BoardHContainer01, 92);

    lv_obj_set_align(ui_BoardHContainer01, LV_ALIGN_LEFT_MID);

    lv_obj_set_scrollbar_mode(ui_BoardHContainer01, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui_BoardHContainer01, LV_DIR_HOR);

    lv_obj_set_style_bg_color(ui_BoardHContainer01, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BoardHContainer01, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BoardHContainer01, lv_color_hex(0x003460), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BoardHContainer01, 70, LV_PART_MAIN | LV_STATE_DEFAULT);

    // MV:
    lv_obj_set_scroll_snap_x(ui_BoardHContainer01, LV_SCROLL_SNAP_NONE);

    // ui_BoardPedalIndex2

    ui_BoardPedalIndex2 = lv_img_create(ui_BoardHContainer01);
    lv_img_set_src(ui_BoardPedalIndex2, &ui_img_pedal_dist_png);

    lv_obj_set_width(ui_BoardPedalIndex2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex2, 69);
    lv_obj_set_y(ui_BoardPedalIndex2, 0);

    lv_obj_set_align(ui_BoardPedalIndex2, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex2, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex2, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex3

    ui_BoardPedalIndex3 = lv_img_create(ui_BoardHContainer01);
    lv_img_set_src(ui_BoardPedalIndex3, &ui_img_pedal_empty_png);

    lv_obj_set_width(ui_BoardPedalIndex3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex3, -18);
    lv_obj_set_y(ui_BoardPedalIndex3, 0);

    lv_obj_set_align(ui_BoardPedalIndex3, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex3, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex3, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardHContainer02

    ui_BoardHContainer02 = lv_obj_create(ui_BoardContainer);

    lv_obj_set_width(ui_BoardHContainer02, 345);
    lv_obj_set_height(ui_BoardHContainer02, 89);

    lv_obj_set_x(ui_BoardHContainer02, 18);
    lv_obj_set_y(ui_BoardHContainer02, 184);

    lv_obj_set_align(ui_BoardHContainer02, LV_ALIGN_LEFT_MID);

    lv_obj_set_scrollbar_mode(ui_BoardHContainer02, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui_BoardHContainer02, LV_DIR_HOR);

    lv_obj_set_style_bg_color(ui_BoardHContainer02, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BoardHContainer02, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BoardHContainer02, lv_color_hex(0x003460), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BoardHContainer02, 70, LV_PART_MAIN | LV_STATE_DEFAULT);

    // MV:
    lv_obj_set_scroll_snap_x(ui_BoardHContainer02, LV_SCROLL_SNAP_NONE);

    // ui_BoardPedalIndex13

    ui_BoardPedalIndex13 = lv_img_create(ui_BoardHContainer02);
    lv_img_set_src(ui_BoardPedalIndex13, &ui_img_pedal_dist_png);

    lv_obj_set_width(ui_BoardPedalIndex13, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex13, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex13, 69);
    lv_obj_set_y(ui_BoardPedalIndex13, 0);

    lv_obj_set_align(ui_BoardPedalIndex13, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex13, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex13, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex14

    ui_BoardPedalIndex14 = lv_img_create(ui_BoardHContainer02);
    lv_img_set_src(ui_BoardPedalIndex14, &ui_img_pedal_volume_png);

    lv_obj_set_width(ui_BoardPedalIndex14, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex14, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex14, 156);
    lv_obj_set_y(ui_BoardPedalIndex14, 0);

    lv_obj_set_align(ui_BoardPedalIndex14, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex14, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex14, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex15

    ui_BoardPedalIndex15 = lv_img_create(ui_BoardHContainer02);
    lv_img_set_src(ui_BoardPedalIndex15, &ui_img_pedal_echo_png);

    lv_obj_set_width(ui_BoardPedalIndex15, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex15, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex15, -18);
    lv_obj_set_y(ui_BoardPedalIndex15, 0);

    lv_obj_set_align(ui_BoardPedalIndex15, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex15, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex15, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex16

    ui_BoardPedalIndex16 = lv_img_create(ui_BoardHContainer02);
    lv_img_set_src(ui_BoardPedalIndex16, &ui_img_pedal_volume_png);

    lv_obj_set_width(ui_BoardPedalIndex16, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex16, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex16, 243);
    lv_obj_set_y(ui_BoardPedalIndex16, 0);

    lv_obj_set_align(ui_BoardPedalIndex16, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex16, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex16, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex17

    ui_BoardPedalIndex17 = lv_img_create(ui_BoardHContainer02);
    lv_img_set_src(ui_BoardPedalIndex17, &ui_img_pedal_volume_png);

    lv_obj_set_width(ui_BoardPedalIndex17, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex17, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex17, 330);
    lv_obj_set_y(ui_BoardPedalIndex17, 1);

    lv_obj_set_align(ui_BoardPedalIndex17, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex17, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex17, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex18

    ui_BoardPedalIndex18 = lv_img_create(ui_BoardHContainer02);
    lv_img_set_src(ui_BoardPedalIndex18, &ui_img_pedal_volume_png);

    lv_obj_set_width(ui_BoardPedalIndex18, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex18, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex18, 417);
    lv_obj_set_y(ui_BoardPedalIndex18, 1);

    lv_obj_set_align(ui_BoardPedalIndex18, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex18, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex18, LV_OBJ_FLAG_SCROLLABLE);

    // ui_ScreenIcon

    ui_ScreenIcon = lv_img_create(ui_ScreenBoards);
    lv_img_set_src(ui_ScreenIcon, &ui_img_screen_icon_png);

    lv_obj_set_width(ui_ScreenIcon, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ScreenIcon, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_ScreenIcon, 210);
    lv_obj_set_y(ui_ScreenIcon, -58);

    lv_obj_set_align(ui_ScreenIcon, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_ScreenIcon, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_ScreenIcon, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BtScreenUp

    ui_BtScreenUp = lv_btn_create(ui_ScreenBoards);

    lv_obj_set_width(ui_BtScreenUp, 44);
    lv_obj_set_height(ui_BtScreenUp, 50);

    lv_obj_set_x(ui_BtScreenUp, 210);
    lv_obj_set_y(ui_BtScreenUp, -98);

    lv_obj_set_align(ui_BtScreenUp, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_BtScreenUp, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_BtScreenUp, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_BtScreenUp, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BtScreenUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_BtScreenUp, &ui_img_arrows_up_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BtScreenUp, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BtScreenUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_BtScreenUp, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_BtScreenUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_BtScreenUp, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_BtScreenUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_BtScreenDown

    ui_BtScreenDown = lv_btn_create(ui_ScreenBoards);

    lv_obj_set_width(ui_BtScreenDown, 44);
    lv_obj_set_height(ui_BtScreenDown, 50);

    lv_obj_set_x(ui_BtScreenDown, 210);
    lv_obj_set_y(ui_BtScreenDown, -18);

    lv_obj_set_align(ui_BtScreenDown, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_BtScreenDown, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_BtScreenDown, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_BtScreenDown, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BtScreenDown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_BtScreenDown, &ui_img_arrows_down_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BtScreenDown, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BtScreenDown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_BtScreenDown, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_BtScreenDown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_BtScreenDown, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_BtScreenDown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

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

    // ui_BtBoardUp

    ui_BtBoardUp = lv_btn_create(ui_ScreenBoards);

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

    ui_BtBoardDown = lv_btn_create(ui_ScreenBoards);

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

    // ui_BoardHContainer1

    ui_BoardHContainer1 = lv_obj_create(ui_AvailableContainer);

    lv_obj_set_width(ui_BoardHContainer1, 345);
    lv_obj_set_height(ui_BoardHContainer1, 89);

    lv_obj_set_x(ui_BoardHContainer1, 18);
    lv_obj_set_y(ui_BoardHContainer1, 0);

    lv_obj_set_align(ui_BoardHContainer1, LV_ALIGN_LEFT_MID);

    lv_obj_set_scrollbar_mode(ui_BoardHContainer1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui_BoardHContainer1, LV_DIR_HOR);

    lv_obj_set_style_bg_color(ui_BoardHContainer1, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BoardHContainer1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BoardHContainer1, lv_color_hex(0x003460), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BoardHContainer1, 70, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_BoardPedalIndex7

    ui_BoardPedalIndex7 = lv_img_create(ui_BoardHContainer1);
    lv_img_set_src(ui_BoardPedalIndex7, &ui_img_pedal_volume_png);

    lv_obj_set_width(ui_BoardPedalIndex7, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex7, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex7, -18);
    lv_obj_set_y(ui_BoardPedalIndex7, 0);

    lv_obj_set_align(ui_BoardPedalIndex7, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex7, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex7, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex8

    ui_BoardPedalIndex8 = lv_img_create(ui_BoardHContainer1);
    lv_img_set_src(ui_BoardPedalIndex8, &ui_img_pedal_echo_png);

    lv_obj_set_width(ui_BoardPedalIndex8, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex8, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex8, 69);
    lv_obj_set_y(ui_BoardPedalIndex8, 0);

    lv_obj_set_align(ui_BoardPedalIndex8, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex8, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex8, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex9

    ui_BoardPedalIndex9 = lv_img_create(ui_BoardHContainer1);
    lv_img_set_src(ui_BoardPedalIndex9, &ui_img_pedal_dist_png);

    lv_obj_set_width(ui_BoardPedalIndex9, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex9, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex9, 156);
    lv_obj_set_y(ui_BoardPedalIndex9, 0);

    lv_obj_set_align(ui_BoardPedalIndex9, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex9, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex9, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex10

    ui_BoardPedalIndex10 = lv_img_create(ui_BoardHContainer1);
    lv_img_set_src(ui_BoardPedalIndex10, &ui_img_pedal_fuzz_png);

    lv_obj_set_width(ui_BoardPedalIndex10, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex10, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex10, 243);
    lv_obj_set_y(ui_BoardPedalIndex10, 0);

    lv_obj_set_align(ui_BoardPedalIndex10, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex10, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex10, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex11

    ui_BoardPedalIndex11 = lv_img_create(ui_BoardHContainer1);
    lv_img_set_src(ui_BoardPedalIndex11, &ui_img_pedal_compr_png);

    lv_obj_set_width(ui_BoardPedalIndex11, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex11, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex11, 330);
    lv_obj_set_y(ui_BoardPedalIndex11, 1);

    lv_obj_set_align(ui_BoardPedalIndex11, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex11, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex11, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex12

    ui_BoardPedalIndex12 = lv_img_create(ui_BoardHContainer1);
    lv_img_set_src(ui_BoardPedalIndex12, &ui_img_pedal_volume_png);

    lv_obj_set_width(ui_BoardPedalIndex12, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex12, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex12, 417);
    lv_obj_set_y(ui_BoardPedalIndex12, 1);

    lv_obj_set_align(ui_BoardPedalIndex12, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BoardPedalIndex12, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex12, LV_OBJ_FLAG_SCROLLABLE);
}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_ScreenBoards_screen_init();
    lv_disp_load_scr(ui_ScreenBoards);
}

