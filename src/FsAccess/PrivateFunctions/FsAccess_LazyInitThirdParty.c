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
#include "FsAccess/ComplexDataStructs/RefCon/DataStructDefs/RefCon_Struct.h"
#include "FsAccess/ComplexDataStructs/ToLissDatarefs/Functions/ToLissDatarefs_Publicfunctions.h"
#include "FsAccess/PrivateFunctions/FsAccess_PrivateFunctions.h"

/* Refer the header for description */
int32_t FsAccess_LazyInitThirdParty(void *inRefcon) {
  VERIFY(inRefcon != NULL);

  /* Things that need lazy init */
  /* If it is not ready yet */
  if (ToLissDatarefs_isInitialised(inRefcon) != B_TRUE) {
    /* Check if it is ready now */
    ToLissDatarefs_lazyInit(inRefcon);
  }

  /* We are ok */
  return B_TRUE;
}