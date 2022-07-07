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

#define DELAY_SLIDER_IDX 0
#define GAIN_SLIDER_IDX 2

static const char * info = { "Plug-in: Echo\nVersion: 0.0.1\nBy: Varanda Labs"};
static const char * delay_text = { "Delay (ms):"};
static const char * gain_text = { "Gain:"};

static const char * check_text = { "Across R/L:"};


static void new_context(pedal_t * pedal)
{
    LOG("New Echo");
    pedal->props.echo = calloc(1, sizeof(pedal_props_echo_t));
    if (! pedal->props.echo) {
        LOG_E("new_context: no memo");
    }

    // enter default prop values:
    pedal->props.volume->generic_props.info = info;

    pedal->props.volume->generic_props.generic_slider[DELAY_SLIDER_IDX].slider_label = delay_text;
    pedal->props.volume->generic_props.generic_slider[DELAY_SLIDER_IDX].slider_pos = 1;
    snprintf(   pedal->props.volume->generic_props.generic_slider[DELAY_SLIDER_IDX].prop_val_text,
                MAX_PROP_VAL_TEXT,
                "%d ms",
                10);

    pedal->props.volume->generic_props.generic_slider[GAIN_SLIDER_IDX].slider_label = gain_text;
    pedal->props.volume->generic_props.generic_slider[GAIN_SLIDER_IDX].slider_pos = 20;
    snprintf(   pedal->props.volume->generic_props.generic_slider[GAIN_SLIDER_IDX].prop_val_text,
                MAX_PROP_VAL_TEXT,
                "%.2f",
                0.2);

    pedal->props.volume->generic_props.generic_check[0].check_label = check_text;
}

static void delete_context(pedal_t * pedal)
{
    LOG("Delete Echo");
    free(pedal->props.echo);
    pedal->props.echo = NULL;
}


static audio_sample_t * process_audio(   audio_sample_t * input,
                                                    int num_input_samples,
                                                    int * num_output_samples)
{
    return NULL;
}

void pedal_init_available_echo(void * _pedal)
{
    pedal_t * pedal = (pedal_t *) _pedal;
    pedal->PropScreen = NULL;        // properties screen
    pedal->normal_img = &ui_img_pedal_echo_png;         // normal image
    pedal->type = PEDAL_TYPE__ECHO;
    pedal->props.compressor = NULL,            // properties
    pedal->pedal_new_context_func_t = new_context;
    pedal->pedal_delete_context_func_t = delete_context;

    pedal->process_audio = process_audio;

}


