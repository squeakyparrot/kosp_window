/**
 * @file FsAccess_FlightLoopCallback.c
 *
 * @brief
 *
 * @date 2025-07-22
 *
 * @copyright KOSP Project 2025
 */

/* C Library Includes */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* XPLM Includes */

/* Acfutils includes */
#include "acfutils/assert.h"
#include "acfutils/dr.h"
#include "acfutils/log.h"

/* Custom Includes */
#include "FsAccess/ComplexDataStructs/RefCon/DataStructDefs/RefCon_Struct.h"
#include "SoundLogic/DataStructDefs/SoundLogic_Struct.h"
#include "Utils/Utils_RCFilters.h"

/* Refer the header for description */
int32_t SoundLogic_Init(SoundLogic *p_sound_logic, RefCon *refcon) {
  logMsg("SoundLogic_Init()");

  /* Create Datarefs */
  dr_create_vi(&(p_sound_logic->d_liftoffTrigger),
               p_sound_logic->d_liftoffTriggerData,
               SOUNDLOGIC_MAX_NUM_LANDING_GEARS,
               B_TRUE,
               "KOSP/liftoff_trigger");
  dr_create_vi(&(p_sound_logic->d_touchdownTrigger),
               p_sound_logic->d_touchdownTriggerData,
               SOUNDLOGIC_MAX_NUM_LANDING_GEARS,
               B_TRUE,
               "KOSP/touchdown_trigger");
  dr_create_f(&(p_sound_logic->d_flapStressFactor),
              &(p_sound_logic->d_flapStressFactorData),
              B_TRUE,
              "KOSP/flap_stress_factor");
  dr_create_f(&(p_sound_logic->d_throttleLeftHighPass),
              &(p_sound_logic->d_throttleLeftHighPassData),
              B_TRUE,
              "KOSP/throttleLeftHighPass");
  dr_create_f(&(p_sound_logic->d_throttleRightHighPass),
              &(p_sound_logic->d_throttleRightHighPassData),
              B_TRUE,
              "KOSP/throttleRightHighPass");

  /* Initialise Throttle Lever Filters */
  RCFilters_initHighPassFilter(
      &(p_sound_logic->throttleLeftHighPassFilter),
      SOUNDLOGIC_THROTTLE_LEVER_HIGH_PASS_TIMECONSTANT);
  RCFilters_initHighPassFilter(
      &(p_sound_logic->throttleRightHighPassFilter),
      SOUNDLOGIC_THROTTLE_LEVER_HIGH_PASS_TIMECONSTANT);

  return B_TRUE;
}