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

/* Refer the header for description */
void KospWindow_SetDrfsf(cJSON *p_groupArrayPtr, float *p_floatArray) {

  /* Find how many datarefs we have in this catagory */
  int32_t numDrfs = cJSON_GetArraySize(p_groupArrayPtr);

  /* Check if json is empty */
  VERIFY(numDrfs > 0);

  /* For all of the drfs */
  for (int32_t idx = 0; idx < numDrfs; idx++) {

    /* Descend into the savedRatio field */
    cJSON *p_thisDrf = cJSON_GetArrayItem(p_groupArrayPtr, idx);
    VERIFY(p_thisDrf != NULL);
    cJSON *p_savedRatio = cJSON_GetObjectItem(p_thisDrf, "savedRatio");
    VERIFY(p_savedRatio != NULL);

    /* Write to the drf underlying array using the json val */
    p_floatArray[idx] = p_savedRatio->valuedouble;
  }
}

/* Refer the header for description */
void KospWindow_SetDrfsfi(cJSON *p_groupArrayPtr, int32_t *p_intArray) {
  int32_t numDrfs = cJSON_GetArraySize(p_groupArrayPtr);

  /* Check if json is empty */
  VERIFY(numDrfs > 0);

  /* For all of the drfs */
  for (int32_t idx = 0; idx < numDrfs; idx++) {

    /* Descend into the savedRatio field */
    cJSON *p_thisDrf = cJSON_GetArrayItem(p_groupArrayPtr, idx);
    VERIFY(p_thisDrf != NULL);
    cJSON *p_savedRatio = cJSON_GetObjectItem(p_thisDrf, "savedRatio");
    VERIFY(p_savedRatio != NULL);

    /* Write to the drf underlying array using the json val */
    p_intArray[idx] = p_savedRatio->valuedouble;
  }
}