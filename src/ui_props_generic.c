// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: SquareLine_Volume

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Slider1;
lv_obj_t * ui_LabelSlider1;
lv_obj_t * ui_Slider2;
lv_obj_t * ui_LabelSlider2;
lv_obj_t * ui_LabelSlider3;
lv_obj_t * ui_Slider3;
lv_obj_t * ui_Checkbox1;
lv_obj_t * ui_Checkbox2;

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
    lv_obj_set_style_bg_img_src(ui_Screen1, &ui_img_disp_background_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Label1

    ui_Label1 = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Label1, -166);
    lv_obj_set_y(ui_Label1, -97);

    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label1, "Plug-in: Volume\nVersion: 0.0.1\nBy: Varanda Labs");

    // ui_Slider1

    ui_Slider1 = lv_slider_create(ui_Screen1);
    lv_slider_set_range(ui_Slider1, 0, 100);

    lv_obj_set_width(ui_Slider1, 233);
    lv_obj_set_height(ui_Slider1, 10);

    lv_obj_set_x(ui_Slider1, -120);
    lv_obj_set_y(ui_Slider1, 93);

    lv_obj_set_align(ui_Slider1, LV_ALIGN_TOP_RIGHT);

    // ui_LabelSlider1

    ui_LabelSlider1 = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_LabelSlider1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelSlider1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelSlider1, -198);
    lv_obj_set_y(ui_LabelSlider1, -40);

    lv_obj_set_align(ui_LabelSlider1, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LabelSlider1, "Volume:");

    // ui_Slider2

    ui_Slider2 = lv_slider_create(ui_Screen1);
    lv_slider_set_range(ui_Slider2, 0, 100);

    lv_obj_set_width(ui_Slider2, 233);
    lv_obj_set_height(ui_Slider2, 10);

    lv_obj_set_x(ui_Slider2, -120);
    lv_obj_set_y(ui_Slider2, 139);

    lv_obj_set_align(ui_Slider2, LV_ALIGN_TOP_RIGHT);

    // ui_LabelSlider2

    ui_LabelSlider2 = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_LabelSlider2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelSlider2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelSlider2, -197);
    lv_obj_set_y(ui_LabelSlider2, 5);

    lv_obj_set_align(ui_LabelSlider2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LabelSlider2, "Volume:");

    // ui_LabelSlider3

    ui_LabelSlider3 = lv_label_create(ui_Screen1);

    lv_obj_set_width(ui_LabelSlider3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelSlider3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelSlider3, -197);
    lv_obj_set_y(ui_LabelSlider3, 51);

    lv_obj_set_align(ui_LabelSlider3, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LabelSlider3, "Volume:");

    // ui_Slider3

    ui_Slider3 = lv_slider_create(ui_Screen1);
    lv_slider_set_range(ui_Slider3, 0, 100);

    lv_obj_set_width(ui_Slider3, 233);
    lv_obj_set_height(ui_Slider3, 10);

    lv_obj_set_x(ui_Slider3, -118);
    lv_obj_set_y(ui_Slider3, 186);

    lv_obj_set_align(ui_Slider3, LV_ALIGN_TOP_RIGHT);

    // ui_Checkbox1

    ui_Checkbox1 = lv_checkbox_create(ui_Screen1);
    lv_checkbox_set_text(ui_Checkbox1, "Checkbox");

    lv_obj_set_width(ui_Checkbox1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Checkbox1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Checkbox1, -174);
    lv_obj_set_y(ui_Checkbox1, 100);

    lv_obj_set_align(ui_Checkbox1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Checkbox1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    // ui_Checkbox2

    ui_Checkbox2 = lv_checkbox_create(ui_Screen1);
    lv_checkbox_set_text(ui_Checkbox2, "Checkbox");

    lv_obj_set_width(ui_Checkbox2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Checkbox2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Checkbox2, 2);
    lv_obj_set_y(ui_Checkbox2, 101);

    lv_obj_set_align(ui_Checkbox2, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Checkbox2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

}

// void ui_init(void)
// {
//     lv_disp_t * dispp = lv_disp_get_default();
//     lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
//                                                false, LV_FONT_DEFAULT);
//     lv_disp_set_theme(dispp, theme);
//     ui_Screen1_screen_init();
//     lv_disp_load_scr(ui_Screen1);
// }

