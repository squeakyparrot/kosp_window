/**
 * @file KospWindow_Page2Struct.h
 *
 * @brief
 *
 * @date 2025-07-30
 *
 * @copyright KOSP Project 2025
 */
#ifndef H_KOSPWINDOW_PAGE2STRUCT_H_
#define H_KOSPWINDOW_PAGE2STRUCT_H_

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

typedef struct KospWindow_Page2Struct {

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

} KospWindow_Page2;

#ifdef __cplusplus
}
#endif

#endif /* H_KOSPWINDOW_PAGE2STRUCT_H_ */