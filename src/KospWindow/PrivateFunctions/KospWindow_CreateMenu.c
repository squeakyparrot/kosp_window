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
#include "XPLMMenus.h"

/* Acfutils includes */
#include "acfutils/assert.h"
#include "acfutils/helpers.h"
#include "acfutils/log.h"

/* Custom Includes */
#include "KospWindow/PrivateFunctions/KospWindow_PrivateFunctions.h"

/* Refer the header for description */
int32_t KospWindow_CreateMenu(KospWindow *p_kosp_window) {

  p_kosp_window->menuContainerIdx =
      XPLMAppendMenuItem(XPLMFindPluginsMenu(), "KOSP Project", NULL, 0);
  VERIFY(p_kosp_window->menuContainerIdx >= 0);

  p_kosp_window->menuToggleWindowMenuId =
      XPLMCreateMenu("KOSP Project",
                     XPLMFindPluginsMenu(),
                     p_kosp_window->menuContainerIdx,
                     KospWindow_ToggleIsVisible,
                     p_kosp_window);

  XPLMAppendMenuItem(
      p_kosp_window->menuToggleWindowMenuId, "Show/Hide", NULL, 0);

  return B_TRUE;
}