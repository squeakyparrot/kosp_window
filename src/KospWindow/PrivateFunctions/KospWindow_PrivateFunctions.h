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

/**
 * @brief Callback provided to XPLM to be called when a scroll event happens
 *        on top of our window.
 *        This function will then be used to manipulate the KospWindow struct
 *        such that the UI responds.
 *
 * @param inWindowID The window ID of our window
 * @param x The x coord of the event
 * @param y The y coord of the event
 * @param wheel 0 is vertical 1 is horizontal scroll
 * @param clicks how far the wheel has turned since last callback
 * @param inRefcon items passed into the callback
 * @return int
 */
extern int KospWindow_ScrollWheelCallback(XPLMWindowID inWindowID,
                                          int          x,
                                          int          y,
                                          int          wheel,
                                          int          clicks,
                                          void        *inRefcon);

/**
 * @brief Given the path to a json, load it and populate the cJSON pointer.
 * @param config_path Absolute path to the JSON file to be loaded
 * @param pp_destPtr Pointer to the cJSON Pointer to be populated.
 */
extern void KospWindow_LoadJson(char config_path[256], cJSON **pp_destPtr);

/**
 * @brief Given a pointer to the top of the userconfig.json, write it to the
 *        given path on disk.
 *
 * @param p_configJson pointer to the top of the userconfig.json
 * @param config_path Absolute path of the json to write to
 */
void KospWindow_WriteConfJson(cJSON *p_configJson, char config_path[256]);

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

/**
 * @brief Deletes datarefs given a cJSON pointer containing groups of buttons /
 *        switches so on.
 * @param p_groupArrayPtr cJSON ptr that contains childrens with the field
 *        "drfName"
 * @param destDrArray Array of dr_t handles to be deleted in order.
 */
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

/**
 * @brief Given a pointer to the KospWindow struct, create a menu in X-Plane
 *        and append buttons to the plugins menu bar
 *
 * @param p_kosp_window A pointer to the KospWindow struct
 * @return
 */
extern void KospWindow_CreateMenu(KospWindow *p_kosp_window);

/**
 * @brief Wrapper for XPLM stuff that kills the window and removes our entry
 *        from the plugin menu cleanly.
 * @param p_kosp_window A pointer to the KospWindow struct
 * @return
 */
extern void KospWindow_DestroyMenu(KospWindow *p_kosp_window);

/**
 * @brief Callback provided to XPLM for the show/hide button to show or hide
 *        the Kosp window.
 * @param inMenuRef The refcon for the menu itself (us)
 * @param inItemRef The refcon for the menu item (the parent of the button)
 */
extern void KospWindow_ToggleIsVisible(void *inMenuRef, void *inItemRef);

#ifdef __cplusplus
}
#endif
#endif /* H_KOSPWINDOW_PRIVATEFUNCTIONS_H_ */
