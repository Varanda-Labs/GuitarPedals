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
#include "pedal.h"
#include "log.h"
#include "util.h"

///////////////////// VARIABLES ////////////////////

extern lv_indev_t * global_indev;

static bool is_playing = false;

lv_obj_t * ui_VisualScreen;
static lv_obj_t * ui_PlayerPanel;
static lv_obj_t * ui_Chart1;
static lv_obj_t * ui_GuitarOrPlayerSwitch;
static lv_obj_t * ui_GuitarLabel;
static lv_obj_t * ui_PlayerLabel;
static lv_obj_t * ui_playimg;
static lv_obj_t * ui_stopimg;
static lv_obj_t * ui_RightTopPanelContainer2;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

static bool    lock_screen_swipe = false;

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
extern void start_player();
extern void stop_player();

static void OnPlayEvent(lv_event_t * event)
{
    if (event->code == LV_EVENT_CLICKED) {
//        start_player();
        is_playing = true;
        hide(ui_playimg);
        show(ui_stopimg);
    }
}

static void OnStopPlayEvent(lv_event_t * event)
{
    if (event->code == LV_EVENT_CLICKED) {
//        stop_player();
        is_playing = false;
        hide(ui_stopimg);
        show(ui_playimg);
    }
}

static void OnRightTopPanelContainerEvent(lv_event_t * event)
{
    static int start_y = -1;
    lv_point_t point;
    int e = lv_event_get_code(event);

    switch(e)
    {
    case LV_EVENT_PRESSED:             /**< The object has been pressed*/
        lv_indev_get_vect(global_indev, &point);
        start_y = 0;
        break;
    case LV_EVENT_PRESSING:
        lv_indev_get_vect(global_indev, &point);
        start_y += point.y;

        if (lock_screen_swipe) break;

        if (start_y > 5) {
            start_y = 0;
            lv_scr_load_anim(ui_ScreenBoards, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, SCREE_LOAD_SPEED, 0, 0);
            lock_screen_swipe = true;
        }
        if (start_y < -5) {
            start_y = 0;
            lv_scr_load_anim(ui_ScreenBoards, LV_SCR_LOAD_ANIM_MOVE_TOP, SCREE_LOAD_SPEED, 0, 0);
            lock_screen_swipe = true;
        }
        break;

    case LV_EVENT_RELEASED:
        start_y = -1;
        lock_screen_swipe = false;
        break;

    default:
        break;
    }
}
///////////////////// SCREENS ////////////////////
void init_VisualScreen_screen(void)
{

    // ui_VisualScreen

    ui_VisualScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_VisualScreen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_img_src(ui_VisualScreen, &ui_img_disp_background_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_PlayerPanel

    ui_PlayerPanel = lv_obj_create(ui_VisualScreen);

    lv_obj_set_width(ui_PlayerPanel, 382);
    lv_obj_set_height(ui_PlayerPanel, 43);

    lv_obj_set_x(ui_PlayerPanel, 24);
    lv_obj_set_y(ui_PlayerPanel, 212);

    lv_obj_clear_flag(ui_PlayerPanel, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_PlayerPanel, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PlayerPanel, 64, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PlayerPanel, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PlayerPanel, 64, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_PlayerPanel, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_PlayerPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Chart1

    ui_Chart1 = lv_chart_create(ui_VisualScreen);

    lv_obj_set_width(ui_Chart1, 380);
    lv_obj_set_height(ui_Chart1, 177);

    lv_obj_set_x(ui_Chart1, 24);
    lv_obj_set_y(ui_Chart1, 19);

    lv_obj_set_style_bg_color(ui_Chart1, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Chart1, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Chart1, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Chart1, 97, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_Chart1, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_Chart1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_line_color(ui_Chart1, lv_color_hex(0x47DFFF), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui_Chart1, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui_Chart1, lv_color_hex(0x47DFFF), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui_Chart1, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);

    // ui_GuitarOrPlayerSwitch

    ui_GuitarOrPlayerSwitch = lv_switch_create(ui_VisualScreen);

    lv_obj_set_width(ui_GuitarOrPlayerSwitch, 50);
    lv_obj_set_height(ui_GuitarOrPlayerSwitch, 25);

    lv_obj_set_x(ui_GuitarOrPlayerSwitch, -115);
    lv_obj_set_y(ui_GuitarOrPlayerSwitch, 97);

    lv_obj_set_align(ui_GuitarOrPlayerSwitch, LV_ALIGN_CENTER);

    lv_obj_set_style_bg_color(ui_GuitarOrPlayerSwitch, lv_color_hex(0x001E28), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_GuitarOrPlayerSwitch, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_GuitarOrPlayerSwitch, lv_color_hex(0x47DFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_GuitarOrPlayerSwitch, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    // ui_GuitarLabel

    ui_GuitarLabel = lv_label_create(ui_VisualScreen);

    lv_obj_set_width(ui_GuitarLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_GuitarLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_GuitarLabel, -177);
    lv_obj_set_y(ui_GuitarLabel, 97);

    lv_obj_set_align(ui_GuitarLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_GuitarLabel, "Guitar");

    lv_obj_set_style_text_color(ui_GuitarLabel, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_GuitarLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_GuitarLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_GuitarLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_PlayerLabel

    ui_PlayerLabel = lv_label_create(ui_VisualScreen);

    lv_obj_set_width(ui_PlayerLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_PlayerLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_PlayerLabel, -56);
    lv_obj_set_y(ui_PlayerLabel, 97);

    lv_obj_set_align(ui_PlayerLabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_PlayerLabel, "Player");

    lv_obj_set_style_text_color(ui_PlayerLabel, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_PlayerLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PlayerLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PlayerLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_playimg

    ui_playimg = lv_img_create(ui_VisualScreen);
    lv_img_set_src(ui_playimg, &ui_img_play_icon_png);

    lv_obj_set_width(ui_playimg, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_playimg, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_playimg, 50);
    lv_obj_set_y(ui_playimg, 97);

    lv_obj_set_align(ui_playimg, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_playimg, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_playimg, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_playimg, OnPlayEvent, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui_playimg, LV_OBJ_FLAG_CLICKABLE);

    // ui_stopimg

    ui_stopimg = lv_img_create(ui_VisualScreen);
    lv_img_set_src(ui_stopimg, &ui_img_stop_icon_png);

    lv_obj_set_width(ui_stopimg, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_stopimg, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_stopimg, 48);
    lv_obj_set_y(ui_stopimg, 97);

    lv_obj_set_align(ui_stopimg, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_stopimg, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_stopimg, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_stopimg, OnStopPlayEvent, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui_stopimg, LV_OBJ_FLAG_CLICKABLE);

    hide(ui_stopimg);

    // ui_RightTopPanelContainer2

    ui_RightTopPanelContainer2 = lv_obj_create(ui_VisualScreen);

    lv_obj_set_width(ui_RightTopPanelContainer2, 51);
    lv_obj_set_height(ui_RightTopPanelContainer2, 116);

    lv_obj_set_x(ui_RightTopPanelContainer2, 425);
    lv_obj_set_y(ui_RightTopPanelContainer2, 19);

    lv_obj_add_flag(ui_RightTopPanelContainer2, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_RightTopPanelContainer2, lv_color_hex(0x47DFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(ui_RightTopPanelContainer2, 64, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui_RightTopPanelContainer2, lv_color_hex(PRESSED_COLOR), LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_set_style_bg_opa(ui_RightTopPanelContainer2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_RightTopPanelContainer2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_RightTopPanelContainer2, OnRightTopPanelContainerEvent, LV_EVENT_ALL, NULL);   /*Assign an event callback*/
    lv_obj_add_flag(ui_RightTopPanelContainer2, LV_OBJ_FLAG_CLICKABLE);
}

void process_audio_frame(char * buffer, int len)
{
    if ( ! is_playing) {
        if (len)
            memset(buffer, 0, len);
        return;
    }
#if 1
    pedal_board_t * board = &boards[board_idx];

    if (len < 4) return;
    len = len & 0xfffffffc;
    int i, n_out;

    if (board->num_pedals > 0)
    {
        for (i=0; i < board->num_pedals; i++) {
            if (board->pedals[i].process_audio) {
                board->pedals[i].process_audio((uint32_t *) buffer, len, &n_out, &board->pedals[i]);
            }
        }
    }
#endif
}
