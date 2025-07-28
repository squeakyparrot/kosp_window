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

#ifndef H_FsAccess_Struct_H_
#define H_FsAccess_Struct_H_

/* C Library Includes */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* XPLM Includes */
#include "XPLMProcessing.h"

/* Acfutils includes */
#include "acfutils/font_utils.h"

/* Custom Includes */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FsAccess_Struct {

  /**
   * @brief       The parameters passed to X Plane about this plugin
   *              on init.
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  XPLMCreateFlightLoop_t flightLoopParams;

  /**
   * @details     The ID of the main flight loop called every frame.
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  XPLMFlightLoopID flightLoopId;
  /**
   * @details     The path to the plugin.
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  char pluginFilePath[256];

  /**
   * @details     An instance of the FreeType font library.
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  FT_Library ftLibrary;

} FsAccess;

#ifdef __cplusplus
}
#endif

#endif /* H_FsAccess_Struct_H_ */