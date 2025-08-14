/**
 * @file FsAccess_PrivateFunctions.h
 *
 * @brief
 *
 * @date 2025-07-22
 *
 * @copyright KOSP Project 2025
 */

#ifndef H_KOSPWINDOW_PUBLICFUNCTIONS_H_
#define H_KOSPWINDOW_PUBLICFUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* C Library Includes */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* XPLM Includes */
#include "XPLMProcessing.h"

/* Acfutils includes */

/* Custom Includes */
#include "FsAccess/ComplexDataStructs/RefCon/DataStructDefs/RefCon_Struct.h"
#include "KospWindow/DataStructDefs/KospWindow_Struct.h"

/**
 * @brief Init function to populate the KospWindow struct, responsible for
 *        loading fonts, JSON config files etc, and presetting datarefs.
 * @param p_kosp_window_inout Pointer to the KospWindow struct
 * @param inRefcon items passed into the callback
 * @return int32_t
 */
extern int32_t KospWindow_Init(KospWindow *p_kosp_window_inout, RefCon *refcon);

/**
 * @brief Deinit function on unloading the plugin. Handles freeing of uploaders,
 *        fonts, and other resources.
 * @param p_kosp_window_inout Pointer to the KospWindow struct
 * @return int32_t
 */
extern int32_t KospWindow_Deinit(KospWindow *p_kosp_window_inout);

/**
 * @brief Callback on flight loop provided to XPLM.
 * @param inElapsedSinceLastCall See FsAccess_FlightLoopCallback
 * @param inElapsedTimeSinceLastFlightLoop  See FsAccess_FlightLoopCallback
 * @param inCounter  See FsAccess_FlightLoopCallback
 * @param inRefcon  See FsAccess_FlightLoopCallback
 * @return int32_t
 */
extern int32_t
KospWindow_FlightLoopCallback(float inElapsedSinceLastCall,
                              float inElapsedTimeSinceLastFlightLoop,
                              int   inCounter,
                              void *inRefcon);

#ifdef __cplusplus
}
#endif
#endif /* H_KOSPWINDOW_PUBLICFUNCTIONS_H_ */
