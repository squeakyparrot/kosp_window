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
#include "acfutils/mt_cairo_render.h"

/* Custom Includes */
#include "KospWindow/ConstantDefs/KospWindow_ConstantDefs.h"
#include "KospWindow/DataStructDefs/KospWindow_Struct.h"
#include "KospWindow/PrivateFunctions/KospWindow_PrivateFunctions.h"

void KospWindow_DrawCallback(XPLMWindowID inWindowID, void *inRefcon) {

  VERIFY(inRefcon != NULL);
  KospWindow *p_kosp_window = inRefcon;

  /* Get the dimensions of the window. */
  int32_t left, top, right, bottom, window_w, window_h;
  XPLMGetWindowGeometry(inWindowID, &left, &top, &right, &bottom);
  window_w = right - left;
  window_h = top - bottom;

  /* Setup Rendering Callback for Cairo */

  /* If there is no mtcr surface, or the window got resized */
  if (p_kosp_window->p_mtCairoRender == NULL ||
      (int)mt_cairo_render_get_width(p_kosp_window->p_mtCairoRender) !=
          window_w ||
      (int)mt_cairo_render_get_height(p_kosp_window->p_mtCairoRender) !=
          window_h) {

    /* If there was a mtcr surface (hence resized)*/
    if (p_kosp_window->p_mtCairoRender != NULL) {
      /* Free the old surface */
      mt_cairo_render_fini(p_kosp_window->p_mtCairoRender);
    }

    /* Init a new mtcr */
    p_kosp_window->p_mtCairoRender =
        mt_cairo_render_init(window_w,
                             window_h,
                             KOSPWINDOW_RENDER_FPS,
                             NULL,
                             KospWindow_RenderCallback,
                             NULL,
                             inRefcon);

    /* Check uploader against null ptr */
    if (p_kosp_window->p_mtCairoUploader != NULL) {
      /* Assign the mtcr to the uploader */
      mt_cairo_render_set_uploader(p_kosp_window->p_mtCairoRender,
                                   p_kosp_window->p_mtCairoUploader);
    }
  }

  /* Put the mtcr surface onto the ogl target i.e. the window */
  /* If pos is left as VECT2(0,0) then whatever you draw will not follow the
   * window and get stuck at the bottom of the screen */
  mt_cairo_render_draw(p_kosp_window->p_mtCairoRender,
                       VECT2(left, bottom),
                       VECT2(window_w, window_h));
}