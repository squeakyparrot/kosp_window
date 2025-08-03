/**
 * @file FsAccess_PrivateFunctions.h
 *
 * @brief
 *
 * @date 2025-07-22
 *
 * @copyright KOSP Project 2025
 */

#ifndef H_KOSPWINDOW_PRIVATEFUNCTIONS_H_
#define H_KOSPWINDOW_PRIVATEFUNCTIONS_H_

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

extern void KospWindow_DrawCallback(XPLMWindowID inWindowID, void *inRefcon);

extern void KospWindow_RenderCallback(cairo_t *cr,
                                      unsigned window_w,
                                      unsigned window_h,
                                      void    *userinfo);

extern int KospWindow_MouseCallback(XPLMWindowID    inWindowID,
                                    int             x,
                                    int             y,
                                    XPLMMouseStatus inMouse,
                                    void           *inRefcon);

extern int KospWindow_ScrollWheelCallback(XPLMWindowID inWindowID,
                                          int          x,
                                          int          y,
                                          int          wheel,
                                          int          clicks,
                                          void        *inRefcon);

extern void KospWindow_LoadJson(cJSON **pp_destPtr, char config_path[256]);

extern void KospWindow_WriteConfJson(KospWindow *p_kosp_window_in,
                                     char        config_path[256]);

extern void KospWindow_SetSliderRatio(KospWindow *p_kosp_window_in,
                                      char       *catagoryName,
                                      char       *drfName,
                                      char       *propertyName,
                                      double      ratio);

extern void KospWindow_CreateDrfs(cJSON *p_groupArrayPtr,
                                  dr_t  *destDrArray,
                                  float *p_floatArray);

extern void KospWindow_CreateDrfsInt(cJSON   *p_groupArrayPtr,
                                     dr_t    *destDrArray,
                                     int32_t *p_intArray);

extern void KospWindow_DeleteDrfs(cJSON *p_groupArrayPtr, dr_t *destDrArray);

extern void KospWindow_SetDrfs(cJSON *p_groupArrayPtr, float *p_floatArray);

extern void KospWindow_SetDrfsInt(cJSON *p_groupArrayPtr, int32_t *p_intArray);

extern int32_t KospWindow_CreateMenu(KospWindow *p_kosp_window);

extern int32_t KospWindow_DestroyMenu(KospWindow *p_kosp_window);

extern void KospWindow_ToggleIsVisible(void *inMenuRef, void *inItemRef);

#ifdef __cplusplus
}
#endif
#endif /* H_KOSPWINDOW_PRIVATEFUNCTIONS_H_ */
