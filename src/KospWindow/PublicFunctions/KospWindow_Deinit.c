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
#include "acfutils/font_utils.h"
#include "acfutils/log.h"

/* Custom Includes */
#include "KospWindow/ConstantDefs/KospWindow_ConstantDefs.h"
#include "KospWindow/InternalData/KospWindow_InternalData.h"
#include "KospWindow/PrivateFunctions/KospWindow_PrivateFunctions.h"
#include "KospWindow/PublicFunctions/KospWindow_PublicFunctions.h"

/* Refer the header for description */
int32_t KospWindow_Deinit(KospWindow *p_kosp_window_inout) {
  logMsg("KospWindow_Deinit()");

  /* Delete all datarefs associated with buttons and sliders */
  cJSON *p_sliders = cJSON_GetObjectItem(p_kosp_window_inout->p_configJson,
                                         "slidersByDrfName");
  KospWindow_DeleteDrfs(p_sliders, p_kosp_window_inout->volumeRatioDrfs);
  cJSON *p_mixers = cJSON_GetObjectItem(p_kosp_window_inout->p_configJson,
                                        "mixerSlidersByDrfName");
  KospWindow_DeleteDrfs(p_mixers, p_kosp_window_inout->mixerRatioDrfs);
  cJSON *p_switches = cJSON_GetObjectItem(p_kosp_window_inout->p_configJson,
                                          "switchesByDrfName");
  KospWindow_DeleteDrfs(p_switches, p_kosp_window_inout->switchesRatioDrfs);

  /* End both the cairo renderer and uploader */
  if (p_kosp_window_inout->p_mtCairoRender != NULL) {
    mt_cairo_render_fini(p_kosp_window_inout->p_mtCairoRender);
  }
  if (p_kosp_window_inout->p_mtCairoUploader != NULL) {
    mt_cairo_uploader_fini(p_kosp_window_inout->p_mtCairoUploader);
  }

  /* Release cr font before freetype font, details see
   * font_utils_try_load_font() */

  /* Free all the fonts we loaded */
  if (p_kosp_window_inout->montserratLightCairoFontFace != NULL) {
    cairo_font_face_destroy(p_kosp_window_inout->montserratLightCairoFontFace);
  }
  if (p_kosp_window_inout->montserratLightFtFace != NULL) {
    FT_Done_Face(p_kosp_window_inout->montserratLightFtFace);
  }

  if (p_kosp_window_inout->montserratMediumCairoFontFace != NULL) {
    cairo_font_face_destroy(p_kosp_window_inout->montserratMediumCairoFontFace);
  }
  if (p_kosp_window_inout->montserratMediumFtFace != NULL) {
    FT_Done_Face(p_kosp_window_inout->montserratMediumFtFace);
  }

  if (p_kosp_window_inout->montserratRegularCairoFontFace != NULL) {
    cairo_font_face_destroy(
        p_kosp_window_inout->montserratRegularCairoFontFace);
  }
  if (p_kosp_window_inout->montserratRegularFtFace != NULL) {
    FT_Done_Face(p_kosp_window_inout->montserratRegularFtFace);
  }

  if (p_kosp_window_inout->robotoRegularCairoFontFace != NULL) {
    cairo_font_face_destroy(p_kosp_window_inout->robotoRegularCairoFontFace);
  }
  if (p_kosp_window_inout->robotoRegularFtFace != NULL) {
    FT_Done_Face(p_kosp_window_inout->robotoRegularFtFace);
  }

  if (p_kosp_window_inout->robotoSemiboldCairoFontFace != NULL) {
    cairo_font_face_destroy(p_kosp_window_inout->robotoSemiboldCairoFontFace);
  }
  if (p_kosp_window_inout->robotoSemiboldFtFace != NULL) {
    FT_Done_Face(p_kosp_window_inout->robotoSemiboldFtFace);
  }

  /* Erase our button from the plugin menu */
  KospWindow_DestroyMenu(p_kosp_window_inout);

  /* Destroy the window that we drew on */
  XPLMDestroyWindow(p_kosp_window_inout->windowId);

  /* Free the loaded json config */
  cJSON_Delete(kosp_window.p_configJson);
  cJSON_Delete(kosp_window.p_changeLogJson);

  return B_TRUE;
}