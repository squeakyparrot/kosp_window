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

int32_t FsAccess_Deinit() {

  /* Deinit Window */
  KospWindow_Deinit(&kosp_window);

  FT_Done_FreeType(fs_access.ftLibrary);

  /* Deinit Logging */
  log_fini();

  return B_TRUE;
}