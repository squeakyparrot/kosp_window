/**
 * @file FsAccess_FlightLoopCallback.c
 *
 * @brief
 *
 * @date 2025-07-22
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
#include "acfutils/assert.h"
#include "acfutils/log.h"

/* Custom Includes */
#include "FsAccess/ComplexDataStructs/RefCon/DataStructDefs/RefCon_Struct.h"
#include "KospWindow/ConstantDefs/KospWindow_ConstantDefs.h"
#include "KospWindow/PrivateFunctions/KospWindow_PrivateFunctions.h"
#include "KospWindow/PublicFunctions/KospWindow_PublicFunctions.h"
#include "Utils/Utils_AnimUtils.h"

int32_t KospWindow_FlightLoopCallback(float inElapsedSinceLastCall,
                                      float inElapsedTimeSinceLastFlightLoop,
                                      int   inCounter,
                                      void *inRefcon) {
  /* Extract ptr to KospWindow */
  VERIFY(inRefcon != NULL);
  KospWindow *p_kosp_window = ((RefCon *)inRefcon)->p_kosp_window;
  VERIFY(p_kosp_window != NULL);

  /* Update the smooth animation of the scroll. */
  p_kosp_window->page1.sliderScrollSmooth =
      AnimUtils_SetAnimValueNoLim(p_kosp_window->page1.sliderScrollSmooth,
                                  p_kosp_window->page1.sliderScroll,
                                  KOSPWINDOW_SLIDER_SCROLL_ANIM_SPEED,
                                  inElapsedSinceLastCall);
  p_kosp_window->page3.sliderScrollSmooth =
      AnimUtils_SetAnimValueNoLim(p_kosp_window->page3.sliderScrollSmooth,
                                  p_kosp_window->page3.sliderScroll,
                                  KOSPWINDOW_SLIDER_SCROLL_ANIM_SPEED,
                                  inElapsedSinceLastCall);
  p_kosp_window->page4.sliderScrollSmoothPx =
      AnimUtils_SetAnimValueNoLim(p_kosp_window->page4.sliderScrollSmoothPx,
                                  p_kosp_window->page4.sliderScrollPx,
                                  KOSPWINDOW_SLIDER_SCROLL_ANIM_SPEED,
                                  inElapsedSinceLastCall);

  return B_TRUE;
}