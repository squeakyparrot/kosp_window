/**
 * @file main.c
 *
 * @brief
 *
 * @date 2025-07-28
 *
 * @copyright KOSP Project 2025
 */

/* C Library Includes */
#include <acfutils/glew.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* XPLM Includes */
#include "XPLMDefs.h"
#include "XPLMPlugin.h"
#include "XPLMProcessing.h"

/* Acfutils includes */
#include "acfutils/except.h"
#include "acfutils/log.h"
#include "acfutils/types.h"

/* Custom Includes */
#include "FsAccess/InternalData/FsAccess_InternalData.h"
#include "FsAccess/PrivateFunctions/FsAccess_PrivateFunctions.h"
#include "FsAccess/PublicFunctions/FsAccess_PublicFunctions.h"

//---------------------------------------------------------------------------
// GLEW Mandatory Callbacks

// Put this somewhere in your main file too:
#if IBM
BOOL WINAPI DllMain(HINSTANCE hinst, DWORD reason, LPVOID resvd) {
  lacf_glew_dllmain_hook(reason);
  return (TRUE);
}
#endif // IBM

//---------------------------------------------------------------------------
// SDK Mandatory Callbacks

/**
 * @brief Called when the plugin is first loaded.
 *
 * @param outName Pointer to a buffer of 256 for the name of the plugin.
 * @param outSig Pointer to a buffer of 256 for the signature of the plugin.
 * @param outDesc Pointer to a buffer of 256 for the description of the plugin.
 * @return int True to indicate it was loaded successfully.
 */
PLUGIN_API int XPluginStart(char *outName, char *outSig, char *outDesc) {

#ifdef DEBUG
  /* Init the crash handler */
  except_init();
#endif

#if 0 /* Note: This needs further investigation into what it actually does */
  /* Otherwise funny path separators will appear */
  XPLMEnableFeature("XPLM_USE_NATIVE_PATHS", 1);
#endif

  /* Init the acfutils logger. */
  log_init(log_xplm_cb, "kosp");

  /* Give XPLM a plugin name and signature. */
  snprintf(outName, 256, "kosp_menu");
  snprintf(outSig, 256, "kosp_project.kosp_menu");
  snprintf(outDesc, 256, "KOSP Project Mixing Panel Menu");

  /* Init OpenGL Context for libacfutils & Cairo*/
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    /* Problem: glewInit failed, something is seriously wrong. */
  }

  /* Call init for our own part of the program*/
  ASSERT(FsAccess_Init());

  return B_TRUE;
}

//---------------------------------------------------------------------------

/* Called right before the plugin is unloaded */
PLUGIN_API void XPluginStop(void) {

  /* Stop the flight loop. */
  XPLMDestroyFlightLoop(fs_access.flightLoopId);

  /* Stop all modules */
  FsAccess_Deinit();

  /* Call Logging finish. */
  log_fini();

#ifdef DEBUG
  /* Stop the crash handler */
  except_fini();
#endif
}

//---------------------------------------------------------------------------

/* Called when the plugin is enabled. */
PLUGIN_API int XPluginEnable(void) { return B_TRUE; }

//---------------------------------------------------------------------------

/* Called when the plugin is disabled. */
PLUGIN_API void XPluginDisable(void) {}

//---------------------------------------------------------------------------

/* Called when a plugin or X-Plane sends the plugin a message eg plane crash. */
PLUGIN_API void
XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void *inParam) {
  UNUSED(inFrom);
  UNUSED(inMsg);
  UNUSED(inParam);
}
