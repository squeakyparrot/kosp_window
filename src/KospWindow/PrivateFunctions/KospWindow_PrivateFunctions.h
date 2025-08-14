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

/**
 * @brief
 * @param p_kosp_window_in
 * @param config_path
 */
extern void KospWindow_WriteConfJson(KospWindow *p_kosp_window_in,
                                     char        config_path[256]);

/**
 * @brief A function that writes the new value to the json file's drf field
 * @param p_thisDrf A ptr to the parent cJSON drf containing the names, ratios
 * @param p_savedRatio A ptr to the field actually containing the stored value
 * @param ratio A double of the new valye you want to write
 */
extern void KospWindow_SetSliderRatio(cJSON *p_savedRatio, double ratio);

/**
 * @brief Creates a dataref given a cJSON pointer containing groups of buttons /
 *        switches so on.
 * @param p_groupArrayPtr cJSON ptr that contains childrens with the field
 *        "drfName"
 * @param destDrArray Array of dr_t handles to be populated in order.
 * @param p_floatArray Array of floats that the dr_t handles internally refer to
 */
extern void KospWindow_CreateDrfsf(cJSON *p_groupArrayPtr,
                                   dr_t  *destDrArray,
                                   float *p_floatArray);

/**
 * @brief Same as above, but the underlying array is an int, so an int dataref
 *        is created (eg for a switch)
 */
extern void KospWindow_CreateDrfsi(cJSON   *p_groupArrayPtr,
                                   dr_t    *destDrArray,
                                   int32_t *p_intArray);

extern void KospWindow_DeleteDrfs(cJSON *p_groupArrayPtr, dr_t *destDrArray);

/**
 * @brief Sets a dataref given a cJSON pointer containing groups of buttons /
 *        switches so on. This call will set the entirity of the list of
 *        items in the cJSON folder to the value underneath the drfs.
 * @param p_groupArrayPtr cJSON ptr that contains childrens with the field
 *        "drfName"
 * @param p_floatArray Array of floats that the dr_t handles internally refer to
 */
extern void KospWindow_SetDrfsf(cJSON *p_groupArrayPtr, float *p_floatArray);

/**
 * @brief Same as above, but the underlying drf array to write to is an int.
 */
extern void KospWindow_SetDrfsfi(cJSON *p_groupArrayPtr, int32_t *p_intArray);

extern int32_t KospWindow_CreateMenu(KospWindow *p_kosp_window);

extern int32_t KospWindow_DestroyMenu(KospWindow *p_kosp_window);

extern void KospWindow_ToggleIsVisible(void *inMenuRef, void *inItemRef);

#ifdef __cplusplus
}
#endif
#endif /* H_KOSPWINDOW_PRIVATEFUNCTIONS_H_ */
