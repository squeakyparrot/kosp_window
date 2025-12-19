/**
 * @file FsAccess_InternalData.c
 *
 * @brief
 *
 * @date 2025-07-23
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
#include <acfutils/dr.h>

/* Custom Includes */
#include "FsAccess/ComplexDataStructs/RefCon/DataStructDefs/RefCon_Struct.h"
#include "FsAccess/ComplexDataStructs/ToLissDatarefs/DataStructDefs/ToLissDatarefs_Struct.h"
#include "FsAccess/ComplexDataStructs/ToLissDatarefs/Functions/ToLissDatarefs_Publicfunctions.h"
#include "FsAccess/DataStructDefs/FsAccess_Struct.h"

/* Refer the header for description */
int32_t ToLissDatarefs_lazyInit(void *inRefcon) {
  /* Sanity Check */
  VERIFY(inRefcon != NULL);
  VERIFY(((RefCon *)inRefcon)->p_tolissDatarefs != NULL);
  logMsg("ToLissDatarefs_lazyInit()");

  /* Create a local flag to keep checking all datarefs init status */
  /* Preset the initialised flag to True */
  int32_t isInitialised = B_TRUE;

  /* ######################################################
   * ckpt/
   * ###################################################### */

  /* ToLiss Throttle Levers*/
  /* Check for success on every dr_find call */
  isInitialised &=
      dr_find(&(((RefCon *)inRefcon)->p_tolissDatarefs->ckpt.throttleLeft.anim),
              "ckpt/throttleLeft/anim");
  isInitialised &= dr_find(
      &(((RefCon *)inRefcon)->p_tolissDatarefs->ckpt.throttleRight.anim),
      "ckpt/throttleRight/anim");

  /* Update the global state of the struct with the local flag results */
  ((RefCon *)inRefcon)->p_tolissDatarefs->isInitialised = isInitialised;
  return B_TRUE;
}
