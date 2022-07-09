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

#define FUZZ_SLIDER_IDX 0
#define TONE_SLIDER_IDX 2

static const char * info = { "Plug-in: Fuzz\nVersion: 0.0.1\nBy: Varanda Labs"};
static const char * fuzz_text = { "Fuzz level:"};
static const char * tone_text = { "Tone:"};

static void update_props_values(pedal_t * pedal)
{
    // fuzz level
    int val = pedal->props.fuzz->generic_props.generic_slider[FUZZ_SLIDER_IDX].slider_pos;
    char * target_text = pedal->props.fuzz->generic_props.generic_slider[FUZZ_SLIDER_IDX].prop_val_text;

    snprintf(   target_text,
                MAX_PROP_VAL_TEXT,
                "%d %%",
                val);

    // tone
    val = pedal->props.fuzz->generic_props.generic_slider[TONE_SLIDER_IDX].slider_pos;
    target_text = pedal->props.fuzz->generic_props.generic_slider[TONE_SLIDER_IDX].prop_val_text;

     snprintf(   target_text,
                MAX_PROP_VAL_TEXT,
                "%d %%",
                val);

}

static void new_context(pedal_t * pedal)
{
    LOG("New Fuzz");
    pedal->props.fuzz = calloc(1, sizeof(pedal_props_fuzz_t));
    if (! pedal->props.fuzz) {
        LOG_E("new_context: no memo");
    }

    // enter default prop values:
    pedal->props.volume->generic_props.info = info;

    pedal->props.volume->generic_props.generic_slider[FUZZ_SLIDER_IDX].slider_label = fuzz_text;
    pedal->props.volume->generic_props.generic_slider[FUZZ_SLIDER_IDX].slider_pos = 50;

    pedal->props.volume->generic_props.generic_slider[TONE_SLIDER_IDX].slider_label = tone_text;
    pedal->props.volume->generic_props.generic_slider[TONE_SLIDER_IDX].slider_pos = 50;

    update_props_values(pedal);
}

static void delete_context(pedal_t * pedal)
{
    LOG("Delete Fuzz");
    free(pedal->props.fuzz);
    pedal->props.fuzz = NULL;
}

static audio_sample_t * process_audio(   audio_sample_t * input,
                                         int num_input_samples,
                                         int * num_output_samples,
                                         pedal_t * pedal)
{
    return NULL;
}

void pedal_init_available_fuzz(void * _pedal)
{
    pedal_t * pedal = (pedal_t *) _pedal;
    pedal->PropScreen = NULL;        // properties screen
    pedal->normal_img = &ui_img_pedal_fuzz_png;         // normal image
    pedal->type = PEDAL_TYPE__FUZZ;
    pedal->props.compressor = NULL,            // properties
    pedal->pedal_new_context_func_t = new_context;
    pedal->pedal_delete_context_func_t = delete_context;
    pedal->update_props_values_func_t = update_props_values;

    pedal->process_audio = process_audio;

}


