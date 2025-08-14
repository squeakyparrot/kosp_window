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
#include "acfutils/dr.h"
#include "acfutils/helpers.h"
#include "acfutils/log.h"

/* cJSON Includes */

/* Custom Includes */
#include "KospWindow/ConstantDefs/KospWindow_ConstantDefs.h"
#include "KospWindow/DataStructDefs/KospWindow_Struct.h"
#include "KospWindow/PrivateFunctions/KospWindow_PrivateFunctions.h"

/**
 * @brief Internal. Do not use.
 *
 */
#define DEFN_KOSPWINDOW_CREATEDRFS(name, type, dr_create_func_name)            \
  void name(cJSON *p_groupArrayPtr, dr_t *destDrArray, type *p_floatArray) {   \
    /* Find how many datarefs we have in this catagory */                      \
    int32_t numDrfs = cJSON_GetArraySize(p_groupArrayPtr);                     \
    /* Check if json is empty */                                               \
    VERIFY(numDrfs > 0);                                                       \
    /* Loop through the items (switches / sliders)*/                           \
    for (int32_t idx = 0; idx < numDrfs; idx++) {                              \
      cJSON *p_thisDrf = cJSON_GetArrayItem(p_groupArrayPtr, idx);             \
      VERIFY(p_thisDrf != NULL);                                               \
      /* Extract the field named drfName */                                    \
      cJSON *p_drfName = cJSON_GetObjectItem(p_thisDrf, "drfName");            \
      VERIFY_MSG(p_drfName != NULL, "%s", "No field named drfName");           \
      /* For this switch / slider, create the drf and store it in the handles  \
       * array in the struct */                                                \
      dr_create_func_name(&(destDrArray[idx]),                                 \
                          &(p_floatArray[idx]),                                \
                          B_TRUE,                                              \
                          "%s",                                                \
                          p_drfName->valuestring);                             \
    }                                                                          \
  }

/* Refer the header for description */
DEFN_KOSPWINDOW_CREATEDRFS(KospWindow_CreateDrfsf, float, dr_create_f)
DEFN_KOSPWINDOW_CREATEDRFS(KospWindow_CreateDrfsi, int32_t, dr_create_i)

#undef DEFN_KOSPWINDOW_CREATEDRFS
