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
#include "FsAccess/PublicFunctions/FsAccess_PublicFunctions.h"
#include "KospWindow/InternalData/KospWindow_InternalData.h"
#include "KospWindow/PublicFunctions/KospWindow_PublicFunctions.h"
#include "SoundLogic/InternalData/SoundLogic_InternalData.h"
#include "SoundLogic/PublicFunctions/SoundLogic_PublicFunctions.h"

int32_t FsAccess_Deinit() {

  /* Deinit Modules one by one */
  VERIFY(KospWindow_Deinit(&kosp_window));
  VERIFY(SoundLogic_Deinit(&sound_logic));

  logMsg("FT_Done_FreeType()");
  VERIFY0(FT_Done_FreeType(fs_access.ftLibrary));

  return B_TRUE;
}