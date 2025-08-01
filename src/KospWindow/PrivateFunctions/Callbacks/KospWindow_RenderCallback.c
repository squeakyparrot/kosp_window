/**
 * @file KospWindow_RenderCallback.c
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
#include "acfutils/cairo_utils.h"
#include "acfutils/geom.h"
#include "acfutils/log.h"
#include "acfutils/math.h"
#include "acfutils/mt_cairo_render.h"

/* Custom Includes */
#include "KospWindow/ConstantDefs/KospWindow_ConstantDefs.h"
#include "KospWindow/DataStructDefs/KospWindow_Struct.h"
#include "KospWindow/PrivateFunctions/KospWindow_PrivateFunctions.h"

void KospWindow_RenderCallback(cairo_t *cr,
                               unsigned window_w,
                               unsigned window_h,
                               void    *userinfo) {
  VERIFY(cr != NULL);
  VERIFY(userinfo != NULL);
  KospWindow *p_kosp_window = userinfo;

  cairo_text_extents_t extents;
  cairo_pattern_t     *pat;

  int32_t pageNum = p_kosp_window->pageNum;

  /* Background of frame colour to prevent leakage */
  cairo_rectangle(cr, 0, 0, KOSPWINDOW_WINDOW_WIDTH, KOSPWINDOW_WINDOW_HEIGHT);
  cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_MENU_FRAME);
  cairo_fill(cr);

  /* Margins of the top title background */
  cairo_utils_rounded_rect(cr,
                           0,
                           0,
                           KOSPWINDOW_WINDOW_WIDTH,
                           KOSPWINDOW_MENU_BAR_TOP_EDGE_Y,
                           KOSPWINDOW_MENU_ROUNDED_CORNER_OUTER_RADIUS);
  cairo_set_source_rgb(cr, CAIRO_COLOUR_MENU_MARGIN);
  cairo_fill(cr);

  /* Top title background */
  pat = cairo_pattern_create_linear(
      0.0, 0.0, 0.0, KOSPWINDOW_MENU_BAR_TOP_EDGE_Y);
  cairo_pattern_add_color_stop_rgba(pat, 0, CAIRO_COLOUR_MENU_BACKGROUND, 1);
  cairo_pattern_add_color_stop_rgba(
      pat, 1, CAIRO_COLOUR_MENU_BACKGROUND_GLOW, 1);
  cairo_utils_rounded_rect(
      cr,
      0 + KOSPWINDOW_MENU_MARGIN_WIDTH,
      0 + KOSPWINDOW_MENU_MARGIN_WIDTH,
      KOSPWINDOW_WINDOW_WIDTH - 2 * KOSPWINDOW_MENU_MARGIN_WIDTH,
      KOSPWINDOW_MENU_BAR_TOP_EDGE_Y - 2 * KOSPWINDOW_MENU_MARGIN_WIDTH,
      KOSPWINDOW_MENU_ROUNDED_CORNER_INNER_RADIUS);
  cairo_set_source(cr, pat);
  cairo_fill(cr);
  cairo_pattern_destroy(pat);

  /* Contents Background */
  pat = cairo_pattern_create_linear(0.0,
                                    KOSPWINDOW_MENU_BAR_TOP_EDGE_Y_GAPPED,
                                    0.0,
                                    KOSPWINDOW_WINDOW_HEIGHT -
                                        KOSPWINDOW_MENU_BAR_TOP_EDGE_Y_GAPPED);
  cairo_pattern_add_color_stop_rgba(pat, 0, CAIRO_COLOUR_MENU_BACKGROUND, 1);
  cairo_pattern_add_color_stop_rgba(
      pat, 0.5, CAIRO_COLOUR_MENU_BACKGROUND_GLOW, 1);
  cairo_pattern_add_color_stop_rgba(pat, 1, CAIRO_COLOUR_MENU_BACKGROUND, 1);
  cairo_utils_rounded_rect(cr,
                           0,
                           KOSPWINDOW_MENU_BAR_TOP_EDGE_Y_GAPPED,
                           KOSPWINDOW_WINDOW_WIDTH,
                           KOSPWINDOW_WINDOW_HEIGHT -
                               KOSPWINDOW_MENU_BAR_TOP_EDGE_Y_GAPPED,
                           KOSPWINDOW_MENU_ROUNDED_CORNER_OUTER_RADIUS);
  cairo_set_source(cr, pat);
  cairo_fill(cr);
  cairo_pattern_destroy(pat);

  /* Buttons */

  int32_t button_height = KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y -
                          KOSPWINDOW_MENU_BAR_TOP_EDGE_Y_GAPPED +
                          KOSPWINDOW_MENU_ROUNDED_CORNER_OUTER_RADIUS;
  double button_width =
      (double)KOSPWINDOW_WINDOW_WIDTH / (double)KOSPWINDOW_NUM_PAGES;

  /* Draw Button Background */
  pat = cairo_pattern_create_linear(0.0,
                                    KOSPWINDOW_MENU_BAR_TOP_EDGE_Y_GAPPED,
                                    0.0,
                                    KOSPWINDOW_MENU_BAR_TOP_EDGE_Y_GAPPED +
                                        button_height);
  cairo_pattern_add_color_stop_rgba(
      pat, 0, CAIRO_COLOUR_MENU_BUTTON_BACKGROUND, 1);
  cairo_pattern_add_color_stop_rgba(
      pat, 1, CAIRO_COLOUR_MENU_BUTTON_BACKGROUND_GLOW, 1);
  cairo_utils_rounded_rect(cr,
                           0,
                           KOSPWINDOW_MENU_BAR_TOP_EDGE_Y_GAPPED,
                           KOSPWINDOW_WINDOW_WIDTH,
                           button_height,
                           KOSPWINDOW_MENU_ROUNDED_CORNER_OUTER_RADIUS);
  cairo_set_source(cr, pat);
  cairo_fill(cr);
  cairo_pattern_destroy(pat);

  /* Draw Enabled Button */
  cairo_utils_rounded_rect(cr,
                           (pageNum)*button_width,
                           KOSPWINDOW_MENU_BAR_TOP_EDGE_Y_GAPPED,
                           button_width,
                           button_height,
                           KOSPWINDOW_MENU_ROUNDED_CORNER_OUTER_RADIUS);
  cairo_set_source_rgb(cr, CAIRO_COLOUR_MENU_BACKGROUND_SHADOW);
  cairo_fill(cr);
  pat = cairo_pattern_create_linear(0.0,
                                    KOSPWINDOW_MENU_BAR_TOP_EDGE_Y_GAPPED,
                                    0.0,
                                    KOSPWINDOW_MENU_BAR_TOP_EDGE_Y_GAPPED +
                                        button_height);
  cairo_pattern_add_color_stop_rgba(pat, 0, CAIRO_COLOUR_MENU_BACKGROUND, 1);
  cairo_pattern_add_color_stop_rgba(
      pat, 0.5, CAIRO_COLOUR_MENU_BACKGROUND_GLOW, 1);
  cairo_pattern_add_color_stop_rgba(pat, 1, CAIRO_COLOUR_MENU_BACKGROUND, 1);
  cairo_utils_rounded_rect(cr,
                           (pageNum)*button_width + 2,
                           KOSPWINDOW_MENU_BAR_TOP_EDGE_Y_GAPPED + 2,
                           button_width - 4,
                           button_height,
                           KOSPWINDOW_MENU_ROUNDED_CORNER_OUTER_RADIUS - 4);
  cairo_set_source(cr, pat);
  cairo_fill(cr);
  cairo_pattern_destroy(pat);

  /* Button separator */
  for (int32_t i = 1; i < KOSPWINDOW_NUM_PAGES; i++) {
    if ((pageNum == 0 && (i == 2 || i == 3)) || (pageNum == 1 && (i == 3)) ||
        (pageNum == 2 && (i == 1)) || (pageNum == 3 && (i == 1 || i == 1))) {
      cairo_move_to(
          cr, i * button_width, KOSPWINDOW_MENU_BAR_TOP_EDGE_Y_GAPPED + 6);
      cairo_line_to(
          cr, i * button_width, KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y - 6);
      cairo_set_line_width(cr, 2);
      cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_MENU_FRAME);
      cairo_stroke(cr);
    }
  }

  /* Button Text */
  char *buttons_text[] = {"Volume", "Balance", "Options", "Version"};
  cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_WHITE);
  cairo_set_font_face(cr, p_kosp_window->montserratMediumCairoFontFace);
  cairo_set_font_size(cr, 20.0);
  int32_t textOffset = 0;
  for (int32_t i = 0; i < KOSPWINDOW_NUM_PAGES; i++) {
    if (i == 1) {
      textOffset = -3;
    }
    cairo_text_extents(cr, buttons_text[i], &extents);
    cairo_move_to(cr,
                  i * button_width + 10.0 + textOffset,
                  (double)(KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y +
                           KOSPWINDOW_MENU_BAR_TOP_EDGE_Y_GAPPED) /
                          2.0 +
                      8.0);
    cairo_show_text(cr, buttons_text[i]);
  }

  /* Cover up */
  pat = cairo_pattern_create_linear(0.0,
                                    KOSPWINDOW_MENU_BAR_TOP_EDGE_Y_GAPPED,
                                    0.0,
                                    KOSPWINDOW_WINDOW_HEIGHT -
                                        KOSPWINDOW_MENU_BAR_TOP_EDGE_Y_GAPPED);
  cairo_pattern_add_color_stop_rgba(pat, 0, CAIRO_COLOUR_MENU_BACKGROUND, 1);
  cairo_pattern_add_color_stop_rgba(
      pat, 0.5, CAIRO_COLOUR_MENU_BACKGROUND_GLOW, 1);
  cairo_pattern_add_color_stop_rgba(pat, 1, CAIRO_COLOUR_MENU_BACKGROUND, 1);
  cairo_rectangle(cr,
                  0,
                  KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y,
                  KOSPWINDOW_WINDOW_WIDTH,
                  KOSPWINDOW_WINDOW_HEIGHT - KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y -
                      KOSPWINDOW_MENU_ROUNDED_CORNER_OUTER_RADIUS);
  cairo_set_source(cr, pat);
  cairo_fill(cr);
  cairo_pattern_destroy(pat);

  /* Menu separator */
  cairo_move_to(cr, 0, KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y);
  cairo_line_to(cr, KOSPWINDOW_WINDOW_WIDTH, KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y);
  cairo_set_line_width(cr, 1);
  cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_MENU_FRAME);
  cairo_stroke(cr);

  /* Title */
  cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_WHITE);

  cairo_set_font_face(cr, p_kosp_window->montserratLightCairoFontFace);
  cairo_set_font_size(cr, 65.0);
  cairo_text_extents(cr, "KOSP", &extents);
  int32_t kosp_text_width = extents.width;
  cairo_move_to(cr,
                KOSPWINDOW_WINDOW_WIDTH / 2 - (kosp_text_width / 2),
                KOSPWINDOW_TITLE_BIG_TEXT_Y);
  cairo_show_text(cr, "KOSP");

  cairo_set_font_size(cr, 18.0);
  char *letters = "PROJECT";
  char  letter_str[2];
  cairo_set_font_face(cr, p_kosp_window->montserratMediumCairoFontFace);
  for (int32_t i = 0; i < 7; i++) {
    int32_t offset = 6;
    if (i == 3) {
      offset = 7;
    }
    letter_str[0] = letters[i];
    letter_str[1] = '\0'; // Null-terminate the string
    cairo_text_extents(cr, letter_str, &extents);
    cairo_move_to(cr,
                  (double)(KOSPWINDOW_WINDOW_WIDTH - kosp_text_width) / 2.0 +
                      i * ((double)kosp_text_width / 7.0 + 2.0) -
                      extents.x_bearing + offset,
                  KOSPWINDOW_TITLE_SMALL_TEXT_Y);
    cairo_show_text(cr, letter_str);
  }

  if (pageNum == KOSPWINDOW_PAGE_1) {

    /* Clip region with the sliders */
    cairo_rectangle(cr,
                    0,
                    KOSPWINDOW_SLIDER_START_Y -
                        KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS,
                    KOSPWINDOW_WINDOW_WIDTH,
                    KOSPWINDOW_SLIDER_MAX_NUM_DISPLAYABLE_SLIDERS *
                            KOSPWINDOW_SLIDER_Y_SPACING +
                        KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS);
    cairo_clip(cr);

    int32_t startY =
        KOSPWINDOW_SLIDER_START_Y -
        (p_kosp_window->page1.sliderScrollSmooth) * KOSPWINDOW_SLIDER_Y_SPACING;

    cJSON *p_sliders =
        cJSON_GetObjectItem(p_kosp_window->p_configJson, "slidersByDrfName");
    cJSON  *p_thisDrf;
    int32_t numDrfs = cJSON_GetArraySize(p_sliders);

    for (int32_t sliderIdx = 0; sliderIdx < numDrfs; sliderIdx++) {
      p_thisDrf           = cJSON_GetArrayItem(p_sliders, sliderIdx);

      int32_t sliderTextY = startY + KOSPWINDOW_SLIDER_TEXT_Y_OFFSET;
      int32_t sliderBarY  = startY + KOSPWINDOW_SLIDER_BAR_Y_OFFSET;

      /* Lookup name by drf name */
      cJSON *p_min         = cJSON_GetObjectItem(p_thisDrf, "min");
      cJSON *p_max         = cJSON_GetObjectItem(p_thisDrf, "max");
      cJSON *p_savedRatio  = cJSON_GetObjectItem(p_thisDrf, "savedRatio");
      cJSON *p_displayName = cJSON_GetObjectItem(p_thisDrf, "displayName");
      cJSON *p_displayMultiplier =
          cJSON_GetObjectItem(p_thisDrf, "displayMultiplier");

      double barRatio = fx_lin(p_savedRatio->valuedouble,
                               p_min->valuedouble,
                               0.0,
                               p_max->valuedouble,
                               1.0);
      double barRatioIncreaseX =
          (KOSPWINDOW_SLIDER_END_X - KOSPWINDOW_SLIDER_START_X) * barRatio;
      double barKnobX = barRatioIncreaseX + KOSPWINDOW_SLIDER_START_X;
      char   ratioString[10];
      snprintf(ratioString,
               10,
               "%d",
               (int32_t)(barRatio * (p_max->valuedouble - p_min->valuedouble) *
                         (p_displayMultiplier->valuedouble)));

      /* Description Text */
      cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_WHITE);
      cairo_set_font_face(cr, p_kosp_window->montserratMediumCairoFontFace);
      cairo_set_font_size(cr, 21.0);
      cairo_text_extents(cr, p_displayName->valuestring, &extents);
      cairo_move_to(cr, KOSPWINDOW_SLIDER_START_X, sliderTextY);
      cairo_show_text(cr, p_displayName->valuestring);

      /* Ratio Text */
      cairo_text_extents(cr, ratioString, &extents);
      cairo_move_to(cr, KOSPWINDOW_SLIDER_END_X - extents.width, sliderTextY);
      cairo_show_text(cr, ratioString);

      /* Slider Bar */
      cairo_utils_rounded_rect(cr,
                               KOSPWINDOW_SLIDER_START_X,
                               sliderBarY,
                               barRatioIncreaseX,
                               KOSPWINDOW_SLIDER_BAR_THICKNESS,
                               KOSPWINDOW_SLIDER_BAR_THICKNESS / 2);
      cairo_set_source_rgb(cr, CAIRO_COLOUR_SLIDER_BAR_GREY);
      cairo_fill(cr);

      cairo_move_to(cr,
                    KOSPWINDOW_SLIDER_START_X +
                        KOSPWINDOW_SLIDER_BAR_THICKNESS / 2,
                    sliderBarY + KOSPWINDOW_SLIDER_BAR_THICKNESS / 2);
      cairo_line_to(cr,
                    KOSPWINDOW_SLIDER_START_X + barRatioIncreaseX -
                        KOSPWINDOW_SLIDER_BAR_THICKNESS / 2,
                    sliderBarY + KOSPWINDOW_SLIDER_BAR_THICKNESS / 2);
      cairo_set_line_width(cr, 1);
      cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_MENU_FRAME);
      cairo_stroke(cr);

      cairo_utils_rounded_rect(
          cr,
          KOSPWINDOW_SLIDER_START_X + barRatioIncreaseX,
          sliderBarY,
          (KOSPWINDOW_SLIDER_END_X - KOSPWINDOW_SLIDER_START_X) *
              (1 - barRatio),
          KOSPWINDOW_SLIDER_BAR_THICKNESS,
          KOSPWINDOW_SLIDER_BAR_THICKNESS / 2);
      cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_MENU_FRAME);
      cairo_fill(cr);

      cairo_move_to(cr,
                    KOSPWINDOW_SLIDER_START_X + barRatioIncreaseX +
                        KOSPWINDOW_SLIDER_BAR_THICKNESS / 2,
                    sliderBarY + KOSPWINDOW_SLIDER_BAR_THICKNESS / 2);
      cairo_line_to(cr,
                    KOSPWINDOW_SLIDER_END_X -
                        KOSPWINDOW_SLIDER_BAR_THICKNESS / 2,
                    sliderBarY + KOSPWINDOW_SLIDER_BAR_THICKNESS / 2);
      cairo_set_line_width(cr, 1);
      cairo_set_source_rgb(cr, CAIRO_COLOUR_MENU_BACKGROUND);
      cairo_stroke(cr);

      /* Slider Ball */
      pat = cairo_pattern_create_radial(barKnobX,
                                        sliderBarY,
                                        KOSPWINDOW_SLIDER_BALL_RADIUS,
                                        barKnobX,
                                        sliderBarY,
                                        KOSPWINDOW_SLIDER_BALL_RADIUS +
                                            KOSPWINDOW_SLIDER_BALL_SHADOW_SIZE);
      cairo_pattern_add_color_stop_rgba(
          pat, 0, CAIRO_COLOUR_MENU_BUTTON_BACKGROUND_GLOW, 1);
      cairo_pattern_add_color_stop_rgba(pat, 1, CAIRO_COLOUR_XPLANE_BLACK, 0);
      cairo_set_source(cr, pat);
      cairo_arc(cr,
                barKnobX,
                sliderBarY,
                KOSPWINDOW_SLIDER_BALL_RADIUS +
                    KOSPWINDOW_SLIDER_BALL_SHADOW_SIZE,
                0,
                2 * M_PI);
      cairo_fill(cr);
      cairo_pattern_destroy(pat);

      cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_WHITE);
      cairo_arc(cr,
                barKnobX,
                sliderBarY,
                KOSPWINDOW_SLIDER_BALL_INNER_RING_RADIUS,
                0,
                2 * M_PI);
      cairo_fill(cr);

      cairo_set_source_rgb(cr, CAIRO_COLOUR_MENU_BUTTON_BACKGROUND_GLOW);
      cairo_arc(cr,
                barKnobX,
                sliderBarY,
                KOSPWINDOW_SLIDER_BALL_INNER_RING_RADIUS - 2,
                0,
                2 * M_PI);
      cairo_fill(cr);

      /* Move downwards to next slider */
      startY += KOSPWINDOW_SLIDER_Y_SPACING;
    }

    cairo_reset_clip(cr);

    /* Top Slider Fading Strip */
    pat = cairo_pattern_create_linear(
        0.0,
        KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y,
        0.0,
        KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y +
            KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS);
    cairo_pattern_add_color_stop_rgba(pat, 0, CAIRO_COLOUR_MENU_BACKGROUND, 1);
    cairo_pattern_add_color_stop_rgba(
        pat, 0.2, CAIRO_COLOUR_MENU_BACKGROUND, 1);
    cairo_pattern_add_color_stop_rgba(pat, 1, CAIRO_COLOUR_MENU_BACKGROUND, 0);
    cairo_rectangle(cr,
                    0,
                    KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y,
                    KOSPWINDOW_WINDOW_WIDTH,
                    KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS);
    cairo_set_source(cr, pat);
    cairo_fill(cr);
    cairo_pattern_destroy(pat);

    /* Bottom Slider Fading Strip */
    pat = cairo_pattern_create_linear(
        0.0,
        KOSPWINDOW_SLIDER_START_Y +
            KOSPWINDOW_SLIDER_MAX_NUM_DISPLAYABLE_SLIDERS *
                KOSPWINDOW_SLIDER_Y_SPACING,
        0.0,
        KOSPWINDOW_SLIDER_START_Y +
            KOSPWINDOW_SLIDER_MAX_NUM_DISPLAYABLE_SLIDERS *
                KOSPWINDOW_SLIDER_Y_SPACING -
            KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS);
    cairo_pattern_add_color_stop_rgba(pat, 0, CAIRO_COLOUR_MENU_BACKGROUND, 1);
    cairo_pattern_add_color_stop_rgba(pat, 1, CAIRO_COLOUR_MENU_BACKGROUND, 0);
    cairo_rectangle(cr,
                    0,
                    KOSPWINDOW_SLIDER_START_Y +
                        KOSPWINDOW_SLIDER_MAX_NUM_DISPLAYABLE_SLIDERS *
                            KOSPWINDOW_SLIDER_Y_SPACING -
                        KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS,
                    KOSPWINDOW_WINDOW_WIDTH,
                    KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS);
    cairo_set_source(cr, pat);
    cairo_fill(cr);
    cairo_pattern_destroy(pat);

    /* Bottom separator of the sliders */
    cairo_utils_rounded_rect(cr,
                             KOSPWINDOW_BOTTOM_SEPARATOR_X_MARGIN,
                             KOSPWINDOW_BOTTOM_SEPARATOR_Y,
                             KOSPWINDOW_WINDOW_WIDTH -
                                 KOSPWINDOW_BOTTOM_SEPARATOR_X_MARGIN * 2,
                             2,
                             1);
    cairo_set_source_rgb(cr, CAIRO_COLOUR_MENU_BUTTON_BACKGROUND_GLOW);
    cairo_fill(cr);

    /* Scroll bar */
    double scrollBarRatio =
        (p_kosp_window->page1.sliderScrollSmooth) /
        fmax((double)(numDrfs) + (double)KOSPWINDOW_SLIDER_BOTTOM_BUFFER_SPACE -
                 (double)KOSPWINDOW_SLIDER_MAX_NUM_DISPLAYABLE_SLIDERS,
             1.0);

    cairo_utils_rounded_rect(cr,
                             KOSPWINDOW_SLIDER_SCROLL_BAR_X,
                             KOSPWINDOW_SLIDER_SCROLL_BAR_START_Y,
                             4,
                             KOSPWINDOW_SLIDER_SCROLL_BAR_END_Y -
                                 KOSPWINDOW_SLIDER_SCROLL_BAR_START_Y,
                             2);
    cairo_set_source_rgb(cr, CAIRO_COLOUR_MENU_BUTTON_BACKGROUND_GLOW);
    cairo_fill(cr);

    cairo_utils_rounded_rect(
        cr,
        KOSPWINDOW_SLIDER_SCROLL_BAR_X,
        KOSPWINDOW_SLIDER_SCROLL_BAR_START_Y +
            fx_lin(scrollBarRatio,
                   0,
                   0,
                   1,
                   (KOSPWINDOW_SLIDER_SCROLL_BAR_END_Y -
                    KOSPWINDOW_SLIDER_SCROLL_BAR_START_Y) -
                       KOSPWINDOW_SLIDER_SCROLL_BAR_LENGTH),
        4,
        KOSPWINDOW_SLIDER_SCROLL_BAR_LENGTH,
        2);
    cairo_set_source_rgb(cr, CAIRO_COLOUR_SLIDER_BAR_GREY);
    cairo_fill(cr);

    /* Bottom Text */
    cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_WHITE);
    cairo_set_font_face(cr, p_kosp_window->montserratMediumCairoFontFace);
    cairo_set_font_size(cr, 21.0);
    cairo_move_to(cr, KOSPWINDOW_SLIDER_START_X, KOSPWINDOW_BOTTOM_TEXT_Y);
    cairo_show_text(cr, "Use these over the ISCS.");

    cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_WHITE);
    cairo_set_font_face(cr, p_kosp_window->montserratMediumCairoFontFace);
    cairo_set_font_size(cr, 21.0);
    cairo_move_to(
        cr, KOSPWINDOW_SLIDER_START_X, KOSPWINDOW_BOTTOM_TEXT_Y + 30.0);
    cairo_show_text(cr, "Scroll down for more sliders.");
  } else if (pageNum == KOSPWINDOW_PAGE_2) {

    int32_t mixerSliderBarY;
    cJSON  *p_mixerSliders = cJSON_GetObjectItem(p_kosp_window->p_configJson,
                                                "mixerSlidersByDrfName");

    for (int barIdx = 0; barIdx < 3; barIdx++) {

      int32_t middleOfTheMixerBar =
          KOSPWINDOW_WINDOW_WIDTH / 2 +
          CAIRO_COLOUR_X_DIST_BTWN_BARS * (barIdx - 1);

      /* Rheostat Bar */
      cairo_utils_rounded_rect(
          cr,
          middleOfTheMixerBar - KOSPWINDOW_MIXER_SLIDER_WIDTH / 2 - 1,
          KOSPWINDOW_MIXER_SLIDER_START_Y - 1,
          KOSPWINDOW_MIXER_SLIDER_WIDTH + 2,
          KOSPWINDOW_MIXER_SLIDER_END_Y - KOSPWINDOW_MIXER_SLIDER_START_Y + 1,
          KOSPWINDOW_MIXER_SLIDER_WIDTH / 2);
      cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_BLACK);
      cairo_fill(cr);

      cairo_utils_rounded_rect(
          cr,
          middleOfTheMixerBar - KOSPWINDOW_MIXER_SLIDER_WIDTH / 2,
          KOSPWINDOW_MIXER_SLIDER_START_Y,
          KOSPWINDOW_MIXER_SLIDER_WIDTH,
          KOSPWINDOW_MIXER_SLIDER_END_Y - KOSPWINDOW_MIXER_SLIDER_START_Y,
          KOSPWINDOW_MIXER_SLIDER_WIDTH / 2);
      cairo_set_source_rgb(cr, CAIRO_COLOUR_MENU_BUTTON_BACKGROUND_GLOW);
      cairo_fill(cr);

      pat = cairo_pattern_create_linear(
          middleOfTheMixerBar - KOSPWINDOW_MIXER_SLIDER_WIDTH / 2,
          0.0,
          middleOfTheMixerBar + KOSPWINDOW_MIXER_SLIDER_WIDTH / 2,
          0.0);

      switch (barIdx) {
      case 0:
        cairo_pattern_add_color_stop_rgba(
            pat, 0, CAIRO_COLOUR_SLIDER_ACCENT_RED, 0);
        cairo_pattern_add_color_stop_rgba(
            pat, 0.3, CAIRO_COLOUR_SLIDER_ACCENT_RED, 0);
        cairo_pattern_add_color_stop_rgba(
            pat, 1, CAIRO_COLOUR_SLIDER_ACCENT_RED, 1);
        break;
      case 1:
        cairo_pattern_add_color_stop_rgba(
            pat, 0, CAIRO_COLOUR_SLIDER_ACCENT_YELLOW, 0);
        cairo_pattern_add_color_stop_rgba(
            pat, 0.3, CAIRO_COLOUR_SLIDER_ACCENT_YELLOW, 0);
        cairo_pattern_add_color_stop_rgba(
            pat, 1, CAIRO_COLOUR_SLIDER_ACCENT_YELLOW, 1);
        break;
      case 2:
        cairo_pattern_add_color_stop_rgba(
            pat, 0, CAIRO_COLOUR_SLIDER_ACCENT_GREEN, 0);
        cairo_pattern_add_color_stop_rgba(
            pat, 0.3, CAIRO_COLOUR_SLIDER_ACCENT_GREEN, 0);
        cairo_pattern_add_color_stop_rgba(
            pat, 1, CAIRO_COLOUR_SLIDER_ACCENT_GREEN, 1);
        break;
      }

      cairo_utils_rounded_rect(
          cr,
          middleOfTheMixerBar - KOSPWINDOW_MIXER_SLIDER_WIDTH / 2,
          KOSPWINDOW_MIXER_SLIDER_START_Y,
          KOSPWINDOW_MIXER_SLIDER_WIDTH,
          KOSPWINDOW_MIXER_SLIDER_END_Y - KOSPWINDOW_MIXER_SLIDER_START_Y,
          KOSPWINDOW_MIXER_SLIDER_WIDTH / 2);
      cairo_set_source(cr, pat);
      cairo_fill(cr);
      cairo_pattern_destroy(pat);

      int32_t bigMarkersYList[] = {284, 322, 419, 455, 626};
      int32_t bigMarkersYListCount =
          sizeof(bigMarkersYList) / sizeof(bigMarkersYList[0]);
      int32_t smallMarkersYList[] = {
          306, 370, 434, 476, 498, 517, 536, 556, 575, 593, 611};
      int32_t smallMarkersYListCount =
          sizeof(smallMarkersYList) / sizeof(smallMarkersYList[0]);

      cairo_set_source_rgb(cr, CAIRO_COLOUR_SLIDER_BAR_GREY);
      cairo_set_line_width(cr, 2);
      for (int side = -1; side <= 1; side += 2) {
        for (int i = 0; i < bigMarkersYListCount; i++) {
          cairo_move_to(cr,
                        middleOfTheMixerBar +
                            KOSPWINDOW_MIXER_BIG_MARKER_OFFSET_START_X * side,
                        bigMarkersYList[i]);
          cairo_line_to(cr,
                        middleOfTheMixerBar +
                            KOSPWINDOW_MIXER_BIG_MARKER_OFFSET_END_X * side,
                        bigMarkersYList[i]);
          cairo_stroke(cr);
        }
        for (int i = 0; i < smallMarkersYListCount; i++) {
          cairo_move_to(cr,
                        middleOfTheMixerBar +
                            KOSPWINDOW_MIXER_SMALL_MARKER_OFFSET_START_X * side,
                        smallMarkersYList[i]);
          cairo_line_to(cr,
                        middleOfTheMixerBar +
                            KOSPWINDOW_MIXER_SMALL_MARKER_OFFSET_END_X * side,
                        smallMarkersYList[i]);
          cairo_stroke(cr);
        }

        cairo_move_to(cr,
                      middleOfTheMixerBar +
                          KOSPWINDOW_MIXER_BIG_MARKER_OFFSET_START_X * side,
                      322);
        cairo_line_to(cr,
                      middleOfTheMixerBar +
                          KOSPWINDOW_MIXER_BIG_MARKER_OFFSET_START_X * side,
                      419);
        cairo_stroke(cr);

        cairo_move_to(cr,
                      middleOfTheMixerBar +
                          KOSPWINDOW_MIXER_BIG_MARKER_OFFSET_END_X * side,
                      322);
        cairo_line_to(cr,
                      middleOfTheMixerBar +
                          KOSPWINDOW_MIXER_BIG_MARKER_OFFSET_END_X * side,
                      419);
        cairo_stroke(cr);
      }

      int32_t numNumbers =
          sizeof(numberYPosAndNumber) / sizeof(numberYPosAndNumber[0]);

      cairo_set_font_face(cr, p_kosp_window->robotoSemiboldCairoFontFace);
      cairo_set_font_size(cr, 18.0);
      cairo_set_source_rgb(cr, CAIRO_COLOUR_SLIDER_BAR_GREY);
      char bufferString[10];
      for (int i = 0; i < numNumbers; i++) {
        int32_t markingNumber = numberYPosAndNumber[i].x;
        if (markingNumber > -80) {
          snprintf(bufferString, 10, "%d", (int32_t)(abs(markingNumber)));
        } else {
          snprintf(bufferString, 10, "∞");
        }
        cairo_move_to(
            cr,
            middleOfTheMixerBar + KOSPWINDOW_MIXER_LABEL_TEXT_OFFSET_X,
            (numberYPosAndNumber[i]).y + KOSPWINDOW_MIXER_LABEL_TEXT_OFFSET_Y);
        cairo_show_text(cr, bufferString);
      }
      cairo_move_to(
          cr, middleOfTheMixerBar + KOSPWINDOW_MIXER_LABEL_TEXT_OFFSET_X, 250);
      cairo_show_text(cr, "dB");

      cairo_set_source_rgb(cr, CAIRO_COLOUR_SLIDER_BAR_GREY);
      cairo_utils_rounded_rect(cr,
                               middleOfTheMixerBar -
                                   KOSPWINDOW_MIXER_SURROUNDING_BOX_WIDTH / 2,
                               KOSPWINDOW_MIXER_SURROUNDING_BOX_START_Y,
                               KOSPWINDOW_MIXER_SURROUNDING_BOX_WIDTH,
                               KOSPWINDOW_MIXER_SURROUNDING_BOX_END_Y -
                                   KOSPWINDOW_MIXER_SURROUNDING_BOX_START_Y,
                               KOSPWINDOW_MIXER_SURROUNDING_BOX_CORNER_RADIUS);
      cairo_set_line_width(cr, 1);
      cairo_stroke(cr);

      cairo_set_font_size(cr, 21.0);
      cairo_set_font_face(cr, p_kosp_window->montserratMediumCairoFontFace);
      char *balanceBarTest[] = {"Lows", "Mids", "Highs"};
      cairo_text_extents(cr, balanceBarTest[barIdx], &extents);
      cairo_move_to(cr,
                    middleOfTheMixerBar - extents.width / 2,
                    CAIRO_COLOUR_MIXER_DESCRIPTION_TEXT_Y);
      cairo_show_text(cr, balanceBarTest[barIdx]);

      /* The slider knob */

      cJSON *p_thisDrf = cJSON_GetArrayItem(p_mixerSliders, barIdx);
      VERIFY(p_thisDrf != NULL);
      cJSON *p_savedRatio = cJSON_GetObjectItem(p_thisDrf, "savedRatio");
      VERIFY(p_savedRatio != NULL);
      int32_t sliderMiddleY =
          fx_lin_multi(p_savedRatio->valuedouble, numberYPosAndNumber, B_TRUE);
      cairo_utils_rounded_rect(
          cr,
          middleOfTheMixerBar - KOSPWINDOW_MIXER_SLIDER_SWITCH_WIDTH / 2,
          sliderMiddleY - KOSPWINDOW_MIXER_SLIDER_SWITCH_HEIGHT / 2,
          KOSPWINDOW_MIXER_SLIDER_SWITCH_WIDTH,
          KOSPWINDOW_MIXER_SLIDER_SWITCH_HEIGHT,
          KOSPWINDOW_MIXER_SLIDER_SWITCH_CORNER_RADIUS);
      cairo_set_source_rgb(cr, CAIRO_COLOUR_MIXER_SLIDER_SWITCH_GREY1);
      cairo_fill(cr);

      cairo_rectangle(
          cr,
          middleOfTheMixerBar - KOSPWINDOW_MIXER_SLIDER_SWITCH_WIDTH / 2,
          sliderMiddleY - KOSPWINDOW_MIXER_SLIDER_SWITCH_HEIGHT / 2 +
              KOSPWINDOW_MIXER_SLIDER_SWITCH_SOLID_RECTANGLE_FROM_EDGE,
          KOSPWINDOW_MIXER_SLIDER_SWITCH_WIDTH,
          KOSPWINDOW_MIXER_SLIDER_SWITCH_HEIGHT / 2 -
              KOSPWINDOW_MIXER_SLIDER_SWITCH_SOLID_RECTANGLE_FROM_EDGE);
      cairo_set_source_rgb(cr, CAIRO_COLOUR_MIXER_SLIDER_SWITCH_GREY2);
      cairo_fill(cr);

      cairo_rectangle(
          cr,
          middleOfTheMixerBar - KOSPWINDOW_MIXER_SLIDER_SWITCH_WIDTH / 2,
          sliderMiddleY,
          KOSPWINDOW_MIXER_SLIDER_SWITCH_WIDTH,
          KOSPWINDOW_MIXER_SLIDER_SWITCH_HEIGHT / 2 -
              KOSPWINDOW_MIXER_SLIDER_SWITCH_SOLID_RECTANGLE_FROM_EDGE);
      cairo_set_source_rgb(cr, CAIRO_COLOUR_MIXER_SLIDER_SWITCH_GREY3);
      cairo_fill(cr);

      cairo_rectangle(
          cr,
          middleOfTheMixerBar - KOSPWINDOW_MIXER_SLIDER_SWITCH_WIDTH / 2,
          sliderMiddleY -
              KOSPWINDOW_MIXER_SLIDER_SWITCH_MIDDLE_LINE_THICKNESS / 2,
          KOSPWINDOW_MIXER_SLIDER_SWITCH_WIDTH,
          KOSPWINDOW_MIXER_SLIDER_SWITCH_MIDDLE_LINE_THICKNESS);
      cairo_set_source_rgb(cr, CAIRO_COLOUR_MIXER_SLIDER_SWITCH_GREY4);
      cairo_fill(cr);
    }
  } else if (pageNum == KOSPWINDOW_PAGE_3) {

    /* Clip region with the sliders */
    cairo_rectangle(cr,
                    0,
                    KOSPWINDOW_SLIDER_START_Y -
                        KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS,
                    KOSPWINDOW_WINDOW_WIDTH,
                    KOSPWINDOW_ON_OFF_SWITCH_MAX_NUM_DISPLAYABLE_SWITCHS *
                            KOSPWINDOW_ON_OFF_SWITCH_Y_SPACING +
                        KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS);
    cairo_clip(cr);

    int32_t switchRowY;
    cJSON  *p_thisDrf;
    cJSON  *p_switches =
        cJSON_GetObjectItem(p_kosp_window->p_configJson, "switchesByDrfName");
    int32_t numDrfs = cJSON_GetArraySize(p_switches);

    for (int32_t switchIdx = 0; switchIdx < numDrfs; switchIdx++) {
      /* Description Text */
      cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_WHITE);
      cairo_set_font_face(cr, p_kosp_window->montserratMediumCairoFontFace);
      cairo_set_font_size(cr, 21.0);
      p_thisDrf            = cJSON_GetArrayItem(p_switches, switchIdx);
      cJSON *p_displayName = cJSON_GetObjectItem(p_thisDrf, "displayName");
      cJSON *p_savedRatio  = cJSON_GetObjectItem(p_thisDrf, "savedRatio");

      switchRowY           = KOSPWINDOW_ON_OFF_SWITCH_START_Y +
                   KOSPWINDOW_ON_OFF_SWITCH_Y_SPACING *
                       (switchIdx - p_kosp_window->page3.sliderScrollSmooth);
      cairo_move_to(cr,
                    KOSPWINDOW_ON_OFF_SWITCH_TEXT_START_X,
                    switchRowY + KOSPWINDOW_ON_OFF_SWITCH_TEXT_Y_OFFSET);
      cairo_show_text(cr, p_displayName->valuestring);

      /* Switch body */
      cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_BLACK);
      cairo_utils_rounded_rect(cr,
                               KOSPWINDOW_ON_OFF_SWITCH_START_X,
                               switchRowY + KOSPWINDOW_ON_OFF_SWITCH_Y_OFFSET,
                               KOSPWINDOW_ON_OFF_SWITCH_WIDTH,
                               KOSPWINDOW_ON_OFF_SWITCH_HEIGHT,
                               KOSPWINDOW_ON_OFF_SWITCH_CORNER_RADIUS);
      cairo_set_line_width(cr, 3);
      cairo_stroke(cr);
      cairo_set_source_rgb(cr, CAIRO_COLOUR_SLIDER_BAR_GREY);
      cairo_utils_rounded_rect(cr,
                               KOSPWINDOW_ON_OFF_SWITCH_START_X,
                               switchRowY + KOSPWINDOW_ON_OFF_SWITCH_Y_OFFSET,
                               KOSPWINDOW_ON_OFF_SWITCH_WIDTH,
                               KOSPWINDOW_ON_OFF_SWITCH_HEIGHT,
                               KOSPWINDOW_ON_OFF_SWITCH_CORNER_RADIUS);
      cairo_set_line_width(cr, 2);
      cairo_stroke(cr);

      /* On off state */
      if (p_savedRatio->valueint == B_TRUE) {
        cairo_set_source_rgb(cr, CAIRO_COLOUR_ON_OFF_SWITCH_GREEN);
        cairo_utils_rounded_rect(cr,
                                 KOSPWINDOW_ON_OFF_SWITCH_START_X +
                                     KOSPWINDOW_ON_OFF_SWITCH_WIDTH / 2,
                                 switchRowY +
                                     KOSPWINDOW_ON_OFF_SWITCH_Y_OFFSET + 2,
                                 KOSPWINDOW_ON_OFF_SWITCH_WIDTH / 2 - 2,
                                 KOSPWINDOW_ON_OFF_SWITCH_HEIGHT - 4,
                                 KOSPWINDOW_ON_OFF_SWITCH_CORNER_RADIUS / 2);
        cairo_set_line_width(cr, 2);
        cairo_fill(cr);
        cairo_set_font_face(cr, p_kosp_window->robotoSemiboldCairoFontFace);
        cairo_set_font_size(cr, 15.0);
        cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_WHITE);
        cairo_move_to(cr,
                      KOSPWINDOW_ON_OFF_SWITCH_START_X +
                          KOSPWINDOW_ON_OFF_SWITCH_WIDTH / 2 + 8,
                      switchRowY + KOSPWINDOW_ON_OFF_SWITCH_TEXT_Y_OFFSET);
        cairo_show_text(cr, "On");
      } else {
        cairo_set_source_rgb(cr, CAIRO_COLOUR_ON_OFF_SWITCH_RED);
        cairo_utils_rounded_rect(cr,
                                 KOSPWINDOW_ON_OFF_SWITCH_START_X + 2,
                                 switchRowY +
                                     KOSPWINDOW_ON_OFF_SWITCH_Y_OFFSET + 2,
                                 KOSPWINDOW_ON_OFF_SWITCH_WIDTH / 2 - 2,
                                 KOSPWINDOW_ON_OFF_SWITCH_HEIGHT - 4,
                                 KOSPWINDOW_ON_OFF_SWITCH_CORNER_RADIUS / 2);
        cairo_set_line_width(cr, 2);
        cairo_fill(cr);

        /* On off text */
        cairo_set_font_face(cr, p_kosp_window->robotoSemiboldCairoFontFace);
        cairo_set_font_size(cr, 15.0);
        cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_WHITE);
        cairo_move_to(cr,
                      KOSPWINDOW_ON_OFF_SWITCH_START_X + 9,
                      switchRowY + KOSPWINDOW_ON_OFF_SWITCH_TEXT_Y_OFFSET);
        cairo_show_text(cr, "Off");
      }
    }

    cairo_reset_clip(cr);

    /* Scroll bar */
    double scrollBarRatio =
        (p_kosp_window->page3.sliderScrollSmooth) /
        fmax((double)(numDrfs) +
                 (double)KOSPWINDOW_ON_OFF_SWITCH_BOTTOM_BUFFER_SPACE -
                 (double)KOSPWINDOW_ON_OFF_SWITCH_MAX_NUM_DISPLAYABLE_SWITCHS,
             0);

    cairo_utils_rounded_rect(cr,
                             KOSPWINDOW_SLIDER_SCROLL_BAR_X,
                             KOSPWINDOW_SLIDER_SCROLL_BAR_START_Y,
                             4,
                             KOSPWINDOW_SLIDER_SCROLL_BAR_END_Y -
                                 KOSPWINDOW_SLIDER_SCROLL_BAR_START_Y,
                             2);
    cairo_set_source_rgb(cr, CAIRO_COLOUR_MENU_BUTTON_BACKGROUND_GLOW);
    cairo_fill(cr);

    cairo_utils_rounded_rect(
        cr,
        KOSPWINDOW_SLIDER_SCROLL_BAR_X,
        KOSPWINDOW_SLIDER_SCROLL_BAR_START_Y +
            fx_lin(scrollBarRatio,
                   0,
                   0,
                   1,
                   (KOSPWINDOW_SLIDER_SCROLL_BAR_END_Y -
                    KOSPWINDOW_SLIDER_SCROLL_BAR_START_Y) -
                       KOSPWINDOW_SLIDER_SCROLL_BAR_LENGTH),
        4,
        KOSPWINDOW_SLIDER_SCROLL_BAR_LENGTH,
        2);
    cairo_set_source_rgb(cr, CAIRO_COLOUR_SLIDER_BAR_GREY);
    cairo_fill(cr);

    /* Top Slider Fading Strip */
    pat = cairo_pattern_create_linear(
        0.0,
        KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y,
        0.0,
        KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y +
            KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS);
    cairo_pattern_add_color_stop_rgba(pat, 0, CAIRO_COLOUR_MENU_BACKGROUND, 1);
    cairo_pattern_add_color_stop_rgba(
        pat, 0.2, CAIRO_COLOUR_MENU_BACKGROUND, 1);
    cairo_pattern_add_color_stop_rgba(pat, 1, CAIRO_COLOUR_MENU_BACKGROUND, 0);
    cairo_rectangle(cr,
                    0,
                    KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y,
                    KOSPWINDOW_WINDOW_WIDTH,
                    KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS);
    cairo_set_source(cr, pat);
    cairo_fill(cr);
    cairo_pattern_destroy(pat);

    /* Bottom Slider Fading Strip */
    pat = cairo_pattern_create_linear(
        0.0,
        KOSPWINDOW_SLIDER_START_Y +
            KOSPWINDOW_ON_OFF_SWITCH_MAX_NUM_DISPLAYABLE_SWITCHS *
                KOSPWINDOW_ON_OFF_SWITCH_Y_SPACING,
        0.0,
        KOSPWINDOW_SLIDER_START_Y +
            KOSPWINDOW_ON_OFF_SWITCH_MAX_NUM_DISPLAYABLE_SWITCHS *
                KOSPWINDOW_ON_OFF_SWITCH_Y_SPACING -
            KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS);
    cairo_pattern_add_color_stop_rgba(pat, 0, CAIRO_COLOUR_MENU_BACKGROUND, 1);
    cairo_pattern_add_color_stop_rgba(pat, 1, CAIRO_COLOUR_MENU_BACKGROUND, 0);
    cairo_rectangle(cr,
                    0,
                    KOSPWINDOW_SLIDER_START_Y +
                        KOSPWINDOW_ON_OFF_SWITCH_MAX_NUM_DISPLAYABLE_SWITCHS *
                            KOSPWINDOW_ON_OFF_SWITCH_Y_SPACING -
                        KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS,
                    KOSPWINDOW_WINDOW_WIDTH,
                    KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS);
    cairo_set_source(cr, pat);
    cairo_fill(cr);
    cairo_pattern_destroy(pat);
  } else if (pageNum == KOSPWINDOW_PAGE_4) {
    /* Clip region */
    cairo_rectangle(cr,
                    0,
                    KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y,
                    KOSPWINDOW_WINDOW_WIDTH,
                    KOSPWINDOW_WINDOW_HEIGHT -
                        KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y);
    cairo_clip(cr);
    cJSON *p_changeLog =
        cJSON_GetObjectItem(p_kosp_window->p_changeLogJson, "changeLog");
    int32_t numChangeLogs = cJSON_GetArraySize(p_changeLog);

    int32_t currentY      = KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y;

    currentY -= p_kosp_window->page4.sliderScrollSmoothPx;

    currentY += KOSPWINDOW_CHANGELOG_TITLE_SPACING_ABOVE;

    cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_WHITE);

    for (int32_t changeLogIdx = 0; changeLogIdx < numChangeLogs;
         changeLogIdx++) {

      cJSON *p_thisChangelog = cJSON_GetArrayItem(p_changeLog, changeLogIdx);

      /* Title */

      currentY += KOSPWINDOW_CHANGELOG_TITLE_SPACING_ABOVE;
      cairo_set_font_size(cr, 26.0);
      cairo_text_extents(cr, p_thisChangelog->string, &extents);
      cairo_move_to(
          cr, KOSPWINDOW_WINDOW_WIDTH / 2 - extents.width / 2, currentY);
      cairo_show_text(cr, p_thisChangelog->string);
      currentY += KOSPWINDOW_CHANGELOG_TITLE_SPACING_BELOW;

      int numChangeLogEntries = cJSON_GetArraySize(p_thisChangelog);
      // Access individual elements
      for (int changeLogEntryIdx = 0; changeLogEntryIdx < numChangeLogEntries;
           changeLogEntryIdx++) {
        cJSON *p_thisLine =
            cJSON_GetArrayItem(p_thisChangelog, changeLogEntryIdx);

        cairo_set_font_size(cr, 21.0);
        cairo_text_extents(cr, p_thisLine->valuestring, &extents);
        cairo_move_to(cr, KOSPWINDOW_CHANGELOG_TEXT_START_X, currentY);
        cairo_show_text(cr, p_thisLine->valuestring);
        currentY += KOSPWINDOW_CHANGELOG_LINE_SPACING;
      }
    }

    /* current Y is now at the bottom of the changelog */
    currentY += KOSPWINDOW_CHANGELOG_SCROLL_BOTTOM_BUFFER_PX;

    /* Undo what we did at the start, to get the raw offset */
    currentY -= KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y;

    currentY -= KOSPWINDOW_CHANGELOG_TITLE_SPACING_ABOVE;
    currentY += p_kosp_window->page4.sliderScrollSmoothPx;

    /* This is the maximum, store it */
    p_kosp_window->page4.sliderMaxScrollPx = currentY;

    /* Scroll bar */
    double scrollBarRatio = (p_kosp_window->page4.sliderScrollSmoothPx) /
                            (double)(p_kosp_window->page4.sliderMaxScrollPx);

    cairo_utils_rounded_rect(cr,
                             KOSPWINDOW_SLIDER_SCROLL_BAR_X,
                             KOSPWINDOW_SLIDER_SCROLL_BAR_START_Y,
                             4,
                             KOSPWINDOW_SLIDER_SCROLL_BAR_END_Y -
                                 KOSPWINDOW_SLIDER_SCROLL_BAR_START_Y,
                             2);
    cairo_set_source_rgb(cr, CAIRO_COLOUR_MENU_BUTTON_BACKGROUND_GLOW);
    cairo_fill(cr);

    cairo_utils_rounded_rect(
        cr,
        KOSPWINDOW_SLIDER_SCROLL_BAR_X,
        KOSPWINDOW_SLIDER_SCROLL_BAR_START_Y +
            fx_lin(scrollBarRatio,
                   0,
                   0,
                   1,
                   (KOSPWINDOW_SLIDER_SCROLL_BAR_END_Y -
                    KOSPWINDOW_SLIDER_SCROLL_BAR_START_Y) -
                       KOSPWINDOW_SLIDER_SCROLL_BAR_LENGTH),
        4,
        KOSPWINDOW_SLIDER_SCROLL_BAR_LENGTH,
        2);
    cairo_set_source_rgb(cr, CAIRO_COLOUR_SLIDER_BAR_GREY);
    cairo_fill(cr);

    cairo_reset_clip(cr);

    /* Top Fading Strip */
    pat = cairo_pattern_create_linear(
        0.0,
        KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y,
        0.0,
        KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y +
            KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS);
    cairo_pattern_add_color_stop_rgba(pat, 0, CAIRO_COLOUR_MENU_BACKGROUND, 1);
    cairo_pattern_add_color_stop_rgba(pat, 1, CAIRO_COLOUR_MENU_BACKGROUND, 0);
    cairo_rectangle(cr,
                    0,
                    KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y,
                    KOSPWINDOW_WINDOW_WIDTH,
                    KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS);
    cairo_set_source(cr, pat);
    cairo_fill(cr);
    cairo_pattern_destroy(pat);

    /* Bottom Fading Strip */
    pat = cairo_pattern_create_linear(
        0.0,
        KOSPWINDOW_WINDOW_HEIGHT - KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS * 2,
        0.0,
        KOSPWINDOW_WINDOW_HEIGHT - KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS);
    cairo_pattern_add_color_stop_rgba(pat, 0, CAIRO_COLOUR_MENU_BACKGROUND, 0);
    cairo_pattern_add_color_stop_rgba(pat, 1, CAIRO_COLOUR_MENU_BACKGROUND, 1);
    cairo_rectangle(cr,
                    0,
                    KOSPWINDOW_WINDOW_HEIGHT -
                        KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS * 2,
                    KOSPWINDOW_WINDOW_WIDTH,
                    KOSPWINDOW_SLIDER_FADING_STRIP_THICKNESS * 2);
    cairo_set_source(cr, pat);
    cairo_fill(cr);
    cairo_pattern_destroy(pat);
  }
}