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

#define SUSTAIN_SLIDER_IDX 0
#define TONE_SLIDER_IDX 1
#define ATTACK_SLIDER_IDX 2

static const char * info = { "Plug-in: Compressor\nVersion: 0.0.1\nBy: Varanda Labs"};
static const char * sustain_text = { "Sustain:"};
static const char * tone_text = { "Tone:"};
static const char * attack_text = { "Attack:"};

static void update_props_values(pedal_t * pedal)
{
    // Sustain level
    int val = pedal->props.compressor->generic_props.generic_slider[SUSTAIN_SLIDER_IDX].slider_pos;
    char * target_text = pedal->props.compressor->generic_props.generic_slider[SUSTAIN_SLIDER_IDX].prop_val_text;

    snprintf(   target_text,
                MAX_PROP_VAL_TEXT,
                "%d %%",
                val);

    // tone
    val = pedal->props.compressor->generic_props.generic_slider[TONE_SLIDER_IDX].slider_pos;
    target_text = pedal->props.compressor->generic_props.generic_slider[TONE_SLIDER_IDX].prop_val_text;

     snprintf(   target_text,
                MAX_PROP_VAL_TEXT,
                "%d %%",
                val);

     val = pedal->props.compressor->generic_props.generic_slider[ATTACK_SLIDER_IDX].slider_pos;
     target_text = pedal->props.compressor->generic_props.generic_slider[ATTACK_SLIDER_IDX].prop_val_text;

      snprintf(   target_text,
                 MAX_PROP_VAL_TEXT,
                 "%d %%",
                 val);

}
static void new_context(pedal_t * pedal)
{
    LOG("New Compressor");
    pedal->props.compressor = calloc(1, sizeof(pedal_props_compressor_t));
    if (! pedal->props.compressor) {
        LOG_E("new_context: no memo");
    }

    // enter default prop values:
    pedal->props.volume->generic_props.info = info;

    pedal->props.volume->generic_props.generic_slider[SUSTAIN_SLIDER_IDX].slider_label = sustain_text;
    pedal->props.volume->generic_props.generic_slider[SUSTAIN_SLIDER_IDX].slider_pos = 50;

    pedal->props.volume->generic_props.generic_slider[TONE_SLIDER_IDX].slider_label = tone_text;
    pedal->props.volume->generic_props.generic_slider[TONE_SLIDER_IDX].slider_pos = 50;

    pedal->props.volume->generic_props.generic_slider[ATTACK_SLIDER_IDX].slider_label = attack_text;
    pedal->props.volume->generic_props.generic_slider[ATTACK_SLIDER_IDX].slider_pos = 50;

    update_props_values(pedal);
}

static void delete_context(pedal_t * pedal)
{
    LOG("Delete Compressor");
    free(pedal->props.compressor);
    pedal->props.compressor = NULL;
}

static audio_sample_t * process_audio(   audio_sample_t * input,
                                         int num_input_samples,
                                         int * num_output_samples)
{
    return NULL;
}

void pedal_init_available_compressor(void * _pedal)
{
    pedal_t * pedal = (pedal_t *) _pedal;
    pedal->PropScreen = NULL;        // properties screen
    pedal->normal_img = &ui_img_pedal_compr_png;         // normal image
    pedal->type = PEDAL_TYPE__COMPRESSOR;
    pedal->props.compressor = NULL,            // properties
    pedal->pedal_new_context_func_t = new_context;
    pedal->pedal_delete_context_func_t = delete_context;
    pedal->update_props_values_func_t = update_props_values;


    pedal->process_audio = process_audio;

}


