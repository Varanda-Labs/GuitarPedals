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
//lv_obj_t * ui_genericPropScreen;

extern lv_indev_t * global_indev;
static pedal_t * active_pedal = NULL;
void * ui_genericPropScreen;
static bool    lock_screen_swipe = false;

static lv_obj_t * ui_LabelInfo;

static lv_obj_t * ui_Slider0;
static lv_obj_t * ui_LabelSlider0;
static lv_obj_t * ui_val0;

static lv_obj_t * ui_Slider1;
static lv_obj_t * ui_LabelSlider1;
static lv_obj_t * ui_val1;

static lv_obj_t * ui_LabelSlider2;
static lv_obj_t * ui_Slider2;
static lv_obj_t * ui_val2;

static lv_obj_t * ui_Checkbox0;
static lv_obj_t * ui_Checkbox1;

static lv_obj_t * ui_RightTopPanelContainer2;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

extern lv_color_t g_default_fg_color;  // global foreground color
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

static generic_props_ctl_t * g = NULL;


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
            lv_scr_load_anim(ui_ScreenBoards, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 500, 0, 0);
            lock_screen_swipe = true;
        }
        if (start_y < -5) {
            start_y = 0;
            lv_scr_load_anim(ui_ScreenBoards, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 500, 0, 0);
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

void OnSliderChange(lv_event_t * event)
{
    int idx = (int) event->user_data;
    g->generic_slider[idx].slider_pos = (int)lv_slider_get_value(event->target);

    if (active_pedal && active_pedal->update_props_values_func_t) {
        active_pedal->update_props_values_func_t(active_pedal);

        // update value
        switch(idx){
        case 0: lv_label_set_text(ui_val0, g->generic_slider[idx].prop_val_text); break;
        case 1: lv_label_set_text(ui_val1, g->generic_slider[idx].prop_val_text); break;
        case 2: lv_label_set_text(ui_val2, g->generic_slider[idx].prop_val_text); break;
        default: LOG_E("OnCheckChange: unexpected idx %d", idx); break;
        }
    }
}

void OnCheckChange(lv_event_t * event)
{
    int idx = (int) event->user_data;
    g->generic_check[idx].check = lv_obj_has_state(event->target, LV_STATE_CHECKED);

    // update value


}

static void set_slider_pos(lv_obj_t * slider, int val)
{
    lv_slider_set_value(slider, val, LV_ANIM_OFF);
}

void set_generic_props_ctl(void * _pedal)
{
    active_pedal = _pedal;
    g = &active_pedal->props.volume->generic_props; // generic_props_ctl;

    hide(ui_Slider0);
    hide(ui_LabelSlider0);
    hide(ui_val0);

    hide(ui_Slider1);
    hide(ui_LabelSlider1);
    hide(ui_val1);

    hide(ui_LabelSlider2);
    hide(ui_Slider2);
    hide(ui_val2);

    hide(ui_Checkbox0);
    hide(ui_Checkbox1);

    lv_label_set_text(ui_LabelInfo, g->info);

    if (g->generic_slider[0].slider_label) {
        lv_label_set_text(ui_LabelSlider0, g->generic_slider[0].slider_label);
        set_slider_pos(ui_Slider0, g->generic_slider[0].slider_pos);
        lv_label_set_text(ui_val0, g->generic_slider[0].prop_val_text);
        show(ui_Slider0);
        show(ui_val0);
        show(ui_LabelSlider0);
    }

    if (g->generic_slider[1].slider_label) {
        lv_label_set_text(ui_LabelSlider1, g->generic_slider[1].slider_label);
        set_slider_pos(ui_Slider1, g->generic_slider[1].slider_pos);
        lv_label_set_text(ui_val1, g->generic_slider[1].prop_val_text);
        show(ui_Slider1);
        show(ui_val1);
        show(ui_LabelSlider1);
    }

    if (g->generic_slider[2].slider_label) {
        lv_label_set_text(ui_LabelSlider2, g->generic_slider[2].slider_label);
        set_slider_pos(ui_Slider2, g->generic_slider[2].slider_pos);
        lv_label_set_text(ui_val2, g->generic_slider[2].prop_val_text);
        show(ui_Slider2);
        show(ui_val2);
        show(ui_LabelSlider2);
    }

    if (g->generic_check[0].check_label) {
        lv_checkbox_set_text(ui_Checkbox0, g->generic_check[0].check_label);
        if (g->generic_check[0].check) {
            lv_obj_add_state(ui_Checkbox0, LV_STATE_CHECKED);
        } else {
            lv_obj_clear_state(ui_Checkbox0, LV_STATE_CHECKED);
        }
        show(ui_Checkbox0);
    }

    if (g->generic_check[1].check_label) {
        lv_checkbox_set_text(ui_Checkbox1, g->generic_check[1].check_label);
        if (g->generic_check[1].check) {
            lv_obj_add_state(ui_Checkbox1, LV_STATE_CHECKED);
        } else {
            lv_obj_clear_state(ui_Checkbox1, LV_STATE_CHECKED);
        }
        show(ui_Checkbox1);
    }
}

///////////////////// SCREENS ////////////////////
/// \brief ui_genericPropScreen_screen_init
///
void ui_genericPropScreen_screen_init(void)
{

    // ui_genericPropScreen

    ui_genericPropScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_genericPropScreen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_genericPropScreen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_genericPropScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LabelInfo

    ui_LabelInfo = lv_label_create(ui_genericPropScreen);

    lv_obj_set_width(ui_LabelInfo, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelInfo, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelInfo, -166);
    lv_obj_set_y(ui_LabelInfo, -97);

    lv_obj_set_align(ui_LabelInfo, LV_ALIGN_CENTER);

    lv_obj_set_style_text_color(ui_LabelInfo, g_default_fg_color, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ui_LabelInfo, "Plug-in: \nVersion:\nBy:");

    // ui_Slider0

    ui_Slider0 = lv_slider_create(ui_genericPropScreen);
    lv_slider_set_range(ui_Slider0, 0, 100);

    lv_obj_set_width(ui_Slider0, 233);
    lv_obj_set_height(ui_Slider0, 10);

    lv_obj_set_x(ui_Slider0, -120);
    lv_obj_set_y(ui_Slider0, 93);

    lv_obj_set_align(ui_Slider0, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_event_cb(ui_Slider0, OnSliderChange, LV_EVENT_VALUE_CHANGED, (void *) 0);

    // ui_LabelSlider0

    ui_LabelSlider0 = lv_label_create(ui_genericPropScreen);

    lv_obj_set_width(ui_LabelSlider0, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelSlider0, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelSlider0, -198);
    lv_obj_set_y(ui_LabelSlider0, -40);

    lv_obj_set_align(ui_LabelSlider0, LV_ALIGN_CENTER);

    lv_obj_set_style_text_color(ui_LabelSlider0, g_default_fg_color, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ui_LabelSlider0, "Volume:");

    // ui_Slider1

    ui_Slider1 = lv_slider_create(ui_genericPropScreen);
    lv_slider_set_range(ui_Slider1, 0, 100);

    lv_obj_set_width(ui_Slider1, 233);
    lv_obj_set_height(ui_Slider1, 10);

    lv_obj_set_x(ui_Slider1, -120);
    lv_obj_set_y(ui_Slider1, 139);

    lv_obj_set_align(ui_Slider1, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_event_cb(ui_Slider1, OnSliderChange, LV_EVENT_VALUE_CHANGED, (void *) 1);

    // ui_LabelSlider1

    ui_LabelSlider1 = lv_label_create(ui_genericPropScreen);

    lv_obj_set_width(ui_LabelSlider1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelSlider1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelSlider1, -197);
    lv_obj_set_y(ui_LabelSlider1, 5);

    lv_obj_set_align(ui_LabelSlider1, LV_ALIGN_CENTER);

    lv_obj_set_style_text_color(ui_LabelSlider1, g_default_fg_color, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ui_LabelSlider1, "Volume:");

    // ui_LabelSlider2

    ui_LabelSlider2 = lv_label_create(ui_genericPropScreen);

    lv_obj_set_width(ui_LabelSlider2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelSlider2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelSlider2, -197);
    lv_obj_set_y(ui_LabelSlider2, 51);

    lv_obj_set_align(ui_LabelSlider2, LV_ALIGN_CENTER);

    lv_obj_set_style_text_color(ui_LabelSlider2, g_default_fg_color, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ui_LabelSlider2, "Volume:");

    // ui_Slider2

    ui_Slider2 = lv_slider_create(ui_genericPropScreen);
    lv_slider_set_range(ui_Slider2, 0, 100);

    lv_obj_set_width(ui_Slider2, 233);
    lv_obj_set_height(ui_Slider2, 10);

    lv_obj_set_x(ui_Slider2, -118);
    lv_obj_set_y(ui_Slider2, 186);

    lv_obj_set_align(ui_Slider2, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_event_cb(ui_Slider2, OnSliderChange, LV_EVENT_VALUE_CHANGED, (void *) 2);

    // ui_Checkbox style
    static lv_style_t style_indic;
    lv_style_init(&style_indic);
    lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));

    // ui_Checkbox0
    ui_Checkbox0 = lv_checkbox_create(ui_genericPropScreen);
    lv_checkbox_set_text(ui_Checkbox0, "Checkbox");

    lv_obj_set_width(ui_Checkbox0, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Checkbox0, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Checkbox0, -174);
    lv_obj_set_y(ui_Checkbox0, 100);

    lv_obj_set_align(ui_Checkbox0, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Checkbox0, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_add_event_cb(ui_Checkbox0, OnCheckChange, LV_EVENT_VALUE_CHANGED, (void *) 0);
    lv_obj_set_style_text_color(ui_Checkbox0, g_default_fg_color, LV_PART_MAIN | LV_STATE_DEFAULT);



    // ui_Checkbox1

    ui_Checkbox1 = lv_checkbox_create(ui_genericPropScreen);
    lv_checkbox_set_text(ui_Checkbox1, "Checkbox");

    lv_obj_set_width(ui_Checkbox1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Checkbox1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Checkbox1, 2);
    lv_obj_set_y(ui_Checkbox1, 101);

    lv_obj_set_align(ui_Checkbox1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Checkbox1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_add_event_cb(ui_Checkbox1, OnCheckChange, LV_EVENT_VALUE_CHANGED, (void *) 1);

    // ui_val0

    ui_val0 = lv_label_create(ui_genericPropScreen);

    lv_obj_set_width(ui_val0, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_val0, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_val0, -6);
    lv_obj_set_y(ui_val0, -63);

    lv_obj_set_align(ui_val0, LV_ALIGN_CENTER);

    lv_obj_set_style_text_color(ui_val0, g_default_fg_color, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ui_val0, "Text");

    // ui_val1

    ui_val1 = lv_label_create(ui_genericPropScreen);

    lv_obj_set_width(ui_val1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_val1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_val1, -6);
    lv_obj_set_y(ui_val1, -15);

    lv_obj_set_align(ui_val1, LV_ALIGN_CENTER);

    lv_obj_set_style_text_color(ui_val1, g_default_fg_color, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ui_val1, "Text");

    // ui_val2

    ui_val2 = lv_label_create(ui_genericPropScreen);

    lv_obj_set_width(ui_val2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_val2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_val2, -6);
    lv_obj_set_y(ui_val2, 34);

    lv_obj_set_align(ui_val2, LV_ALIGN_CENTER);

    lv_obj_set_style_text_color(ui_val2, g_default_fg_color, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ui_val2, "Text");

    // ui_RightTopPanelContainer2

    ui_RightTopPanelContainer2 = lv_obj_create(ui_genericPropScreen);

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

    lv_obj_add_event_cb(ui_RightTopPanelContainer2, OnRightTopPanelContainerScrollBegin, LV_EVENT_ALL, NULL);   /*Assign an event callback*/
    lv_obj_add_flag(ui_RightTopPanelContainer2, LV_OBJ_FLAG_CLICKABLE);

}
