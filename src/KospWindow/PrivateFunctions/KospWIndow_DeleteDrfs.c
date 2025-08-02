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

void KospWindow_DeleteDrfs(cJSON *p_groupArrayPtr, dr_t *destDrArray) {
  int32_t numDrfs = cJSON_GetArraySize(p_groupArrayPtr);

  for (int32_t idx = 0; idx < numDrfs; idx++) {
    cJSON *p_thisDrf = cJSON_GetArrayItem(p_groupArrayPtr, idx);
    VERIFY(p_thisDrf != NULL);
    cJSON *p_drfName = cJSON_GetObjectItem(p_thisDrf, "drfName");
    VERIFY(p_drfName != NULL);

    dr_delete(&(destDrArray[idx]));
  }
}