/**
 * @file FsAccess_Init.c
 *
 * @brief
 *
 * @date 2025-07-27
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
#include "acfutils/log.h"

/* Custom Includes */
#include "FsAccess/ComplexDataStructs/Datarefs/Functions/Datarefs_PublicFunctions.h"
#include "FsAccess/InternalData/FsAccess_InternalData.h"
#include "FsAccess/PrivateFunctions/FsAccess_PrivateFunctions.h"
#include "FsAccess/PublicFunctions/FsAccess_PublicFunctions.h"
#include "KospWindow/InternalData/KospWindow_InternalData.h"
#include "KospWindow/PublicFunctions/KospWindow_PublicFunctions.h"
#include "SoundLogic/InternalData/SoundLogic_InternalData.h"
#include "SoundLogic/PublicFunctions/SoundLogic_PublicFunctions.h"

int32_t FsAccess_Init() {

  VERIFY(FsAccess_GetPluginRootDir(fs_access.pluginFilePath));

  /* Init Freetype */
  VERIFY0(FT_Init_FreeType(&(fs_access.ftLibrary)));

  /* Construct Refcon */
  refcon.p_kosp_window = &kosp_window;
  refcon.p_sound_logic = &sound_logic;

  /* Init Flight Loop */
  fs_access.flightLoopParams =
      (XPLMCreateFlightLoop_t){.structSize = sizeof(XPLMCreateFlightLoop_t),
                               .phase = xplm_FlightLoop_Phase_AfterFlightModel,
                               .callbackFunc = FsAccess_FlightLoopCallback,
                               .refcon       = &refcon};
  fs_access.flightLoopId = XPLMCreateFlightLoop(&(fs_access.flightLoopParams));

  /* By default the flight loop is unscheduled. Schedule it. */
  XPLMScheduleFlightLoop(fs_access.flightLoopId, -1.0f, 0);

  /* Populate the datarefs struct by finding them. */
  VERIFY(Datarefs_init(&datarefs));

  /* Init modules one by one */
  VERIFY(KospWindow_Init(&kosp_window, &refcon));

  return B_TRUE;
}