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
#include "acfutils/log.h"
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
  cairo_set_font_size(cr, 21.0);
  for (int32_t i = 0; i < KOSPWINDOW_NUM_PAGES; i++) {
    cairo_text_extents(cr, buttons_text[i], &extents);
    cairo_move_to(cr,
                  i * button_width + 10.0,
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
    int32_t startY =
        KOSPWINDOW_SLIDER_START_Y -
        (p_kosp_window->page1.sliderScrollSmooth) * KOSPWINDOW_SLIDER_Y_SPACING;

    cJSON *p_sliders =
        cJSON_GetObjectItem(p_kosp_window->p_configJson, "slidersByDrfName");
    cJSON  *p_thisDrf;
    int32_t numDrfs = cJSON_GetArraySize(p_sliders);

    for (int32_t sliderIdx = 0; sliderIdx < numDrfs; sliderIdx++) {
      p_thisDrf = cJSON_GetArrayItem(p_sliders, sliderIdx);

      /* Lookup name by drf name */
      cJSON *p_min         = cJSON_GetObjectItem(p_thisDrf, "min");
      cJSON *p_max         = cJSON_GetObjectItem(p_thisDrf, "max");
      cJSON *p_savedRatio  = cJSON_GetObjectItem(p_thisDrf, "savedRatio");
      cJSON *p_displayName = cJSON_GetObjectItem(p_thisDrf, "displayName");

      double barRatio      = p_savedRatio->valuedouble;
      double barKnobX =
          (KOSPWINDOW_SLIDER_END_X - KOSPWINDOW_SLIDER_START_X) * barRatio;
      char ratioString[10];
      snprintf(ratioString,
               10,
               "%d",
               (int32_t)(barRatio * (p_max->valuedouble - p_min->valuedouble) +
                         p_min->valuedouble));

      /* Description Text */
      cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_WHITE);
      cairo_set_font_face(cr, p_kosp_window->montserratMediumCairoFontFace);
      cairo_set_font_size(cr, 21.0);
      cairo_text_extents(cr, p_displayName->valuestring, &extents);
      cairo_move_to(cr,
                    KOSPWINDOW_SLIDER_START_X,
                    startY + KOSPWINDOW_SLIDER_TEXT_Y_OFFSET);
      cairo_show_text(cr, p_displayName->valuestring);

      /* Ratio Text */
      cairo_text_extents(cr, ratioString, &extents);
      cairo_move_to(cr,
                    KOSPWINDOW_SLIDER_END_X - extents.width,
                    startY + KOSPWINDOW_SLIDER_TEXT_Y_OFFSET);
      cairo_show_text(cr, ratioString);

      /* Slider Bar */
      cairo_utils_rounded_rect(cr,
                               KOSPWINDOW_SLIDER_START_X,
                               startY + KOSPWINDOW_SLIDER_BAR_Y_OFFSET,
                               barKnobX,
                               KOSPWINDOW_SLIDER_BAR_THICKNESS,
                               KOSPWINDOW_SLIDER_BAR_THICKNESS / 2);
      cairo_set_source_rgb(cr, CAIRO_COLOUR_SLIDER_BAR_GREY);
      cairo_fill(cr);

      cairo_move_to(cr,
                    KOSPWINDOW_SLIDER_START_X +
                        KOSPWINDOW_SLIDER_BAR_THICKNESS / 2,
                    startY + KOSPWINDOW_SLIDER_BAR_Y_OFFSET +
                        KOSPWINDOW_SLIDER_BAR_THICKNESS / 2);
      cairo_line_to(cr,
                    KOSPWINDOW_SLIDER_START_X + barKnobX -
                        KOSPWINDOW_SLIDER_BAR_THICKNESS / 2,
                    startY + KOSPWINDOW_SLIDER_BAR_Y_OFFSET +
                        KOSPWINDOW_SLIDER_BAR_THICKNESS / 2);
      cairo_set_line_width(cr, 1);
      cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_MENU_FRAME);
      cairo_stroke(cr);

      cairo_utils_rounded_rect(
          cr,
          KOSPWINDOW_SLIDER_START_X + barKnobX,
          startY + KOSPWINDOW_SLIDER_BAR_Y_OFFSET,
          (KOSPWINDOW_SLIDER_END_X - KOSPWINDOW_SLIDER_START_X) *
              (1 - barRatio),
          KOSPWINDOW_SLIDER_BAR_THICKNESS,
          KOSPWINDOW_SLIDER_BAR_THICKNESS / 2);
      cairo_set_source_rgb(cr, CAIRO_COLOUR_XPLANE_MENU_FRAME);
      cairo_fill(cr);

      cairo_move_to(cr,
                    KOSPWINDOW_SLIDER_START_X + barKnobX +
                        KOSPWINDOW_SLIDER_BAR_THICKNESS / 2,
                    startY + KOSPWINDOW_SLIDER_BAR_Y_OFFSET +
                        KOSPWINDOW_SLIDER_BAR_THICKNESS / 2);
      cairo_line_to(cr,
                    KOSPWINDOW_SLIDER_END_X -
                        KOSPWINDOW_SLIDER_BAR_THICKNESS / 2,
                    startY + KOSPWINDOW_SLIDER_BAR_Y_OFFSET +
                        KOSPWINDOW_SLIDER_BAR_THICKNESS / 2);
      cairo_set_line_width(cr, 1);
      cairo_set_source_rgb(cr, CAIRO_COLOUR_MENU_BACKGROUND);
      cairo_stroke(cr);

      /* Move downwards to next slider */
      startY += KOSPWINDOW_SLIDER_Y_SPACING;
    }
  }
}