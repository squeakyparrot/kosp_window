/**
 * @file SoundLogic_PrivateFunctions.h
 *
 * @brief
 *
 * @date 2025-08-01
 *
 * @copyright KOSP Project 2025
 */

#ifndef SOUNDLOGIC_PRIVATEFUNCTIONS_H_
#define SOUNDLOGIC_PRIVATEFUNCTIONS_H_

/* C Library Includes */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "FsAccess/ComplexDataStructs/Datarefs/DataStructDefs/Datarefs_Struct.h"

/**
 * @brief Using the default datarefs, update the debounced versions of our
 *        own datarefs for cueing touchdown and liftoff sounds.
 *
 * @param p_datarefs Pointer to the default datarefs struct
 * @return int32_t
 */
extern int32_t SoundLogic_UpdateAirTimes(Datarefs *p_datarefs);

/**
 * @brief Using the default datarefs, update our own flap stress dataref for
 *        flaps sounds pitch.
 *
 * @param p_datarefs Pointer to the default datarefs struct
 * @return int32_t
 */
extern int32_t SoundLogic_UpdateFlapStress(Datarefs *p_datarefs);

/**
 * @brief Using the ToLiss datarefs, update our own throttle lever movement
 *        dataref after processing with a highpass filter.
 *        WARNING! Only call when the datarefs struct is actually initialised!
 *
 * @param p_tolissDatarefs Pointer to the toliss datarefs struct
 * @param dt essentially inElapsedSinceLastCall from the flight loop
 * @return int32_t
 */
int32_t SoundLogic_UpdateThrottleLevers(TolissDatarefs *p_tolissDatarefs,
                                        double          dt);

#ifdef __cplusplus
}
#endif

#endif /* SOUNDLOGIC_PRIVATEFUNCTIONS_H_ */