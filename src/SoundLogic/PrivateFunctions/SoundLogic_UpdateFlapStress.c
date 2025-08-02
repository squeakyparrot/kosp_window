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

int32_t SoundLogic_UpdateFlapStress(Datarefs *p_datarefs) {

  float airspeedDrf =
      dr_getf(&(p_datarefs->sim.flightmodel.position.indicated_airspeed));

  float laminarFlapDrf =
      dr_getf(&(p_datarefs->sim.cockpit2.controls.flap_handle_deploy_ratio));

  sound_logic.d_flapStressFactorData = airspeedDrf * laminarFlapDrf;
  return B_TRUE;
}