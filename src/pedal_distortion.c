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

#include "log.h"
#include "ui.h"
#include "pedal.h"
#include <stdlib.h>

#define GAIN_SLIDER_IDX 0
#define CLIPPING_SLIDER_IDX 2

static const char * info = { "Plug-in: Distortion\nVersion: 0.0.1\nBy: Varanda Labs"};
static const char * gain_text = { "Gain:"};
static const char * clipping_text = { "Clipping:"};

static void update_props_values(pedal_t * pedal)
{
    // gain
    int val = pedal->props.distortion->generic_props.generic_slider[GAIN_SLIDER_IDX].slider_pos;
    char * target_text = pedal->props.distortion->generic_props.generic_slider[GAIN_SLIDER_IDX].prop_val_text;

    // gain (0~10 times)
    float f_val = val/10.0;
    snprintf(   target_text,
                MAX_PROP_VAL_TEXT,
                "%.2f",
                f_val);

    // clipping (0~1)
    val = pedal->props.distortion->generic_props.generic_slider[CLIPPING_SLIDER_IDX].slider_pos;
    target_text = pedal->props.distortion->generic_props.generic_slider[CLIPPING_SLIDER_IDX].prop_val_text;

     f_val = val/100.0;
     snprintf(   target_text,
                MAX_PROP_VAL_TEXT,
                "%.2f",
                f_val);

}

static void new_context(pedal_t * pedal)
{
    LOG("New Distortion");
    pedal->props.distortion = calloc(1, sizeof(pedal_props_distortion_t));
    if (! pedal->props.distortion) {
        LOG_E("new_context: no memo");
    }

    // enter default prop values:
    pedal->props.distortion->generic_props.info = info;

    pedal->props.distortion->generic_props.generic_slider[GAIN_SLIDER_IDX].slider_label = gain_text;
    pedal->props.distortion->generic_props.generic_slider[GAIN_SLIDER_IDX].slider_pos = 10;

    pedal->props.distortion->generic_props.generic_slider[CLIPPING_SLIDER_IDX].slider_label = clipping_text;
    pedal->props.distortion->generic_props.generic_slider[CLIPPING_SLIDER_IDX].slider_pos = 50;

    update_props_values(pedal);
}

static void delete_context(pedal_t * pedal)
{
    LOG("Delete Distortion");
    free(pedal->props.distortion);
    pedal->props.distortion = NULL;
}

static audio_sample_t * process_audio(   audio_sample_t * input,
                                                    int num_input_samples,
                                                    int * num_output_samples)
{
    return NULL;
}

void pedal_init_available_distortion(void * _pedal)
{
    pedal_t * pedal = (pedal_t *) _pedal;
    pedal->PropScreen = NULL;        // properties screen
    pedal->normal_img = &ui_img_pedal_dist_png;         // normal image
    pedal->type = PEDAL_TYPE__DISTORTION;
    pedal->props.compressor = NULL,            // properties
    pedal->pedal_new_context_func_t = new_context;
    pedal->pedal_delete_context_func_t = delete_context;
    pedal->update_props_values_func_t = update_props_values;

    pedal->process_audio = process_audio;

}


