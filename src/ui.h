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

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if __has_include("lvgl.h")
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

extern lv_obj_t * ui_ScreenBoards;
extern lv_obj_t * ui_labelPadels;
extern lv_obj_t * ui_LabelBoard;
extern lv_obj_t * ui_RightTopPanelContainer;
extern lv_obj_t * ui_LeftArrowPadels;
extern lv_obj_t * ui_LeftArrowBoard;
extern lv_obj_t * ui_RightArrowPedals;
extern lv_obj_t * ui_RightArrowBoard;
extern lv_obj_t * ui_BoardCounter;
extern lv_obj_t * ui_BoardContainer;

extern lv_obj_t * ui_RightBottomPanelContainer;
extern lv_obj_t * ui_BtBoardUp;
extern lv_obj_t * ui_BtBoardDown;
extern lv_obj_t * ui_BoardIcon;

extern lv_obj_t * ui_DialogPanel;
extern lv_obj_t * ui_diaProps;
extern lv_obj_t * ui_diaMoveRight;
extern lv_obj_t * ui_diaMoveLeft;
extern lv_obj_t * ui_diaRemova;
extern lv_obj_t * ui_diaEnable;
extern lv_obj_t * ui_diaClose;
extern lv_obj_t * ui_diaCheck;


LV_IMG_DECLARE(ui_img_sel_props_png);    // assets/sel_props.png
LV_IMG_DECLARE(ui_img_sel_move_right_png);    // assets/sel_move_right.png
LV_IMG_DECLARE(ui_img_sel_move_left_png);    // assets/sel_move_left.png
LV_IMG_DECLARE(ui_img_sel_remove_png);    // assets/sel_remove.png
LV_IMG_DECLARE(ui_img_sel_enable_png);    // assets/sel_enable.png
LV_IMG_DECLARE(ui_img_sel_close_png);    // assets/sel_close.png
LV_IMG_DECLARE(ui_img_sel_check_png);    // assets/sel_check.png

LV_IMG_DECLARE(ui_img_disp_background_png);    // assets/disp_background.png
LV_IMG_DECLARE(ui_img_padels_label_png);    // assets/padels_label.png
LV_IMG_DECLARE(ui_img_board_label_png);    // assets/board_label.png
LV_IMG_DECLARE(ui_img_left_arrow_png);    // assets/left_arrow.png
LV_IMG_DECLARE(ui_img_right_arrow_png);    // assets/right_arrow.png
LV_IMG_DECLARE(ui_img_number_0_png);    // assets/number_0.png
LV_IMG_DECLARE(ui_img_number_1_png);    // assets/number_1.png
LV_IMG_DECLARE(ui_img_number_2_png);    // assets/number_2.png
LV_IMG_DECLARE(ui_img_number_3_png);    // assets/number_3.png
LV_IMG_DECLARE(ui_img_number_4_png);    // assets/number_4.png
LV_IMG_DECLARE(ui_img_number_5_png);    // assets/number_5.png
LV_IMG_DECLARE(ui_img_number_6_png);    // assets/number_6.png
LV_IMG_DECLARE(ui_img_number_7_png);    // assets/number_7.png
LV_IMG_DECLARE(ui_img_number_8_png);    // assets/number_8.png
LV_IMG_DECLARE(ui_img_number_9_png);    // assets/number_9.png
LV_IMG_DECLARE(ui_img_pedal_echo_png);    // assets/Pedal_Echo.png
LV_IMG_DECLARE(ui_img_pedal_dist_png);    // assets/Pedal_Dist.png
LV_IMG_DECLARE(ui_img_pedal_volume_png);    // assets/Pedal_Volume.png
LV_IMG_DECLARE(ui_img_pedal_empty_png);    // assets/Pedal_Empty.png
LV_IMG_DECLARE(ui_img_screen_icon_png);    // assets/screen_icon.png
LV_IMG_DECLARE(ui_img_arrows_up_png);    // assets/arrows_up.png
LV_IMG_DECLARE(ui_img_arrows_down_png);    // assets/arrows_down.png
LV_IMG_DECLARE(ui_img_boards_icon_png);    // assets/boards_icon.png
LV_IMG_DECLARE(ui_img_pedal_fuzz_png);    // assets/Pedal_Fuzz.png
LV_IMG_DECLARE(ui_img_pedal_compr_png);    // assets/Pedal_Compr.png


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
