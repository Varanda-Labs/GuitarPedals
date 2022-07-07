#ifndef GENERIC_PROPS_CTL_H
#define GENERIC_PROPS_CTL_H

typedef void (*process_slider_input_func_t) (   int slider_pos,
                                                int * prop_val);


typedef struct generic_slider_st
{
    const char *    slider_label;   // label
    int             slider_pos;     // 0~100 position in/out
    int             prop_val;       // val
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
    const char * info;
    generic_slider_t generic_slider[3];
    generic_check_t generic_check[2];
} generic_props_ctl_t;

#endif // GENERIC_PROPS_CTL_H
