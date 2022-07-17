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

#include "util.h"


///////////////////// VARIABLES ////////////////////
extern lv_obj_t * ui_ScreenBoards;
extern lv_obj_t * ui_VisualScreen;
extern lv_indev_t * global_indev;
lv_obj_t * ui_AboutScreen;

static bool    lock_screen_swipe = false;

LV_IMG_DECLARE(ui_img_about_png);    // assets/about.png

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

        if (start_y < -5) {
            start_y = 0;
            load_screen_up(ui_VisualScreen);
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

void init_ui_about_screen(void)
{

    // ui_AnimLogoScreen
    LOG("Creating About screen\n");

    ui_AboutScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_AboutScreen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_AboutScreen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_AboutScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_img_src(ui_AboutScreen, &ui_img_about_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_AboutScreen, OnRightTopPanelContainerEvent, LV_EVENT_ALL, NULL);   /*Assign an event callback*/
    lv_obj_add_flag(ui_AboutScreen, LV_OBJ_FLAG_CLICKABLE);
}
