// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"
#include "lv_style.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Screen1;
lv_obj_t * ui_labelPadels;
lv_obj_t * ui_BoardContainer;
lv_obj_t * ui_PedalsContainer;
lv_obj_t * ui_LabelBoard;
lv_obj_t * ui_RightTopPanelContainer;
lv_obj_t * ui_LeftArrowPadels;
lv_obj_t * ui_LeftArrowBoard;
lv_obj_t * ui_RightArrowPedals;
lv_obj_t * ui_RightArrowBoard;
lv_obj_t * ui_PedalAvIndex0;
lv_obj_t * ui_PedalAvIndex1;
lv_obj_t * ui_PedalAvIndex2;
lv_obj_t * ui_PedalAvIndex3;
lv_obj_t * ui_BoardPedalIndex0;
lv_obj_t * ui_BoardPedalIndex1;
lv_obj_t * ui_BoardPedalIndex2;
lv_obj_t * ui_ScreenIcon;
lv_obj_t * ui_BtScreenUp;
lv_obj_t * ui_BtScreenDown;
lv_obj_t * ui_RightBottomPanelContainer;
lv_obj_t * ui_BtBoardUp;
lv_obj_t * ui_BtBoardDown;
lv_obj_t * ui_BoardIcon;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{

    // ui_Screen1

    ui_Screen1 = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_Screen1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Screen1, &ui_img_guitar_background_01_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_Screen1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_Screen1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Screen1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Screen1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_blend_mode(ui_Screen1, LV_BLEND_MODE.NORMAL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_blend_mode(ui_Screen1, LV_BLEND_MODE_NORMAL, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_labelPadels

    ui_labelPadels = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_labelPadels, &ui_img_padels_label_png);

    lv_obj_set_width(ui_labelPadels, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_labelPadels, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_labelPadels, 9);
    lv_obj_set_y(ui_labelPadels, 10);

    lv_obj_add_flag(ui_labelPadels, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_labelPadels, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardContainer

    ui_BoardContainer = lv_obj_create(ui_Screen1);

    lv_obj_set_width(ui_BoardContainer, 407);
    lv_obj_set_height(ui_BoardContainer, 89);

    lv_obj_set_x(ui_BoardContainer, 11);
    lv_obj_set_y(ui_BoardContainer, 167);

    lv_obj_clear_flag(ui_BoardContainer, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_BoardContainer, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BoardContainer, 64, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BoardContainer, lv_color_hex(0x003460), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BoardContainer, 70, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_PedalsContainer

    ui_PedalsContainer = lv_obj_create(ui_Screen1);

    lv_obj_set_width(ui_PedalsContainer, 414);
    lv_obj_set_height(ui_PedalsContainer, 89);

    lv_obj_set_x(ui_PedalsContainer, 6);
    lv_obj_set_y(ui_PedalsContainer, 32);

    lv_obj_clear_flag(ui_PedalsContainer, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_PedalsContainer, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PedalsContainer, 64, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PedalsContainer, lv_color_hex(0x003460), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PedalsContainer, 70, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LabelBoard

    ui_LabelBoard = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_LabelBoard, &ui_img_board_label_png);

    lv_obj_set_width(ui_LabelBoard, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelBoard, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelBoard, 16);
    lv_obj_set_y(ui_LabelBoard, 145);

    lv_obj_add_flag(ui_LabelBoard, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_LabelBoard, LV_OBJ_FLAG_SCROLLABLE);

    // ui_RightTopPanelContainer

    ui_RightTopPanelContainer = lv_obj_create(ui_Screen1);

    lv_obj_set_width(ui_RightTopPanelContainer, 51);
    lv_obj_set_height(ui_RightTopPanelContainer, 116);

    lv_obj_set_x(ui_RightTopPanelContainer, 425);
    lv_obj_set_y(ui_RightTopPanelContainer, 19);

    lv_obj_clear_flag(ui_RightTopPanelContainer, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_RightTopPanelContainer, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RightTopPanelContainer, 64, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_RightTopPanelContainer, lv_color_hex(0x003460), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_RightTopPanelContainer, 70, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LeftArrowPadels

    ui_LeftArrowPadels = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_LeftArrowPadels, &ui_img_left_arrow_png);

    lv_obj_set_width(ui_LeftArrowPadels, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LeftArrowPadels, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LeftArrowPadels, 11);
    lv_obj_set_y(ui_LeftArrowPadels, 43);

    lv_obj_add_flag(ui_LeftArrowPadels, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_LeftArrowPadels, LV_OBJ_FLAG_SCROLLABLE);

    // ui_LeftArrowBoard

    ui_LeftArrowBoard = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_LeftArrowBoard, &ui_img_left_arrow_png);

    lv_obj_set_width(ui_LeftArrowBoard, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LeftArrowBoard, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LeftArrowBoard, 13);
    lv_obj_set_y(ui_LeftArrowBoard, 177);

    lv_obj_add_flag(ui_LeftArrowBoard, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_LeftArrowBoard, LV_OBJ_FLAG_SCROLLABLE);

    // ui_RightArrowPedals

    ui_RightArrowPedals = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_RightArrowPedals, &ui_img_right_arrow_png);

    lv_obj_set_width(ui_RightArrowPedals, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_RightArrowPedals, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_RightArrowPedals, 394);
    lv_obj_set_y(ui_RightArrowPedals, 43);

    lv_obj_add_flag(ui_RightArrowPedals, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_RightArrowPedals, LV_OBJ_FLAG_SCROLLABLE);

    // ui_RightArrowBoard

    ui_RightArrowBoard = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_RightArrowBoard, &ui_img_right_arrow_png);

    lv_obj_set_width(ui_RightArrowBoard, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_RightArrowBoard, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_RightArrowBoard, 394);
    lv_obj_set_y(ui_RightArrowBoard, 177);

    lv_obj_add_flag(ui_RightArrowBoard, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_RightArrowBoard, LV_OBJ_FLAG_SCROLLABLE);

    // ui_PedalAvIndex0

    ui_PedalAvIndex0 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_PedalAvIndex0, &ui_img_pedal_dist_png);

    lv_obj_set_width(ui_PedalAvIndex0, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_PedalAvIndex0, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_PedalAvIndex0, 42);
    lv_obj_set_y(ui_PedalAvIndex0, 37);

    lv_obj_add_flag(ui_PedalAvIndex0, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_PedalAvIndex0, LV_OBJ_FLAG_SCROLLABLE);

    // ui_PedalAvIndex1

    ui_PedalAvIndex1 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_PedalAvIndex1, &ui_img_pedal_volume_png);

    lv_obj_set_width(ui_PedalAvIndex1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_PedalAvIndex1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_PedalAvIndex1, 129);
    lv_obj_set_y(ui_PedalAvIndex1, 37);

    lv_obj_add_flag(ui_PedalAvIndex1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_PedalAvIndex1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_PedalAvIndex2

    ui_PedalAvIndex2 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_PedalAvIndex2, &ui_img_pedal_fuzz_png);

    lv_obj_set_width(ui_PedalAvIndex2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_PedalAvIndex2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_PedalAvIndex2, 215);
    lv_obj_set_y(ui_PedalAvIndex2, 37);

    lv_obj_add_flag(ui_PedalAvIndex2, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_PedalAvIndex2, LV_OBJ_FLAG_SCROLLABLE);

    // ui_PedalAvIndex3

    ui_PedalAvIndex3 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_PedalAvIndex3, &ui_img_pedal_compr_png);

    lv_obj_set_width(ui_PedalAvIndex3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_PedalAvIndex3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_PedalAvIndex3, 301);
    lv_obj_set_y(ui_PedalAvIndex3, 37);

    lv_obj_add_flag(ui_PedalAvIndex3, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_PedalAvIndex3, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex0

    ui_BoardPedalIndex0 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_BoardPedalIndex0, &ui_img_pedal_echo_png);

    lv_obj_set_width(ui_BoardPedalIndex0, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex0, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex0, 42);
    lv_obj_set_y(ui_BoardPedalIndex0, 171);

    lv_obj_add_flag(ui_BoardPedalIndex0, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex0, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex1

    ui_BoardPedalIndex1 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_BoardPedalIndex1, &ui_img_pedal_dist_png);

    lv_obj_set_width(ui_BoardPedalIndex1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex1, 129);
    lv_obj_set_y(ui_BoardPedalIndex1, 171);

    lv_obj_add_flag(ui_BoardPedalIndex1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BoardPedalIndex2

    ui_BoardPedalIndex2 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_BoardPedalIndex2, &ui_img_pedal_volume_png);

    lv_obj_set_width(ui_BoardPedalIndex2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardPedalIndex2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardPedalIndex2, 215);
    lv_obj_set_y(ui_BoardPedalIndex2, 171);

    lv_obj_add_flag(ui_BoardPedalIndex2, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardPedalIndex2, LV_OBJ_FLAG_SCROLLABLE);

    // ui_ScreenIcon

    ui_ScreenIcon = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_ScreenIcon, &ui_img_screen_icon_png);

    lv_obj_set_width(ui_ScreenIcon, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ScreenIcon, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_ScreenIcon, 210);
    lv_obj_set_y(ui_ScreenIcon, -58);

    lv_obj_set_align(ui_ScreenIcon, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_ScreenIcon, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_ScreenIcon, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BtScreenUp

    ui_BtScreenUp = lv_btn_create(ui_Screen1);

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

    ui_BtScreenDown = lv_btn_create(ui_Screen1);

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

    ui_RightBottomPanelContainer = lv_obj_create(ui_Screen1);

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

    ui_BtBoardUp = lv_btn_create(ui_Screen1);

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

    ui_BtBoardDown = lv_btn_create(ui_Screen1);

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

    ui_BoardIcon = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_BoardIcon, &ui_img_boards_icon_png);

    lv_obj_set_width(ui_BoardIcon, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BoardIcon, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BoardIcon, 210);
    lv_obj_set_y(ui_BoardIcon, 72);

    lv_obj_set_align(ui_BoardIcon, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_BoardIcon, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_BoardIcon, LV_OBJ_FLAG_SCROLLABLE);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    lv_disp_load_scr(ui_Screen1);
}

