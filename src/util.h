#ifndef UTIL_H
#define UTIL_H
#if __has_include("lvgl.h")
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

void show(lv_obj_t * widget);
void hide(lv_obj_t * widget);

#endif // UTIL_H
