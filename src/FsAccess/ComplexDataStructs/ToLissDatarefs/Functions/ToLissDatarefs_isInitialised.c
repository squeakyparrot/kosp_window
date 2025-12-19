/**
 * @file ToLissDatarefs_isInitialised.c
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
int32_t ToLissDatarefs_isInitialised(void *inRefcon) {
  /* Sanity Check */
  VERIFY(inRefcon != NULL);
  VERIFY(((RefCon *)inRefcon)->p_tolissDatarefs != NULL);

  /* Return the flag contained in the struct */
  return (((RefCon *)inRefcon)->p_tolissDatarefs->isInitialised);
}
