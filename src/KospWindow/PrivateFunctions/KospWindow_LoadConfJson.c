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

void KospWindow_LoadJson(cJSON **pp_destPtr, char config_path[256]) {
  VERIFY(config_path != NULL);
  logMsg("Loading Config Json from %s", config_path);

  /* Load the content of the json file into a string */
  long  len;
  char *loadedJsonString = file2str_name(&len, config_path);
  VERIFY_MSG(loadedJsonString != NULL, "Cannot find File %s", config_path);
  logMsg("The Loaded JSON String Is:");
  logMsg("\n%s", loadedJsonString);

  /* Parse the string and store it in our own struct */
  *pp_destPtr = cJSON_Parse(loadedJsonString);
  VERIFY(pp_destPtr != NULL);

  free(loadedJsonString);
}