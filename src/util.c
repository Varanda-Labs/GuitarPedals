
#include "util.h"

void show(lv_obj_t * widget)
{
    lv_obj_clear_flag(widget, LV_OBJ_FLAG_HIDDEN);
}

void hide(lv_obj_t * widget)
{
    lv_obj_add_flag(widget, LV_OBJ_FLAG_HIDDEN);
}
