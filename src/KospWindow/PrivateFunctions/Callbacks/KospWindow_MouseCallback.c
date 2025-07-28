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
#include "KospWindow/ConstantDefs/KospWindow_ConstantDefs.h"
#include "KospWindow/DataStructDefs/KospWindow_Struct.h"
#include "KospWindow/PrivateFunctions/KospWindow_PrivateFunctions.h"

int KospWindow_MouseCallback(XPLMWindowID    inWindowID,
                             int             x,
                             int             y,
                             XPLMMouseStatus inMouse,
                             void           *inRefcon) {

  VERIFY(inRefcon != NULL);
  KospWindow *p_kosp_window = inRefcon;

  /* Get the x, y of the mouse action in Cairo (window) frame */
  int32_t left, top, right, bottom, window_w, window_h;
  XPLMGetWindowGeometry(inWindowID, &left, &top, &right, &bottom);
  x = x - left;
  y = top - y;

  /* Clicking anywhere on the menu bar */
  if (y > KOSPWINDOW_MENU_BAR_TOP_EDGE_Y &&
      y < KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y) {
    if (inMouse == xplm_MouseDown) {
      p_kosp_window->pageNum =
          (int32_t)x / (int32_t)(KOSPWINDOW_WINDOW_WIDTH / 4);
    }
  }

  /* On Volume Page */
  if (p_kosp_window->pageNum == KOSPWINDOW_PAGE_1) {

    /* Whenever there is mouse movement just move the slider */
    /* Get the position of the bar */
    int32_t sliderBarY;
    int32_t startY =
        KOSPWINDOW_SLIDER_START_Y -
        (p_kosp_window->page1.sliderScrollSmooth) * KOSPWINDOW_SLIDER_Y_SPACING;
    cJSON *p_sliders =
        cJSON_GetObjectItem(p_kosp_window->p_configJson, "slidersByDrfName");
    int32_t numDrfs = cJSON_GetArraySize(p_sliders);

    /* Set pos of slider */
    for (int32_t sliderIdx = 0; sliderIdx < numDrfs; sliderIdx++) {
      if (p_kosp_window->page1.isSliderAttached == B_TRUE &&
          p_kosp_window->page1.attachedSlider == sliderIdx) {
        cJSON *p_thisDrf    = cJSON_GetArrayItem(p_sliders, sliderIdx);
        cJSON *p_drfName    = cJSON_GetObjectItem(p_thisDrf, "drfName");
        cJSON *p_savedRatio = cJSON_GetObjectItem(p_thisDrf, "savedRatio");
        KospWindow_SetSliderRatio(p_kosp_window,
                                  p_drfName->valuestring,
                                  clamp(fx_lin(x,
                                               KOSPWINDOW_SLIDER_START_X,
                                               0.0,
                                               KOSPWINDOW_SLIDER_END_X,
                                               1.0),
                                        0.0,
                                        1.0));
      }
    }

    /* Register on down click once */
    if (inMouse == xplm_MouseDown) {

      /* Clicking on the content*/
      if (y > KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y &&
          y < KOSPWINDOW_SLIDER_END_Y) {

        /* For every bar */
        for (int32_t sliderIdx = 0; sliderIdx < numDrfs; sliderIdx++) {
          sliderBarY = startY + KOSPWINDOW_SLIDER_BAR_Y_OFFSET;

          /* If the user is clicking on the bar */
          if (y > sliderBarY - KOSPWINDOW_CLICKSPOT_MARGIN &&
              y < sliderBarY + KOSPWINDOW_CLICKSPOT_MARGIN &&
              x > KOSPWINDOW_SLIDER_START_X - KOSPWINDOW_CLICKSPOT_MARGIN &&
              x < KOSPWINDOW_SLIDER_END_X + KOSPWINDOW_CLICKSPOT_MARGIN) {

            /* Mark it as attached*/
            p_kosp_window->page1.isSliderAttached = B_TRUE;
            p_kosp_window->page1.attachedSlider   = sliderIdx;
            logMsg("Slider attached to %d", sliderIdx);
          }

          /* Move downwards to next slider */
          startY += KOSPWINDOW_SLIDER_Y_SPACING;
        }
      }
    } else if (inMouse == xplm_MouseUp) {
      /* Volume page */
      if (p_kosp_window->pageNum == KOSPWINDOW_PAGE_1) {
        p_kosp_window->page1.isSliderAttached = B_FALSE;
        logMsg("Slider detached");
      }
    }
  }

  return B_TRUE;
}