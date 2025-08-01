/**
 * @file KospWindow_Deinit.c
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
#include "acfutils/log.h"

/* Custom Includes */
#include "KospWindow/ConstantDefs/KospWindow_ConstantDefs.h"
#include "KospWindow/InternalData/KospWindow_InternalData.h"
#include "KospWindow/PrivateFunctions/KospWindow_PrivateFunctions.h"
#include "KospWindow/PublicFunctions/KospWindow_PublicFunctions.h"

int32_t KospWindow_Deinit(KospWindow *p_kosp_window_inout) {

  cJSON *p_sliders = cJSON_GetObjectItem(p_kosp_window_inout->p_configJson,
                                         "slidersByDrfName");
  KospWindow_DeleteDrfs(p_sliders, p_kosp_window_inout->volumeRatioDrfs);
  cJSON *p_mixers = cJSON_GetObjectItem(p_kosp_window_inout->p_configJson,
                                        "mixerSlidersByDrfName");
  KospWindow_DeleteDrfs(p_mixers, p_kosp_window_inout->mixerRatioDrfs);
  cJSON *p_switches = cJSON_GetObjectItem(p_kosp_window_inout->p_configJson,
                                          "switchesByDrfName");
  KospWindow_DeleteDrfs(p_switches, p_kosp_window_inout->switchesRatioDrfs);

  if (p_kosp_window_inout->p_mtCairoRender != NULL) {
    mt_cairo_render_fini(p_kosp_window_inout->p_mtCairoRender);
  }

  if (p_kosp_window_inout->p_mtCairoUploader != NULL) {
    mt_cairo_uploader_fini(p_kosp_window_inout->p_mtCairoUploader);
  }

  /* Release cr font before freetype font, details see
   * font_utils_try_load_font() */
  if (p_kosp_window_inout->montserratLightFtFace != NULL) {
    lacf_free(p_kosp_window_inout->montserratLightFtFace);
  }
  if (p_kosp_window_inout->montserratLightCairoFontFace != NULL) {
    lacf_free(p_kosp_window_inout->montserratLightCairoFontFace);
  }
  if (p_kosp_window_inout->montserratMediumFtFace != NULL) {
    lacf_free(p_kosp_window_inout->montserratMediumFtFace);
  }
  if (p_kosp_window_inout->montserratMediumCairoFontFace != NULL) {
    lacf_free(p_kosp_window_inout->montserratMediumCairoFontFace);
  }
  if (p_kosp_window_inout->montserratRegularFtFace != NULL) {
    lacf_free(p_kosp_window_inout->montserratRegularFtFace);
  }
  if (p_kosp_window_inout->montserratRegularCairoFontFace != NULL) {
    lacf_free(p_kosp_window_inout->montserratRegularCairoFontFace);
  }
  if (p_kosp_window_inout->robotoRegularFtFace != NULL) {
    lacf_free(p_kosp_window_inout->robotoRegularFtFace);
  }
  if (p_kosp_window_inout->robotoRegularCairoFontFace != NULL) {
    lacf_free(p_kosp_window_inout->robotoRegularCairoFontFace);
  }
  if (p_kosp_window_inout->robotoSemiboldFtFace != NULL) {
    lacf_free(p_kosp_window_inout->robotoSemiboldFtFace);
  }
  if (p_kosp_window_inout->robotoSemiboldCairoFontFace != NULL) {
    lacf_free(p_kosp_window_inout->robotoSemiboldCairoFontFace);
  }

  XPLMDestroyWindow(p_kosp_window_inout->windowId);

  /* Free the loaded json config */
  cJSON_Delete(kosp_window.p_configJson);

  logMsg("KOSP Window Destroyed");

  return B_TRUE;
}