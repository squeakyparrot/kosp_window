/**
 * @file SoundLogic_Struct.h
 *
 * @brief
 *
 * @date 2025-08-01
 *
 * @copyright KOSP Project 2025
 */

#ifndef H_SOUNDLOGIC_STRUCT_H_
#define H_SOUNDLOGIC_STRUCT_H_

/* C Library Includes */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* XPLM Includes */
#include "acfutils/dr.h"

/* Acfutils includes */

/* Custom Includes */
#include "SoundLogic/ComplexDataStructs/LandingGear/LandingGear_Struct.h"
#include "SoundLogic/ConstantDefs/SoundLogic_ConstantDefs.h"
#include "Utils/Utils_RCFilters.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Structure that stores timestamps for each landing gear, and also the
 *        arrays of trigger datarefs created by this module.
 *
 */
typedef struct SoundLogic_Struct {

  /**
   * @details     Array of LandingGear structs each containing timing info
   */
  LandingGear landing_gear[SOUNDLOGIC_MAX_NUM_LANDING_GEARS];

  /**
   * @details     An array of all the datarefs that could possibly be created
   *              by the liftoff trigger
   */
  dr_t    d_liftoffTrigger;
  int32_t d_liftoffTriggerData[SOUNDLOGIC_MAX_NUM_LANDING_GEARS];

  /**
   * @details     An array of all the datarefs that could possibly be created
   *              by the liftoff trigger
   */
  dr_t    d_touchdownTrigger;
  int32_t d_touchdownTriggerData[SOUNDLOGIC_MAX_NUM_LANDING_GEARS];

  /**
   * @details     The dataref for flapStressFactor
   */
  dr_t  d_flapStressFactor;
  float d_flapStressFactorData;

  /**
   * @details     The dataref for throttleLeftHighPass
   */
  dr_t  d_throttleLeftHighPass;
  float d_throttleLeftHighPassData;

  /**
   * @details     The dataref for throttleRightHighPass
   */
  dr_t  d_throttleRightHighPass;
  float d_throttleRightHighPassData;

  /**
   * @details  Ptr to high pass filters for the left and right throttle levers
   *
   */
  HighPassFilter throttleLeftHighPassFilter;
  HighPassFilter throttleRightHighPassFilter;

} SoundLogic;

#ifdef __cplusplus
}
#endif

#endif /* H_SOUNDLOGIC_STRUCT_H_ */