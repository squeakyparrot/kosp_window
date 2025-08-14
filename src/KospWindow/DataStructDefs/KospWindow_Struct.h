/**
 * @file FsAccess_Struct.h
 *
 * @brief This file stores all properties related to interacting with X-Plane
 *        such as various IDs.
 *
 * @date 2025-07-23
 *
 * @copyright KOSP Project 2025
 */

#ifndef H_KOSPWINDOW_STRUCT_H_
#define H_KOSPWINDOW_STRUCT_H_

/* C Library Includes */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* XPLM Includes */
#include "XPLMDisplay.h"
#include "XPLMMenus.h"

/* Acfutils includes */
#include "acfutils/dr.h"
#include "acfutils/mt_cairo_render.h"

/* cJSON Includes */
#include "cJSON.h"

/* Custom Includes */
#include "KospWindow/ConstantDefs/KospWindow_ConstantDefs.h"
#include "KospWindow/DataStructDefs/KospWindow_Page1Struct.h"
#include "KospWindow/DataStructDefs/KospWindow_Page2Struct.h"
#include "KospWindow/DataStructDefs/KospWindow_Page3Struct.h"
#include "KospWindow/DataStructDefs/KospWindow_Page4Struct.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief A struct that contains all properties of the menu including individual
 *        structs for each page's specific properties.
 *        An instance of this struct is all data about a window.
 *
 */
typedef struct KospWindow_Struct {

  /**
   * @details     The ID of the window
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  XPLMWindowID windowId;

  /**
   * @details     The index of our KOSP Menu under the plugins list
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  int32_t menuContainerIdx;

  /**
   * @details     A pointer to the uploader of the surface above.
   *              For more details see mt_cairo_render.c
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  int32_t pageNum;

  /**
   * @details     The index of our KOSP Menu under the plugins list
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  XPLMMenuID menuToggleWindowMenuId;

  /**
   * @details     A pointer to the surface of the mt_cairo_render
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  mt_cairo_render_t *p_mtCairoRender;

  /**
   * @details     A pointer to the uploader of the surface above.
   *              For more details see mt_cairo_render.c
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  mt_cairo_uploader_t *p_mtCairoUploader;

  /**
   * @details     The FreeType FontFace for Montseratt Light
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  FT_Face montserratLightFtFace;

  /**
   * @details     A pointer to the Cairo FontFace for Montseratt Light
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  cairo_font_face_t *montserratLightCairoFontFace;

  /**
   * @details     The FreeType FontFace for Montseratt Medium
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  FT_Face montserratMediumFtFace;

  /**
   * @details     A pointer to the Cairo FontFace for Montseratt Medium
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  cairo_font_face_t *montserratMediumCairoFontFace;

  /**
   * @details     The FreeType FontFace for Montseratt Regular
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  FT_Face montserratRegularFtFace;

  /**
   * @details     A pointer to the Cairo FontFace for Montseratt Regular
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  cairo_font_face_t *montserratRegularCairoFontFace;

  /**
   * @details     The FreeType FontFace for Roboto Regular
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  FT_Face robotoRegularFtFace;

  /**
   * @details     A pointer to the Cairo FontFace for Roboto Regular
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  cairo_font_face_t *robotoRegularCairoFontFace;

  /**
   * @details     The FreeType FontFace for Roboto Semibold
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  FT_Face robotoSemiboldFtFace;

  /**
   * @details     A pointer to the Cairo FontFace for Roboto Semibold
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  cairo_font_face_t *robotoSemiboldCairoFontFace;

  /**
   * @details     A pointer to the cJSON object that holds userconfig.json
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  cJSON *p_configJson;

  /**
   * @details     A pointer to the cJSON object that holds changelog.json
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  cJSON *p_changeLogJson;

  /**
   * @details     A buffer storing the path to userconfig.json
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  char configPath[256];

  /**
   * @details     A buffer storing the path to changelog.json
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  char changeLogPath[256];

  /**
   * @details     An array of all the datarefs that could possibly be created
   *              by the volume sliders on page 1.
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  dr_t  volumeRatioDrfs[KOSPWINDOW_MAX_NUM_VOLUME_DRFS];
  float volumeRatioDrfsData[KOSPWINDOW_MAX_NUM_VOLUME_DRFS];

  /**
   * @details     An array of all the datarefs that could possibly be created
   *              by the mixer sliders on page 2.
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  dr_t  mixerRatioDrfs[KOSPWINDOW_MAX_NUM_MIXER_DRFS];
  float mixerRatioDrfsData[KOSPWINDOW_MAX_NUM_MIXER_DRFS];

  /**
   * @details     An array of all the datarefs that could possibly be created
   *              by the switches on page 3.
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  dr_t    switchesRatioDrfs[KOSPWINDOW_MAX_NUM_SWITCHES_DRFS];
  int32_t switchesRatioDrfsData[KOSPWINDOW_MAX_NUM_SWITCHES_DRFS];

  /**
   * @details     A struct containing properties that only belongs to page 1.
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  KospWindow_Page1 page1;

  /**
   * @details     A struct containing properties that only belongs to page 2.
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  KospWindow_Page2 page2;

  /**
   * @details     A struct containing properties that only belongs to page 2.
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  KospWindow_Page3 page3;

  /**
   * @details     A struct containing properties that only belongs to page 2.
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  KospWindow_Page4 page4;

} KospWindow;

#ifdef __cplusplus
}
#endif

#endif /* H_KOSPWINDOW_STRUCT_H_ */