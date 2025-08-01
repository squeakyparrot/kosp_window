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
        cJSON *p_thisDrf  = cJSON_GetArrayItem(p_sliders, sliderIdx);
        cJSON *p_drfName  = cJSON_GetObjectItem(p_thisDrf, "drfName");
        cJSON *p_min      = cJSON_GetObjectItem(p_thisDrf, "min");
        cJSON *p_max      = cJSON_GetObjectItem(p_thisDrf, "max");
        double valueToSet = clamp(fx_lin(x,
                                         KOSPWINDOW_SLIDER_START_X,
                                         p_min->valuedouble,
                                         KOSPWINDOW_SLIDER_END_X,
                                         p_max->valuedouble),
                                  p_min->valuedouble,
                                  p_max->valuedouble);

        KospWindow_SetSliderRatio(p_kosp_window,
                                  "slidersByDrfName",
                                  p_drfName->valuestring,
                                  "savedRatio",
                                  valueToSet);
      }
    }

    KospWindow_SetDrfs(p_sliders, p_kosp_window->volumeRatioDrfsData);

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
          }

          /* Move downwards to next slider */
          startY += KOSPWINDOW_SLIDER_Y_SPACING;
        }
      }
    } else if (inMouse == xplm_MouseUp) {
      /* Volume page */
      p_kosp_window->page1.isSliderAttached = B_FALSE;
    }
  }

  /* On Mixing Page */
  else if (p_kosp_window->pageNum == KOSPWINDOW_PAGE_2) {

    int32_t mixerSliderBarY;
    cJSON  *p_mixerSliders = cJSON_GetObjectItem(p_kosp_window->p_configJson,
                                                "mixerSlidersByDrfName");
    VERIFY(p_mixerSliders != NULL);

    for (int barIdx = 0; barIdx < 3; barIdx++) {
      if (p_kosp_window->page2.isSliderAttached == B_TRUE &&
          p_kosp_window->page2.attachedSlider == barIdx) {
        cJSON *p_thisDrf = cJSON_GetArrayItem(p_mixerSliders, barIdx);
        VERIFY(p_thisDrf != NULL);
        cJSON *p_drfName = cJSON_GetObjectItem(p_thisDrf, "drfName");
        VERIFY(p_drfName != NULL);
        cJSON *p_savedValue = cJSON_GetObjectItem(p_thisDrf, "savedValue");
        VERIFY(p_savedValue != NULL);

        double valueToSet =
            clamp(fx_lin_multi(y, numberYPosAndNumberInv, B_TRUE), -80, 10);
        /* Snapping */
        if (fabs(valueToSet) < 2.0) {
          valueToSet = 0;
        }

        KospWindow_SetSliderRatio(p_kosp_window,
                                  "mixerSlidersByDrfName",
                                  p_drfName->valuestring,
                                  "savedValue",
                                  valueToSet);

        logMsg("Set Value is %f", p_savedValue->valuedouble);
      }
    }

    if (inMouse == xplm_MouseDown) {
      /* Clicking on the content*/
      if (y > KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y &&
          y < KOSPWINDOW_SLIDER_END_Y) {
        for (int barIdx = 0; barIdx < 3; barIdx++) {
          cJSON *p_thisDrf = cJSON_GetArrayItem(p_mixerSliders, barIdx);
          VERIFY(p_thisDrf != NULL);
          cJSON *p_savedValue = cJSON_GetObjectItem(p_thisDrf, "savedValue");
          VERIFY(p_savedValue != NULL);
          int32_t sliderMiddleY = fx_lin_multi(
              p_savedValue->valuedouble, numberYPosAndNumber, B_FALSE);

          int32_t middleOfTheMixerBar =
              KOSPWINDOW_WINDOW_WIDTH / 2 +
              CAIRO_COLOUR_X_DIST_BTWN_BARS * (barIdx - 1);
          if ((x > middleOfTheMixerBar -
                       KOSPWINDOW_MIXER_SLIDER_SWITCH_WIDTH / 2) &&
              (x < middleOfTheMixerBar +
                       KOSPWINDOW_MIXER_SLIDER_SWITCH_WIDTH / 2) &&
              (y > sliderMiddleY - KOSPWINDOW_MIXER_SLIDER_SWITCH_HEIGHT / 2 &&
               y < sliderMiddleY + KOSPWINDOW_MIXER_SLIDER_SWITCH_HEIGHT / 2)) {
            p_kosp_window->page2.isSliderAttached = B_TRUE;
            p_kosp_window->page2.attachedSlider   = barIdx;
          }
        }
      }
    } else if (inMouse == xplm_MouseUp) {
      /* Mixing page */
      p_kosp_window->page2.isSliderAttached = B_FALSE;
    }
  }

  else if (p_kosp_window->pageNum == KOSPWINDOW_PAGE_3) {

    if (inMouse == xplm_MouseDown) {
      int32_t switchRowY;
      cJSON  *p_thisDrf;
      cJSON  *p_switches =
          cJSON_GetObjectItem(p_kosp_window->p_configJson, "switchesByDrfName");
      int32_t numDrfs = cJSON_GetArraySize(p_switches);

      for (int32_t switchIdx = 0; switchIdx < numDrfs; switchIdx++) {
        p_thisDrf           = cJSON_GetArrayItem(p_switches, switchIdx);
        cJSON *p_savedValue = cJSON_GetObjectItem(p_thisDrf, "saved_value");
        cJSON *p_drfName    = cJSON_GetObjectItem(p_thisDrf, "drfName");

        switchRowY          = KOSPWINDOW_ON_OFF_SWITCH_START_Y +
                     KOSPWINDOW_ON_OFF_SWITCH_Y_SPACING *
                         (switchIdx - p_kosp_window->page3.sliderScrollSmooth);

        if ((x > KOSPWINDOW_ON_OFF_SWITCH_START_X) &&
            (x < KOSPWINDOW_ON_OFF_SWITCH_START_X +
                     KOSPWINDOW_ON_OFF_SWITCH_WIDTH)) {
          if ((y > switchRowY + KOSPWINDOW_ON_OFF_SWITCH_Y_OFFSET) &&
              (y < switchRowY + KOSPWINDOW_ON_OFF_SWITCH_Y_OFFSET +
                       KOSPWINDOW_ON_OFF_SWITCH_HEIGHT)) {
            KospWindow_SetSliderRatio(p_kosp_window,
                                      "switchesByDrfName",
                                      p_drfName->valuestring,
                                      "saved_value",
                                      !(p_savedValue->valueint));
          }
        }
      }
    }
  }

  /* Write Json on Mouse Up */
  if (inMouse == xplm_MouseUp) {
    KospWindow_WriteConfJson(p_kosp_window, p_kosp_window->configPath);
  }

  return B_TRUE;
}