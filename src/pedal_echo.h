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

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "generic_props_ctl.h"

typedef struct pedal_props_echo_st
{
    // generic_props must be the very first definition in this structure
    generic_props_ctl_t generic_props; // delay and gain using generic sliders

    uint32_t *        samples;        // 32 bits: 16 for left, 16 for right
} pedal_props_echo_t;

void pedal_init_available_echo(void * pedal);


