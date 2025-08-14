/**
 * @file KospWindow_LoadConfJson.c
 *
 * @brief
 *
 * @date 2025-08-14
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

/* Refer the header for description */
void KospWindow_LoadJson(char config_path[256], cJSON **pp_destPtr) {
  VERIFY(config_path != NULL);
  logMsg("Loading Config Json from %s", config_path);

  /* Load the content of the json file into a string */
  long  len;
  char *loadedJsonString = file2str_name(&len, config_path);
  VERIFY_MSG(loadedJsonString != NULL, "Cannot find File %s", config_path);

  /* For user bug reports its better to have a copy of what they loaded */
  logMsg("The Loaded JSON String Is:");
  logMsg("\n%s", loadedJsonString);

  /* Parse the string and store it in our own struct */
  *pp_destPtr = cJSON_Parse(loadedJsonString);
  VERIFY(pp_destPtr != NULL);

  free(loadedJsonString);
}