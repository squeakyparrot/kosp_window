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

#ifndef H_FSACCESS_TOLISSDATAREFSSTRUCTSTRUCT_H_
#define H_FSACCESS_TOLISSDATAREFSSTRUCTSTRUCT_H_

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
 * @brief A struct for third party datarefs that belongs to ToLiss instead of
 *        us or XPLM.
 *
 *        The handles to the drfs are populated with its init function.
 *
 *        As an example sim/cockpit2/controls/flap_handle_deploy_ratio could be
 *        obtained with
 *        dr_getf(tolissDatarefs.sim.cockpit2.controls.flap_handle_deploy_ratio)
 */
typedef struct TolissDatarefs_Struct {

  /* Is the ToLiss datarefs populated and we have found them?
     if not we should avoid access to the drfs below at all times!
     Boolean */
  int32_t isInitialised;

  /* Datarefs */
  struct {

    /* Throttle Levers */
    struct {
      /* float ckpt/throttleLeft/anim */
      dr_t anim;
    } throttleLeft;
    struct {
      /* float ckpt/throttleLeft/anim */
      dr_t anim;
    } throttleRight;

  } ckpt;

} TolissDatarefs;

#ifdef __cplusplus
}
#endif

#endif /* H_FSACCESS_TOLISSDATAREFSSTRUCTSTRUCT_H_ */
