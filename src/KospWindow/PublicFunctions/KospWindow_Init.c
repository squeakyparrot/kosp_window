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
#include "acfutils/helpers.h"
#include "acfutils/log.h"

/* Custom Includes */
#include "FsAccess/InternalData/FsAccess_InternalData.h"
#include "KospWindow/ConstantDefs/KospWindow_ConstantDefs.h"
#include "KospWindow/InternalData/KospWindow_InternalData.h"
#include "KospWindow/PrivateFunctions/KospWindow_PrivateFunctions.h"
#include "KospWindow/PublicFunctions/KospWindow_PublicFunctions.h"

int32_t KospWindow_Init(KospWindow *p_kosp_window_inout) {

  VERIFY(p_kosp_window_inout != NULL);

  /* Fill in the window params */
  XPLMCreateWindow_t window_params = {
      .structSize               = sizeof(window_params),
      .left                     = 100,
      .top                      = 100 + KOSPWINDOW_WINDOW_HEIGHT,
      .right                    = 100 + KOSPWINDOW_WINDOW_WIDTH,
      .bottom                   = 100,
      .drawWindowFunc           = KospWindow_DrawCallback,
      .handleMouseClickFunc     = KospWindow_MouseCallback,
      .handleMouseWheelFunc     = KospWindow_ScrollWheelCallback,
      .refcon                   = &kosp_window,
      .decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle,
      .layer                    = xplm_WindowLayerFloatingWindows,

  };

  /* Create the window */
  p_kosp_window_inout->windowId = XPLMCreateWindowEx(&window_params);

  /* Set window looks */
  XPLMSetWindowResizingLimits(p_kosp_window_inout->windowId,
                              KOSPWINDOW_WINDOW_WIDTH,
                              KOSPWINDOW_WINDOW_HEIGHT,
                              KOSPWINDOW_WINDOW_WIDTH,
                              KOSPWINDOW_WINDOW_HEIGHT);
  XPLMSetWindowTitle(p_kosp_window_inout->windowId, "KOSP Project");
  XPLMSetWindowIsVisible(p_kosp_window_inout->windowId, B_TRUE);

  logMsg("KOSP Window Created");

  /* Call this or font_utils_try_load_font will crash */
  mt_cairo_render_glob_init(true);

  /* Fetch the font file. mkpathname returns a heap allocated string. */
  char *font_dir = mkpathname(fs_access.pluginFilePath,
                              KOSPWINDOW_ASSETS_DIR,
                              KOSPWINDOW_FONTS_DIR,
                              NULL);

  logMsg("Loading font from %s", font_dir);

  font_utils_try_load_font(
      font_dir,
      KOSPWINDOW_FONTS_MONTSERATT_LIGHT_NAME,
      fs_access.ftLibrary,
      &(p_kosp_window_inout->montserratLightFtFace),
      &(p_kosp_window_inout->montserratLightCairoFontFace));
  font_utils_try_load_font(
      font_dir,
      KOSPWINDOW_FONTS_MONTSERATT_MEDIUM_NAME,
      fs_access.ftLibrary,
      &(p_kosp_window_inout->montserratMediumFtFace),
      &(p_kosp_window_inout->montserratMediumCairoFontFace));
  font_utils_try_load_font(
      font_dir,
      KOSPWINDOW_FONTS_MONTSERATT_REGULAR_NAME,
      fs_access.ftLibrary,
      &(p_kosp_window_inout->montserratRegularFtFace),
      &(p_kosp_window_inout->montserratRegularCairoFontFace));
  font_utils_try_load_font(font_dir,
                           KOSPWINDOW_FONTS_ROBOTO_REGULAR_NAME,
                           fs_access.ftLibrary,
                           &(p_kosp_window_inout->robotoRegularFtFace),
                           &(p_kosp_window_inout->robotoRegularCairoFontFace));
  font_utils_try_load_font(font_dir,
                           KOSPWINDOW_FONTS_ROBOTO_SEMIBOLD_NAME,
                           fs_access.ftLibrary,
                           &(p_kosp_window_inout->robotoSemiboldFtFace),
                           &(p_kosp_window_inout->robotoSemiboldCairoFontFace));

  lacf_free(font_dir);

  /* Load Config */
  /* Fetch the font file. mkpathname returns a heap allocated string. */
  char *config_path_tmp = mkpathname(fs_access.pluginFilePath,
                                     KOSPWINDOW_CONFIG_DIR,
                                     KOSPWINDOW_USER_CONFIG_FILE_NAME,
                                     NULL);

  strlcpy(p_kosp_window_inout->configPath,
          config_path_tmp,
          sizeof(p_kosp_window_inout->configPath));
  lacf_free(config_path_tmp);

  KospWindow_LoadConfJson(p_kosp_window_inout, p_kosp_window_inout->configPath);

  /* Dummy test to write to it */
  KospWindow_SetSliderRatio(
      p_kosp_window_inout, "KOSP/master_vol_ratio_extrior", 0);

  return B_TRUE;
}