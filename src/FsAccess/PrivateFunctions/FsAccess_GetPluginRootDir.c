/**
 * @file FsAccess_GetPluginRootDir.c
 *
 * @brief This file contains a function that gets the root directory of an
 *        X-Plane plugin.
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
#include "XPLMPlugin.h"

/* Acfutils includes */
#include "acfutils/helpers.h"
#include "acfutils/log.h"
#include "acfutils/sysmacros.h"

/* Custom Includes */
#include "FsAccess/DataStructDefs/FsAccess_Struct.h"

/* Refer the header for description */
int32_t FsAccess_GetPluginRootDir(char buffer_inout[256]) {

  /* Safeguard */
  VERIFY(buffer_inout != NULL);

  /* Pre-fill so we can detect "no write" */
  buffer_inout[0] = '\0';

  /* Get the path to the .xpl */
  XPLMGetPluginInfo(XPLMGetMyID(), NULL, buffer_inout, NULL, NULL);

  /* Fix an issue where paths might appear with both unix and windows dirsep*/
  fix_pathsep(buffer_inout);

  /* Trim the trailing dirsep */
  char *p = strrchr(buffer_inout, DIRSEP);
  if (p != NULL) {
    *p = '\0';
  }

  /* Cut off the architecture specific fat names */
  if ((p = strrchr(buffer_inout, DIRSEP)) != NULL) {
    /* p+1 points to the fat directory because we placed a \0 after it */
    if (strcmp(p + 1, "64") == 0 || strcmp(p + 1, "32") == 0 ||
        strcmp(p + 1, "win_x64") == 0 || strcmp(p + 1, "mac_x64") == 0 ||
        strcmp(p + 1, "lin_x64") == 0) {
      /* Place a new terminator on top of the dirsep */
      *p = '\0';
    }
  }

  logMsg("Resolved Plugin Root Directory %s", buffer_inout);

  return B_TRUE;
}