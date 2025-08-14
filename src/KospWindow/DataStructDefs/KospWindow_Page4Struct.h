/**
 * @file KospWindow_Page3Struct.h
 *
 * @brief
 *
 * @date 2025-07-27
 *
 * @copyright KOSP Project 2025
 */

#ifndef H_KOSPWINDOW_PAGE4STRUCT_H_
#define H_KOSPWINDOW_PAGE4STRUCT_H_

/* C Library Includes */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* XPLM Includes */
#include "XPLMDisplay.h"

/* Acfutils includes */
#include "acfutils/mt_cairo_render.h"

/* cJSON Includes */
#include "cJSON.h"

/* Custom Includes */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief A struct that contains all properties of page 4 of the menu.
 *
 */
typedef struct KospWindow_Page4Struct {

  /**
   * @details     How much the slider has scrolled down in pixels.
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  int32_t sliderScrollPx;

  /**
   * @details     The smoothed out value of the above, automatically computed
   *              in the flight loop.
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  double sliderScrollSmoothPx;

  /**
   * @details     The max the slider can scroll down computed dynamically from
   *              the size of the json changelog.
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  int32_t sliderMaxScrollPx;

} KospWindow_Page4;

#ifdef __cplusplus
}
#endif

#endif /* H_KOSPWINDOW_PAGE4STRUCT_H_ */