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

#ifndef PEDAL_COMPRESSOR_H
#define PEDAL_COMPRESSOR_H

typedef struct pedal_props_compressor_st
{
    int     level;
} pedal_props_compressor_t;

void pedal_init_available_compressor(void * pedal);


#endif // PEDAL_COMPRESSOR_H
