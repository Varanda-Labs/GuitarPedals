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

#define LAST_LOGO_IMAGE_IDX 24
#define FRAME_TIME 150

///////////////////// VARIABLES ////////////////////
/// \brief ui_AnimLogoScreen
extern lv_obj_t * ui_ScreenBoards;
extern lv_obj_t * ui_VisualScreen;
extern lv_indev_t * global_indev;

lv_obj_t * ui_AnimLogoScreen;
lv_obj_t * ui_AboutScreen;
static bool    lock_screen_swipe = false;

LV_IMG_DECLARE(ui_img_0000_png);    // assets/0000.png
LV_IMG_DECLARE(ui_img_0001_png);    // assets/0001.png
LV_IMG_DECLARE(ui_img_0002_png);    // assets/0002.png
LV_IMG_DECLARE(ui_img_0003_png);    // assets/0003.png
LV_IMG_DECLARE(ui_img_0004_png);    // assets/0004.png
LV_IMG_DECLARE(ui_img_0005_png);    // assets/0005.png
LV_IMG_DECLARE(ui_img_0006_png);    // assets/0006.png
LV_IMG_DECLARE(ui_img_0007_png);    // assets/0007.png
LV_IMG_DECLARE(ui_img_0008_png);    // assets/0008.png
LV_IMG_DECLARE(ui_img_0009_png);    // assets/0009.png
LV_IMG_DECLARE(ui_img_0010_png);    // assets/0010.png
LV_IMG_DECLARE(ui_img_0011_png);    // assets/0011.png
LV_IMG_DECLARE(ui_img_0012_png);    // assets/0012.png
LV_IMG_DECLARE(ui_img_0013_png);    // assets/0013.png
LV_IMG_DECLARE(ui_img_0014_png);    // assets/0014.png
LV_IMG_DECLARE(ui_img_0015_png);    // assets/0015.png
LV_IMG_DECLARE(ui_img_0016_png);    // assets/0016.png
LV_IMG_DECLARE(ui_img_0017_png);    // assets/0017.png
LV_IMG_DECLARE(ui_img_0018_png);    // assets/0018.png
LV_IMG_DECLARE(ui_img_0019_png);    // assets/0019.png
LV_IMG_DECLARE(ui_img_0020_png);    // assets/0020.png
LV_IMG_DECLARE(ui_img_0021_png);    // assets/0021.png
LV_IMG_DECLARE(ui_img_0022_png);    // assets/0022.png
LV_IMG_DECLARE(ui_img_0023_png);    // assets/0023.png
LV_IMG_DECLARE(ui_img_0024_png);    // assets/0024.png
LV_IMG_DECLARE(ui_img_about_png);    // assets/about.png


///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif


static lv_timer_t * timer;
static int img_idx = 1;

static const lv_img_dsc_t * images[] = {
    &ui_img_0000_png,
    &ui_img_0001_png,
    &ui_img_0002_png,
    &ui_img_0003_png,
    &ui_img_0004_png,
    &ui_img_0005_png,
    &ui_img_0006_png,
    &ui_img_0007_png,
    &ui_img_0008_png,
    &ui_img_0009_png,
    &ui_img_0010_png,
    &ui_img_0011_png,
    &ui_img_0012_png,
    &ui_img_0013_png,
    &ui_img_0014_png,
    &ui_img_0015_png,
    &ui_img_0016_png,
    &ui_img_0017_png,
    &ui_img_0018_png,
    &ui_img_0019_png,
    &ui_img_0020_png,
    &ui_img_0021_png,
    &ui_img_0022_png,
    &ui_img_0023_png,
    &ui_img_0024_png,
    &ui_img_about_png,
};

///////////////////// ANIMATIONS ////////////////////
/// \brief play_logo
void animete(void * arg)
{
    if (img_idx <= LAST_LOGO_IMAGE_IDX) {
        lv_obj_set_style_bg_img_src(ui_AnimLogoScreen, images[img_idx++], LV_PART_MAIN | LV_STATE_DEFAULT);
        LOG("update image %d", img_idx);
        return;
    }
    img_idx++;

    if (img_idx == LAST_LOGO_IMAGE_IDX + 2) {
        // lv_scr_load_anim(ui_AboutScreen, LV_SCR_LOAD_ANIM_FADE_IN, SCREEN_LOAD_SPEED / 2, 0, 0);
        lv_scr_load_anim(ui_AboutScreen, LV_SCR_LOAD_ANIM_FADE_ON, SCREEN_LOAD_SPEED / 2, 0, 0);

    }

    if (img_idx >= LAST_LOGO_IMAGE_IDX + 10) {
        load_screen_up(ui_ScreenBoards);
        LOG("should stop %d", img_idx);
        lv_timer_del(timer);
    }

    LOG("still in timer %d", img_idx);

}

void play_logo()
{
    timer = lv_timer_create(animete, FRAME_TIME,  NULL);
}
///////////////////// FUNCTIONS ////////////////////
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

///////////////////// SCREENS ////////////////////
void init_ui_about_screen(void)
{

    // ui_AnimLogoScreen

    ui_AboutScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_AboutScreen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_AboutScreen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_AboutScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_img_src(ui_AboutScreen, &ui_img_about_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_AboutScreen, OnRightTopPanelContainerEvent, LV_EVENT_ALL, NULL);   /*Assign an event callback*/
    lv_obj_add_flag(ui_AboutScreen, LV_OBJ_FLAG_CLICKABLE);
}

void init_ui_AnimLogoScreen_screen(void)
{

    // ui_AnimLogoScreen

    ui_AnimLogoScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_AnimLogoScreen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_img_src(ui_AnimLogoScreen, &ui_img_0000_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    init_ui_about_screen();

}

