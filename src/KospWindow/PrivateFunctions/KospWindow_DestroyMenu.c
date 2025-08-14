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

void KospWindow_DestroyMenu(KospWindow *p_kosp_window) {

  XPLMDestroyMenu(p_kosp_window->menuToggleWindowMenuId);
  XPLMRemoveMenuItem(XPLMFindPluginsMenu(), p_kosp_window->menuContainerIdx);
}