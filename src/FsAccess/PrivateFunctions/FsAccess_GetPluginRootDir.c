/**
 * @file FsAccess_GetPluginRootDir.c
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
#include "XPLMPlugin.h"

/* Acfutils includes */
#include "acfutils/helpers.h"
#include "acfutils/log.h"
#include "acfutils/sysmacros.h"

/* Custom Includes */
#include "FsAccess/DataStructDefs/FsAccess_Struct.h"

int32_t FsAccess_GetPluginRootDir(char buffer[256]) {
  /* Get the path to the .xpl */
  XPLMGetPluginInfo(XPLMGetMyID(), NULL, buffer, NULL, NULL);

  fix_pathsep(buffer);

  /* Trim the trailing file separator */
  char *p = strrchr(buffer, DIRSEP);
  if (p != NULL) {
    *p = '\0';
  }

  /* Cut off the architecture specific fat names */
  if ((p = strrchr(buffer, DIRSEP)) != NULL) {
    /* p+1 points to the fat directory because we placed a \0 after it */
    if (strcmp(p + 1, "64") == 0 || strcmp(p + 1, "32") == 0 ||
        strcmp(p + 1, "win_x64") == 0 || strcmp(p + 1, "mac_x64") == 0 ||
        strcmp(p + 1, "lin_x64") == 0) {
      *p = '\0';
    }
  }

  logMsg("Resolved Plugin Root Directory %s", buffer);

  return B_TRUE;
}