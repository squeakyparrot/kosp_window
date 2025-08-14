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

/**
 * @brief Initialise the SoundLogic Struct including creating datarefs
 * @param p_sound_logic Ptr to the SoundLogic Struct
 * @param refcon items passed into the callback
 * @return int32_t
 */
extern int32_t SoundLogic_Init(SoundLogic *p_sound_logic, RefCon *refcon);

/**
 * @brief Function to delete all the datarefs
 * @param p_sound_logic Ptr to the SoundLogic Struct
 * @return int32_t
 */
extern int32_t SoundLogic_Deinit(SoundLogic *p_sound_logic);

/**
 * @brief Run the update steps of this module when the flight loop is called.
 *        This updates the datarefs etc.
 *
 * @param inElapsedSinceLastCall See FsAccess_FlightLoopCallback
 * @param inElapsedTimeSinceLastFlightLoop  See FsAccess_FlightLoopCallback
 * @param inCounter  See FsAccess_FlightLoopCallback
 * @param inRefcon  See FsAccess_FlightLoopCallback
 * @return int32_t
 */
extern int32_t
SoundLogic_FlightLoopCallback(float inElapsedSinceLastCall,
                              float inElapsedTimeSinceLastFlightLoop,
                              int   inCounter,
                              void *inRefcon);

#ifdef __cplusplus
}
#endif

#endif /* SOUNDLOGIC_PUBLICFUNCTIONS_H_ */