#ifndef UTIL_H
#define UTIL_H
#if __has_include("lvgl.h")
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#define SCREEN_LOAD_SPEED 300

void show(lv_obj_t * widget);
void hide(lv_obj_t * widget);
void load_screen_up(lv_obj_t * screen);
void load_screen_down(lv_obj_t * screen);

#endif // UTIL_H
