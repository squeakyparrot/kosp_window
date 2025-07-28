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
#include "KospWindow/DataStructDefs/KospWindow_Struct.h"

extern int32_t KospWindow_Init(KospWindow *p_kosp_window_inout);

extern int32_t KospWindow_Deinit(KospWindow *p_kosp_window_inout);

extern int32_t
KospWindow_FlightLoopCallback(float inElapsedSinceLastCall,
                              float inElapsedTimeSinceLastFlightLoop,
                              int   inCounter,
                              void *inRefcon);

#ifdef __cplusplus
}
#endif
#endif /* H_KOSPWINDOW_PUBLICFUNCTIONS_H_ */
