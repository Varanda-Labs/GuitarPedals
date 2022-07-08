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

#ifndef GENERIC_PROPS_CTL_H
#define GENERIC_PROPS_CTL_H

#define MAX_PROP_VAL_TEXT   16

typedef void (*process_slider_input_func_t) (   int slider_pos,
                                                int * prop_val);


typedef struct generic_slider_st
{
    const char *    slider_label;                   // label
    int             slider_pos;                     // 0~100 position in/out
    char            prop_val_text[MAX_PROP_VAL_TEXT];    // val
    void            (*process_slider_input_func_t) (struct generic_slider_st * generic_slider);
} generic_slider_t;

typedef struct generic_check_st
{
    const char *    check_label;    // label
    bool            check;          // 0~100 position in/out
    void            (*process_check_input_func_t) (struct generic_check_st * generic_slider);
} generic_check_t;

typedef struct generic_props_ctl_st
{
    char * info;
    generic_slider_t generic_slider[3];
    generic_check_t generic_check[2];
} generic_props_ctl_t;

extern void * ui_genericPropScreen;
void set_generic_props_ctl(void * pedal); // generic_props_ctl_t * _generic_props_ctl);
void ui_genericPropScreen_screen_init(void);



#endif // GENERIC_PROPS_CTL_H
