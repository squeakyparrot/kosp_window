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

typedef struct Datarefs_Struct {

  /**
   * @brief Datarefs under the flightmodel/controls catagory.
   *
   */
  struct {
    /**
     * @brief sim/flightmodel2/controls/pitch_ratio
     *
     */
    dr_t pitch_ratio;

    /**
     * @brief sim/flightmodel2/controls/roll_ratio
     *
     */
    dr_t roll_ratio;
  } controls;

} Datarefs;

#ifdef __cplusplus
}
#endif

#endif /* H_FSACCESS_DATAREFSSTRUCTSTRUCT_H_ */
