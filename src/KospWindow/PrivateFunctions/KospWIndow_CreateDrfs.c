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

void KospWindow_CreateDrfs(cJSON *pp_groupArrayPtr,
                           dr_t  *destDrArray,
                           float *p_floatArray) {
  int32_t numDrfs = cJSON_GetArraySize(pp_groupArrayPtr);

  for (int32_t idx = 0; idx < numDrfs; idx++) {
    cJSON *p_thisDrf = cJSON_GetArrayItem(pp_groupArrayPtr, idx);
    VERIFY(p_thisDrf != NULL);
    cJSON *p_drfName = cJSON_GetObjectItem(p_thisDrf, "drfName");
    VERIFY(p_drfName != NULL);
    dr_create_f(&(destDrArray[idx]),
                &(p_floatArray[idx]),
                B_TRUE,
                "%s",
                p_drfName->valuestring);
  }
}