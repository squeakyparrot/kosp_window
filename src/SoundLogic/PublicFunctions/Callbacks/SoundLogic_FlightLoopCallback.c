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

/* Custom Includes */
#include "FsAccess/ComplexDataStructs/Datarefs/DataStructDefs/Datarefs_Struct.h"
#include "FsAccess/ComplexDataStructs/RefCon/DataStructDefs/RefCon_Struct.h"
#include "SoundLogic/ConstantDefs/SoundLogic_ConstantDefs.h"
#include "SoundLogic/PrivateFunctions/SoundLogic_PrivateFunctions.h"
#include "SoundLogic/PublicFunctions/SoundLogic_PublicFunctions.h"

/* Refer the header for description */
int32_t SoundLogic_FlightLoopCallback(float inElapsedSinceLastCall,
                                      float inElapsedTimeSinceLastFlightLoop,
                                      int   inCounter,
                                      void *inRefcon) {
  /* Extract ptr to SoundLogic */
  VERIFY(inRefcon != NULL);
  SoundLogic *p_sound_logic = ((RefCon *)inRefcon)->p_sound_logic;
  VERIFY(p_sound_logic != NULL);
  Datarefs *p_datarefs = ((RefCon *)inRefcon)->p_datarefs;
  VERIFY(p_datarefs != NULL);

  /* Do needed stuff in this module */
  SoundLogic_UpdateAirTimes(p_datarefs);
  SoundLogic_UpdateFlapStress(p_datarefs);

  return B_TRUE;
}