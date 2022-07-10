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
lv_obj_t * ui_AnimLogoScreen;
lv_obj_t * ui_AboutScreen;

#if 0
static lv_obj_t * ui_about;
static lv_obj_t * ui_Image1;
static lv_obj_t * ui_Image2;
static lv_obj_t * ui_Image3;
static lv_obj_t * ui_Image4;
static lv_obj_t * ui_Image5;
static lv_obj_t * ui_Image6;
static lv_obj_t * ui_Image7;
static lv_obj_t * ui_Image8;
static lv_obj_t * ui_Image9;
static lv_obj_t * ui_Image10;
static lv_obj_t * ui_Image11;
static lv_obj_t * ui_Image12;
static lv_obj_t * ui_Image13;
static lv_obj_t * ui_Image14;
static lv_obj_t * ui_Image15;
static lv_obj_t * ui_Image16;
static lv_obj_t * ui_Image17;
static lv_obj_t * ui_Image18;
static lv_obj_t * ui_Image19;
static lv_obj_t * ui_Image20;
static lv_obj_t * ui_Image21;
static lv_obj_t * ui_Image22;
static lv_obj_t * ui_Image23;
static lv_obj_t * ui_Image24;
#endif


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
        lv_scr_load_anim(ui_AboutScreen, LV_SCR_LOAD_ANIM_FADE_IN, SCREEN_LOAD_SPEED, 0, 0);
    }

    if (img_idx >= LAST_LOGO_IMAGE_IDX + 16) {
        //lv_scr_load_anim(ui_ScreenBoards, LV_SCR_LOAD_ANIM_FADE_IN, SCREEN_LOAD_SPEED, 0, 0);
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

///////////////////// SCREENS ////////////////////
void init_ui_about_screen(void)
{

    // ui_AnimLogoScreen

    ui_AboutScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_AboutScreen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_AboutScreen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_AboutScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_img_src(ui_AboutScreen, &ui_img_about_png, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void init_ui_AnimLogoScreen_screen(void)
{

    // ui_AnimLogoScreen

    ui_AnimLogoScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_AnimLogoScreen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_img_src(ui_AnimLogoScreen, &ui_img_0000_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    init_ui_about_screen();

#if 0
    // ui_Image1

    ui_Image1 = lv_img_create(ui_AnimLogoScreen);
    lv_img_set_src(ui_Image1, &ui_img_0001_png);

    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image1, -204);
    lv_obj_set_y(ui_Image1, -105);

    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image2

    ui_Image2 = lv_img_create(ui_AnimLogoScreen);
    lv_img_set_src(ui_Image2, &ui_img_0002_png);

    lv_obj_set_width(ui_Image2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image2, -116);
    lv_obj_set_y(ui_Image2, -86);

    lv_obj_set_align(ui_Image2, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image3

    ui_Image3 = lv_img_create(ui_AnimLogoScreen);
    lv_img_set_src(ui_Image3, &ui_img_0003_png);

    lv_obj_set_width(ui_Image3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image3, -37);
    lv_obj_set_y(ui_Image3, -86);

    lv_obj_set_align(ui_Image3, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image4

    ui_Image4 = lv_img_create(ui_AnimLogoScreen);
    lv_img_set_src(ui_Image4, &ui_img_0004_png);

    lv_obj_set_width(ui_Image4, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image4, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image4, 34);
    lv_obj_set_y(ui_Image4, -87);

    lv_obj_set_align(ui_Image4, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image4, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image5

    ui_Image5 = lv_img_create(ui_AnimLogoScreen);
    lv_img_set_src(ui_Image5, &ui_img_0005_png);

    lv_obj_set_width(ui_Image5, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image5, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image5, 109);
    lv_obj_set_y(ui_Image5, -87);

    lv_obj_set_align(ui_Image5, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image5, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image5, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image6

    ui_Image6 = lv_img_create(ui_AnimLogoScreen);
    lv_img_set_src(ui_Image6, &ui_img_0006_png);

    lv_obj_set_width(ui_Image6, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image6, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image6, 186);
    lv_obj_set_y(ui_Image6, -87);

    lv_obj_set_align(ui_Image6, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image6, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image6, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image7

    ui_Image7 = lv_img_create(ui_AnimLogoScreen);
    lv_img_set_src(ui_Image7, &ui_img_0007_png);

    lv_obj_set_width(ui_Image7, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image7, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image7, -185);
    lv_obj_set_y(ui_Image7, 1);

    lv_obj_set_align(ui_Image7, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image7, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image7, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image8

    ui_Image8 = lv_img_create(ui_AnimLogoScreen);
    lv_img_set_src(ui_Image8, &ui_img_0008_png);

    lv_obj_set_width(ui_Image8, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image8, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image8, -109);
    lv_obj_set_y(ui_Image8, 1);

    lv_obj_set_align(ui_Image8, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image8, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image8, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image9

    ui_Image9 = lv_img_create(ui_AnimLogoScreen);
    lv_img_set_src(ui_Image9, &ui_img_0009_png);

    lv_obj_set_width(ui_Image9, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image9, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image9, -33);
    lv_obj_set_y(ui_Image9, -1);

    lv_obj_set_align(ui_Image9, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image9, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image9, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image10

    ui_Image10 = lv_img_create(ui_AnimLogoScreen);
    lv_img_set_src(ui_Image10, &ui_img_0010_png);

    lv_obj_set_width(ui_Image10, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image10, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image10, 40);
    lv_obj_set_y(ui_Image10, 0);

    lv_obj_set_align(ui_Image10, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image10, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image10, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image11

    ui_Image11 = lv_img_create(ui_AnimLogoScreen);
    lv_img_set_src(ui_Image11, &ui_img_0011_png);

    lv_obj_set_width(ui_Image11, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image11, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image11, 116);
    lv_obj_set_y(ui_Image11, 1);

    lv_obj_set_align(ui_Image11, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image11, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image11, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image12

    ui_Image12 = lv_img_create(ui_AnimLogoScreen);
    lv_img_set_src(ui_Image12, &ui_img_0012_png);

    lv_obj_set_width(ui_Image12, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image12, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image12, 188);
    lv_obj_set_y(ui_Image12, 10);

    lv_obj_set_align(ui_Image12, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image12, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image12, LV_OBJ_FLAG_SCROLLABLE);

}
void ui_AnimLogoScreen1_screen_init(void)
{

    // ui_AnimLogoScreen1

    ui_AnimLogoScreen1 = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_AnimLogoScreen1, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_img_src(ui_AnimLogoScreen1, &ui_img_0000_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Image13

    ui_Image13 = lv_img_create(ui_AnimLogoScreen1);
    lv_img_set_src(ui_Image13, &ui_img_0013_png);

    lv_obj_set_width(ui_Image13, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image13, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image13, -204);
    lv_obj_set_y(ui_Image13, -105);

    lv_obj_set_align(ui_Image13, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image13, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image13, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image14

    ui_Image14 = lv_img_create(ui_AnimLogoScreen1);
    lv_img_set_src(ui_Image14, &ui_img_0014_png);

    lv_obj_set_width(ui_Image14, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image14, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image14, -116);
    lv_obj_set_y(ui_Image14, -86);

    lv_obj_set_align(ui_Image14, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image14, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image14, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image15

    ui_Image15 = lv_img_create(ui_AnimLogoScreen1);
    lv_img_set_src(ui_Image15, &ui_img_0015_png);

    lv_obj_set_width(ui_Image15, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image15, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image15, -37);
    lv_obj_set_y(ui_Image15, -86);

    lv_obj_set_align(ui_Image15, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image15, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image15, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image16

    ui_Image16 = lv_img_create(ui_AnimLogoScreen1);
    lv_img_set_src(ui_Image16, &ui_img_0016_png);

    lv_obj_set_width(ui_Image16, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image16, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image16, 34);
    lv_obj_set_y(ui_Image16, -87);

    lv_obj_set_align(ui_Image16, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image16, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image16, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image17

    ui_Image17 = lv_img_create(ui_AnimLogoScreen1);
    lv_img_set_src(ui_Image17, &ui_img_0017_png);

    lv_obj_set_width(ui_Image17, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image17, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image17, 109);
    lv_obj_set_y(ui_Image17, -87);

    lv_obj_set_align(ui_Image17, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image17, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image17, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image18

    ui_Image18 = lv_img_create(ui_AnimLogoScreen1);
    lv_img_set_src(ui_Image18, &ui_img_0018_png);

    lv_obj_set_width(ui_Image18, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image18, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image18, 186);
    lv_obj_set_y(ui_Image18, -87);

    lv_obj_set_align(ui_Image18, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image18, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image18, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image19

    ui_Image19 = lv_img_create(ui_AnimLogoScreen1);
    lv_img_set_src(ui_Image19, &ui_img_0019_png);

    lv_obj_set_width(ui_Image19, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image19, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image19, -185);
    lv_obj_set_y(ui_Image19, 1);

    lv_obj_set_align(ui_Image19, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image19, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image19, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image20

    ui_Image20 = lv_img_create(ui_AnimLogoScreen1);
    lv_img_set_src(ui_Image20, &ui_img_0020_png);

    lv_obj_set_width(ui_Image20, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image20, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image20, -109);
    lv_obj_set_y(ui_Image20, 1);

    lv_obj_set_align(ui_Image20, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image20, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image20, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image21

    ui_Image21 = lv_img_create(ui_AnimLogoScreen1);
    lv_img_set_src(ui_Image21, &ui_img_0021_png);

    lv_obj_set_width(ui_Image21, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image21, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image21, -33);
    lv_obj_set_y(ui_Image21, -1);

    lv_obj_set_align(ui_Image21, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image21, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image21, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image22

    ui_Image22 = lv_img_create(ui_AnimLogoScreen1);
    lv_img_set_src(ui_Image22, &ui_img_0022_png);

    lv_obj_set_width(ui_Image22, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image22, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image22, 40);
    lv_obj_set_y(ui_Image22, 0);

    lv_obj_set_align(ui_Image22, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image22, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image22, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image23

    ui_Image23 = lv_img_create(ui_AnimLogoScreen1);
    lv_img_set_src(ui_Image23, &ui_img_0023_png);

    lv_obj_set_width(ui_Image23, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image23, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image23, 116);
    lv_obj_set_y(ui_Image23, 1);

    lv_obj_set_align(ui_Image23, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image23, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image23, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image24

    ui_Image24 = lv_img_create(ui_AnimLogoScreen1);
    lv_img_set_src(ui_Image24, &ui_img_0024_png);

    lv_obj_set_width(ui_Image24, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image24, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image24, 188);
    lv_obj_set_y(ui_Image24, 10);

    lv_obj_set_align(ui_Image24, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image24, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image24, LV_OBJ_FLAG_SCROLLABLE);

    // ui_about

    ui_about = lv_img_create(ui_AnimLogoScreen1);
    lv_img_set_src(ui_about, &ui_img_about_png);

    lv_obj_set_width(ui_about, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_about, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_about, 0);
    lv_obj_set_y(ui_about, 0);

    lv_obj_set_align(ui_about, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_about, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_about, LV_OBJ_FLAG_SCROLLABLE);
#endif

}

// void ui_init(void)
// {
//     lv_disp_t * dispp = lv_disp_get_default();
//     lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
//                                                false, LV_FONT_DEFAULT);
//     lv_disp_set_theme(dispp, theme);
//     ui_AnimLogoScreen_screen_init();
//     lv_disp_load_scr(ui_AnimLogoScreen);
// }

