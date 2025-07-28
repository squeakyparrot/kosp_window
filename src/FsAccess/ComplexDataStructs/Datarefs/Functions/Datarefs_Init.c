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
#include "FsAccess/ComplexDataStructs/Datarefs/DataStructDefs/Datarefs_Struct.h"
#include "FsAccess/DataStructDefs/FsAccess_Struct.h"

int32_t Datarefs_init(Datarefs *p_datarefs_inout) {

  /**
   * @brief Datarefs under the flightmodel/controls catagory.
   *
   */
  dr_find(&(p_datarefs_inout->controls.pitch_ratio),
          "sim/flightmodel2/controls/pitch_ratio");
  dr_find(&(p_datarefs_inout->controls.roll_ratio),
          "sim/flightmodel2/controls/roll_ratio");

  return B_TRUE;
}
