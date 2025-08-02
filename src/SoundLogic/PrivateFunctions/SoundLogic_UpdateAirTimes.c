/**
 * @file SoundLogic_FlightLoopCallback.c
 *
 * @brief
 *
 * @date 2025-08-01
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
#include "FsAccess/ComplexDataStructs/Datarefs/DataStructDefs/Datarefs_Struct.h"
#include "FsAccess/ComplexDataStructs/RefCon/DataStructDefs/RefCon_Struct.h"
#include "SoundLogic/ConstantDefs/SoundLogic_ConstantDefs.h"
#include "SoundLogic/InternalData/SoundLogic_InternalData.h"
#include "SoundLogic/PrivateFunctions/SoundLogic_PrivateFunctions.h"
#include "SoundLogic/PublicFunctions/SoundLogic_PublicFunctions.h"

int32_t SoundLogic_UpdateAirTimes(Datarefs *p_datarefs) {

  /* Get current sim time */
  double timeDrf = dr_getf(&(p_datarefs->sim.time.total_running_time_sec));

  /* Save the onground dataref in a buffer */
  int32_t onGroundDrfBuffer[SOUNDLOGIC_MAX_NUM_LANDING_GEARS];
  dr_getvi(&(p_datarefs->sim.flightmodel2.gear.on_ground),
           onGroundDrfBuffer,
           0,
           SOUNDLOGIC_MAX_NUM_LANDING_GEARS);

  /* For every gear */
  for (int32_t gearIdx = 0; gearIdx < SOUNDLOGIC_MAX_NUM_LANDING_GEARS;
       gearIdx++) {

    /* Update timestamps for on and off ground */
    int32_t thisGearOnGround = onGroundDrfBuffer[gearIdx];
    if (thisGearOnGround == 1) {
      sound_logic.landing_gear[gearIdx].onGroundTime = timeDrf;
    } else {
      sound_logic.landing_gear[gearIdx].offGroundTime = timeDrf;
    }

    if ((sound_logic.landing_gear[gearIdx].timeSinceLiftoff >
         SOUNDLOGIC_GEAR_DEBOUNCE_BUFFER_TIME) &&
        thisGearOnGround == 1) {
      sound_logic.d_touchdownTriggerData[gearIdx] = 1;
      sound_logic.d_liftoffTriggerData[gearIdx]   = 0;
    }

    if ((sound_logic.landing_gear[gearIdx].timeSinceTouchdown >
         SOUNDLOGIC_GEAR_DEBOUNCE_BUFFER_TIME) &&
        thisGearOnGround == 0) {
      sound_logic.d_liftoffTriggerData[gearIdx]   = 1;
      sound_logic.d_touchdownTriggerData[gearIdx] = 0;
    }

    sound_logic.landing_gear[gearIdx].timeSinceTouchdown =
        timeDrf - sound_logic.landing_gear[gearIdx].offGroundTime;
    sound_logic.landing_gear[gearIdx].timeSinceLiftoff =
        timeDrf - sound_logic.landing_gear[gearIdx].onGroundTime;
  }
  return B_TRUE;
}