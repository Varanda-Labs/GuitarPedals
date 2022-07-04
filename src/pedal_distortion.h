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

typedef struct pedal_props_distortion_st
{
    int     gain;
    int     clipping;
} pedal_props_distortion_t;

void pedal_init_available_distortion(void * pedal);


