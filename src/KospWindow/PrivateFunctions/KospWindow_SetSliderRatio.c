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
#include "acfutils/helpers.h"
#include "acfutils/log.h"

/* cJSON Includes */
#include "cJSON.h"

/* Custom Includes */
#include "KospWindow/ConstantDefs/KospWindow_ConstantDefs.h"
#include "KospWindow/DataStructDefs/KospWindow_Struct.h"
#include "KospWindow/PrivateFunctions/KospWindow_PrivateFunctions.h"

void KospWindow_SetSliderRatio(KospWindow *p_kosp_window_in,
                               char       *catagoryName,
                               char       *drfName,
                               char       *propertyName,
                               double      ratio) {
  /* Descend into the big json list */
  cJSON *sliders =
      cJSON_GetObjectItem(p_kosp_window_in->p_configJson, catagoryName);

  /* There is nothing in that json */
  VERIFY(sliders != NULL);

  /* Lookup name by drf name */
  cJSON *entry = cJSON_GetObjectItem(sliders, drfName);

  /* There is no such drf name */
  VERIFY_MSG(
      entry != NULL, "Cannot find Slider by Drf Name (JSON Key): %s", drfName);
  cJSON_ReplaceItemInObject(entry, propertyName, cJSON_CreateNumber(ratio));
}