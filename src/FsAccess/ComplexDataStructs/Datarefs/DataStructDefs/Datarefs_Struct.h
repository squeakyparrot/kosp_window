/**
 * @file FsAccess_Struct.h
 *
 * @brief This file stores all properties related to interacting with X-Plane
 *        such as various IDs.
 *
 * @date 2025-07-23
 *
 * @copyright KOSP Project 2025
 */

#ifndef H_FSACCESS_DATAREFSSTRUCTSTRUCT_H_
#define H_FSACCESS_DATAREFSSTRUCTSTRUCT_H_

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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief A struct in the exact folder structure of how Laminar Research shaped
 *        their default datarefs.
 *
 *        The handles to the drfs are populated with its init function.
 *
 *        As an example sim/cockpit2/controls/flap_handle_deploy_ratio could be
 *        obtained with
 *        dr_getf(datarefs.sim.cockpit2.controls.flap_handle_deploy_ratio)
 *
 */
typedef struct Datarefs_Struct {

  struct {

    /* ######################################################
     * sim/flightmodel2
     * ###################################################### */

    struct {

      /* sim/flightmodel2/controls/... */
      struct {
        /* sim/flightmodel2/controls/pitch_ratio */
        dr_t pitch_ratio;

        /* sim/flightmodel2/controls/roll_ratio */
        dr_t roll_ratio;
      } controls;

      /* sim/flightmodel2/gear/... */
      struct {
        /* int[10] sim/flightmodel2/gear/on_ground */
        dr_t on_ground;
      } gear;

    } flightmodel2;

    /* ######################################################
     * sim/flightmodel
     * ###################################################### */
    struct {

      /* sim/flightmodel/position/... */
      struct {
        /*float sim/flightmodel/position/indicated_airspeed */
        dr_t indicated_airspeed;
      } position;

    } flightmodel;

    /* ######################################################
     * sim/time
     * ###################################################### */
    struct {

      /* float sim/time/total_running_time_sec */
      dr_t total_running_time_sec;

    } time;

    /* ######################################################
     * sim/cockpit2
     * ###################################################### */
    struct {

      /* sim/cockpit2/controls/... */
      struct {
        /* float sim/cockpit2/controls/flap_handle_deploy_ratio */
        dr_t flap_handle_deploy_ratio;
      } controls;

    } cockpit2;
  } sim;

} Datarefs;

#ifdef __cplusplus
}
#endif

#endif /* H_FSACCESS_DATAREFSSTRUCTSTRUCT_H_ */
