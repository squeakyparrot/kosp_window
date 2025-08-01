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

void KospWindow_SetDrfs(cJSON *pp_groupArrayPtr, float *p_floatArray) {
  int32_t numDrfs = cJSON_GetArraySize(pp_groupArrayPtr);

  for (int32_t idx = 0; idx < numDrfs; idx++) {
    cJSON *p_thisDrf = cJSON_GetArrayItem(pp_groupArrayPtr, idx);
    VERIFY(p_thisDrf != NULL);
    cJSON *p_drfName = cJSON_GetObjectItem(p_thisDrf, "drfName");
    VERIFY(p_drfName != NULL);
    cJSON *p_savedRatio = cJSON_GetObjectItem(p_thisDrf, "savedRatio");
    VERIFY(p_savedRatio != NULL);

    p_floatArray[idx] = p_savedRatio->valuedouble;
  }
}

void KospWindow_SetDrfsInt(cJSON *pp_groupArrayPtr, int32_t *p_intArray) {
  int32_t numDrfs = cJSON_GetArraySize(pp_groupArrayPtr);

  for (int32_t idx = 0; idx < numDrfs; idx++) {
    cJSON *p_thisDrf = cJSON_GetArrayItem(pp_groupArrayPtr, idx);
    VERIFY(p_thisDrf != NULL);
    cJSON *p_drfName = cJSON_GetObjectItem(p_thisDrf, "drfName");
    VERIFY(p_drfName != NULL);
    cJSON *p_savedRatio = cJSON_GetObjectItem(p_thisDrf, "savedRatio");
    VERIFY(p_savedRatio != NULL);

    p_intArray[idx] = p_savedRatio->valuedouble;
  }
}