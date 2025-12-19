/**
 * @file SoundLogic_UpdateThrottleLevers.c
 *
 * @brief
 *
 * @date 2025-12-19
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
#include "acfutils/time.h"

/* Custom Includes */
#include "FsAccess/ComplexDataStructs/RefCon/DataStructDefs/RefCon_Struct.h"
#include "FsAccess/ComplexDataStructs/ToLissDatarefs/DataStructDefs/ToLissDatarefs_Struct.h"
#include "SoundLogic/ConstantDefs/SoundLogic_ConstantDefs.h"
#include "SoundLogic/InternalData/SoundLogic_InternalData.h"
#include "SoundLogic/PrivateFunctions/SoundLogic_PrivateFunctions.h"
#include "SoundLogic/PublicFunctions/SoundLogic_PublicFunctions.h"
#include "Utils/Utils_RCFilters.h"

/* Refer the header for description */
int32_t SoundLogic_UpdateThrottleLevers(TolissDatarefs *p_tolissDatarefs,
                                        double          dt) {
  /* Obtain Values */
  double throttleLeft =
      (double)dr_getf(&(p_tolissDatarefs->ckpt.throttleLeft.anim));
  double throttleRight =
      (double)dr_getf(&(p_tolissDatarefs->ckpt.throttleRight.anim));

  /* Do Filtering */
  double throttleLeftHighPass = RCFilters_updateHighPassFilter(
      &(sound_logic.throttleLeftHighPassFilter), throttleLeft, dt);
  double throttleRightHighPass = RCFilters_updateHighPassFilter(
      &(sound_logic.throttleRightHighPassFilter), throttleRight, dt);

  /* Update the datarefs */
  sound_logic.d_throttleLeftHighPassData  = (float)throttleLeftHighPass;
  sound_logic.d_throttleRightHighPassData = (float)throttleRightHighPass;
  return B_TRUE;
}