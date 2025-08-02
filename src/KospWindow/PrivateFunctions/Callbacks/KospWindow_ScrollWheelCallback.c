/**
 * @file KospWindow_DrawCallback.c
 *
 * @brief
 *
 * @date 2025-07-26
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
#include "acfutils/math.h"

/* Custom Includes */
#include "FsAccess/ComplexDataStructs/RefCon/DataStructDefs/RefCon_Struct.h"
#include "KospWindow/ConstantDefs/KospWindow_ConstantDefs.h"
#include "KospWindow/DataStructDefs/KospWindow_Struct.h"
#include "KospWindow/PrivateFunctions/KospWindow_PrivateFunctions.h"

int KospWindow_ScrollWheelCallback(XPLMWindowID inWindowID,
                                   int          x,
                                   int          y,
                                   int          wheel,
                                   int          clicks,
                                   void        *inRefcon) {

  /* Extract ptr to KospWindow */
  VERIFY(inRefcon != NULL);
  KospWindow *p_kosp_window = ((RefCon *)inRefcon)->p_kosp_window;
  VERIFY(p_kosp_window != NULL);

  /* Get the x, y of the mouse action in Cairo (window) frame */
  int32_t left, top, right, bottom, window_w, window_h;
  XPLMGetWindowGeometry(inWindowID, &left, &top, &right, &bottom);
  x = x - left;
  y = top - y;

  if (y > KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y && y < KOSPWINDOW_SLIDER_END_Y) {
    if (p_kosp_window->pageNum == KOSPWINDOW_PAGE_1) {
      cJSON *p_sliders =
          cJSON_GetObjectItem(p_kosp_window->p_configJson, "slidersByDrfName");
      int32_t numDrfs = cJSON_GetArraySize(p_sliders);

      p_kosp_window->page1.sliderScroll =
          clampi(p_kosp_window->page1.sliderScroll - clicks,
                 0,
                 fmax(numDrfs - KOSPWINDOW_SLIDER_MAX_NUM_DISPLAYABLE_SLIDERS +
                          KOSPWINDOW_SLIDER_BOTTOM_BUFFER_SPACE,
                      0));
    } else if (p_kosp_window->pageNum == KOSPWINDOW_PAGE_3) {
      cJSON *p_switches =
          cJSON_GetObjectItem(p_kosp_window->p_configJson, "switchesByDrfName");
      int32_t numDrfs                   = cJSON_GetArraySize(p_switches);

      p_kosp_window->page3.sliderScroll = clampi(
          p_kosp_window->page3.sliderScroll - clicks,
          0,
          fmax(numDrfs - KOSPWINDOW_ON_OFF_SWITCH_MAX_NUM_DISPLAYABLE_SWITCHS +
                   KOSPWINDOW_ON_OFF_SWITCH_BOTTOM_BUFFER_SPACE,
               0));
    } else if (p_kosp_window->pageNum == KOSPWINDOW_PAGE_4) {
      p_kosp_window->page4.sliderScrollPx =
          clampi(p_kosp_window->page4.sliderScrollPx -
                     clicks * KOSPWINDOW_CHANGELOG_SCROLL_PIXELS_PER_CLICK,
                 0,
                 p_kosp_window->page4.sliderMaxScrollPx);
    }
  }

  return B_TRUE;
}