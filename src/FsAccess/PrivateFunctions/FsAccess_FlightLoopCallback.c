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
#include "acfutils/log.h"

/* Custom Includes */
#include "FsAccess/InternalData/FsAccess_InternalData.h"
#include "FsAccess/PrivateFunctions/FsAccess_PrivateFunctions.h"
#include "KospWindow/PublicFunctions/KospWindow_PublicFunctions.h"
#include "SoundLogic/PublicFunctions/SoundLogic_PublicFunctions.h"

/* Refer the header for description */
float FsAccess_FlightLoopCallback(float inElapsedSinceLastCall,
                                  float inElapsedTimeSinceLastFlightLoop,
                                  int   inCounter,
                                  void *inRefcon) {

  /* Call callbacks in each module one by one */
  KospWindow_FlightLoopCallback(inElapsedSinceLastCall,
                                inElapsedTimeSinceLastFlightLoop,
                                inCounter,
                                inRefcon);
  SoundLogic_FlightLoopCallback(inElapsedSinceLastCall,
                                inElapsedTimeSinceLastFlightLoop,
                                inCounter,
                                inRefcon);

  /* Call me next frame */
  return -1.0f;
}