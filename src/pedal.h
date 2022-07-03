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
#ifndef _PEDAL_H
#define _PEDAL_H

#ifdef __cplusplus
extern "C" {
#endif

#if __has_include("lvgl.h")
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif


#define BOARD_MAX_NUM_PEDALS        6  // max num of pedals per board
#define NUM_MAX_BOARDS              8

#define Y_OFFSET_BOARD_ROWS         92
#define X_OFFSET_PEDAL              87
#define X_OFFSET_FIRST_PEDAL        -18


typedef uint32_t    audio_sample_t;
typedef audio_sample_t * (*process_audio_func_t) ( audio_sample_t * input,
                                                    int num_input_samples,
                                                    int * num_output_samples);

typedef enum {
    PEDAL_TYPE__VOLUME,
    PEDAL_TYPE__DISTORTION,
    PEDAL_TYPE__ECHO,
} pedal_type_t;

typedef struct pedal_volume_st
{
    int     volume;
} pedal_volume_t;

typedef struct pedal_distortion_st
{
    int     gain;
    int     clipping;
} pedal_distortion_t;

typedef struct pedal_echo_st
{
    int                     delay;          //  in milliseconds
    float                   feedback_gain;
    int                     num_samples;    //
    audio_sample_t *        samples;        // 32 bits: 16 for left, 16 for right
} pedal_echo_t;

typedef union {
    pedal_volume_t *        volume_ptr;
    pedal_distortion_t *    distortion_ptr;
    pedal_echo_t *          echo_ptr;
} props_t;

typedef struct pedal_st
{
    lv_obj_t *              PropScreen;         // properties screen
    lv_obj_t *              normal_img;         // normal image
    lv_obj_t *              highlighted_img;    // pressed or selected image
    int                     pos_idx;            // position index (inside Board container)
    pedal_type_t            type;

    // firmware
    props_t                 props;              // properties
    process_audio_func_t    process_audio;
} pedal_t;

typedef struct pedal_board_st
{
    int         num_pedals;
    lv_obj_t * ui_BoardHContainer;
    pedal_t     pedals[BOARD_MAX_NUM_PEDALS];
    int         selected_pedal_idx;
} pedal_board_t;

typedef struct boards_st
{
    int                     num_boards;
    pedal_board_t           boards[NUM_MAX_BOARDS];
} boards_t;



#ifdef __cplusplus
}
#endif

//----------------------------------------------------------------
#endif // _PEDAL_H_
