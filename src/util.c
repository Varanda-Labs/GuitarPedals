
#include "util.h"

void show(lv_obj_t * widget)
{
    lv_obj_clear_flag(widget, LV_OBJ_FLAG_HIDDEN);
}

void hide(lv_obj_t * widget)
{
    lv_obj_add_flag(widget, LV_OBJ_FLAG_HIDDEN);
}

void load_screen_up(lv_obj_t * screen)
{
    lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_MOVE_TOP, SCREEN_LOAD_SPEED, 0, 0);
}

void load_screen_down(lv_obj_t * screen)
{
    lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, SCREEN_LOAD_SPEED, 0, 0);
}
