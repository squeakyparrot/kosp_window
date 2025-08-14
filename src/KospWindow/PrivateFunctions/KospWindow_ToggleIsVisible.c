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
#include "XPLMDisplay.h"

/* Acfutils includes */
#include "acfutils/assert.h"
#include "acfutils/helpers.h"
#include "acfutils/log.h"

/* Custom Includes */
#include "KospWindow/DataStructDefs/KospWindow_Struct.h"

/* Refer the header for description */
void KospWindow_ToggleIsVisible(void *inMenuRef, void *inItemRef) {

  /* Cast the refcon into KospWindow */
  VERIFY(inMenuRef != NULL);
  KospWindow *p_kosp_window = inMenuRef;

  /* Flip visibility */
  XPLMSetWindowIsVisible(p_kosp_window->windowId,
                         !XPLMGetWindowIsVisible(p_kosp_window->windowId));
}