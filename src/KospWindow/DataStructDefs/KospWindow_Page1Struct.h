/**
 * @file KospWindow_Page1Struct.h
 *
 * @brief
 *
 * @date 2025-07-27
 *
 * @copyright KOSP Project 2025
 */

#ifndef H_KOSPWINDOW_PAGE1STRUCT_H_
#define H_KOSPWINDOW_PAGE1STRUCT_H_

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

typedef struct KospWindow_Page1Struct {

  /**
   * @details     How much the slider has scrolled down. 0 is at the top, N+1
   *              is at the bottom (1 empty margin) when the page is at the
   *              bottom.
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  int32_t sliderScroll;

  /**
   * @details     The smoothed out value of the above, automatically computed
   *              in the flight loop.
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  double sliderScrollSmooth;

  /**
   * @details     The index in the order of the cJson structure of the sliders,
   *              whether any of them are attached.
   *              Only valid if the slider attached flag is true.
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  int32_t attachedSlider;

  /**
   * @details     Boolean flag to state if any of the sliders are attached.
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  int32_t isSliderAttached;

} KospWindow_Page1;

#ifdef __cplusplus
}
#endif

#endif /* H_KOSPWINDOW_PAGE1STRUCT_H_ */