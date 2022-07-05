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

static void new_context(pedal_t * pedal)
{
    LOG("New Distortion");
    pedal->props.distortion = calloc(1, sizeof(pedal_props_distortion_t));
    if (! pedal->props.distortion) {
        LOG_E("new_context: no memo");
    }

    // enter default prop values:
}

static void delete_context(pedal_t * pedal)
{

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
    pedal->highlighted_img = NULL;    // pressed or selected image
    pedal->pos_idx = 0;            // position index (inside Board container)
    pedal->type = PEDAL_TYPE__DISTORTION;
    pedal->props.compressor = NULL,            // properties
    pedal->pedal_new_context_func_t = new_context;
    pedal->pedal_delete_context_func_t = delete_context;

    pedal->process_audio = process_audio;

}


