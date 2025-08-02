/**
 * @file SoundLogic_PublicFunctions.h
 *
 * @brief
 *
 * @date 2025-08-01
 *
 * @copyright KOSP Project 2025
 */

#ifndef SOUNDLOGIC_PUBLICFUNCTIONS_H_
#define SOUNDLOGIC_PUBLICFUNCTIONS_H_

/* C Library Includes */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int32_t SoundLogic_Init(SoundLogic *p_sound_logic, RefCon *refcon);

extern int32_t SoundLogic_Deinit(SoundLogic *p_sound_logic);

extern int32_t
SoundLogic_FlightLoopCallback(float inElapsedSinceLastCall,
                              float inElapsedTimeSinceLastFlightLoop,
                              int   inCounter,
                              void *inRefcon);

#ifdef __cplusplus
}
#endif

#endif /* SOUNDLOGIC_PUBLICFUNCTIONS_H_ */