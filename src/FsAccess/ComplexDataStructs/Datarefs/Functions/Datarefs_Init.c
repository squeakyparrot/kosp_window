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

/* Refer the header for description */
int32_t Datarefs_init(Datarefs *p_datarefs_inout) {
  logMsg("Datarefs_init()");

  /* ######################################################
   * sim/flightmodel2
   * ###################################################### */
  fdr_find(&(p_datarefs_inout->sim.flightmodel2.controls.pitch_ratio),
           "sim/flightmodel2/controls/pitch_ratio");
  fdr_find(&(p_datarefs_inout->sim.flightmodel2.controls.roll_ratio),
           "sim/flightmodel2/controls/roll_ratio");
  fdr_find(&(p_datarefs_inout->sim.flightmodel2.gear.on_ground),
           "sim/flightmodel2/gear/on_ground");

  /* ######################################################
   * sim/flightmodel
   * ###################################################### */
  fdr_find(&(p_datarefs_inout->sim.flightmodel.position.indicated_airspeed),
           "sim/flightmodel/position/indicated_airspeed");

  /* ######################################################
   * sim/time
   * ###################################################### */
  fdr_find(&(p_datarefs_inout->sim.time.total_running_time_sec),
           "sim/time/total_running_time_sec");

  /* ######################################################
   * sim/cockpit2
   * ###################################################### */
  fdr_find(&(p_datarefs_inout->sim.cockpit2.controls.flap_handle_deploy_ratio),
           "sim/cockpit2/controls/flap_handle_deploy_ratio");

  return B_TRUE;
}
