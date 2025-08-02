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

void KospWindow_WriteConfJson(KospWindow *p_kosp_window_in,
                              char        config_path[256]) {
  VERIFY(config_path != NULL);

  /* File handle */
  FILE *fp = fopen(config_path, "wb");
  VERIFY(fp != NULL);

  /* cJSON object to string */
  char *json_string = cJSON_Print(p_kosp_window_in->p_configJson);
  VERIFY(json_string != NULL);

  /* Write string to file */
  fwrite(json_string, 1, strlen(json_string), fp);

  /* Cleanup */
  fclose(fp);
  if (json_string != NULL) {
    free(json_string);
  }
}