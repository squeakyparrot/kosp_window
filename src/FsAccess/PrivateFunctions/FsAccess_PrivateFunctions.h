/**
 * @file FsAccess_PrivateFunctions.h
 *
 * @brief
 *
 * @date 2025-07-22
 *
 * @copyright KOSP Project 2025
 */

#ifndef FSACCESS_PRIVATEFUNCTIONS_H_
#define FSACCESS_PRIVATEFUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief A function that takes in a 256 bit buffer (same as the size required
 *        by XPLMGetPluginInfo) and fills it with a null terminated string of
 *        the absolute path to the root of the plugin (not the binary)
 *
 * @param buffer_inout A 256 bit buffer string to be filled
 * @return int32_t On success returns 1, on failure returns 0
 */
extern int32_t FsAccess_GetPluginRootDir(char buffer_inout[256]);

/**
 * @brief A parent to be called by XPLM that covers all flight loop callbacks
 *        from other modules in the project.
 *
 * @param inElapsedSinceLastCall time since last time this was called
 * @param inElapsedTimeSinceLastFlightLoop time since any last flight loop
 * @param inCounter number of flight loops so far
 * @param inRefcon void ptr of a refcon to be passed to callbacks
 * @return float
 */
extern float FsAccess_FlightLoopCallback(float inElapsedSinceLastCall,
                                         float inElapsedTimeSinceLastFlightLoop,
                                         int   inCounter,
                                         void *inRefcon);

#ifdef __cplusplus
}
#endif

#endif /* FSACCESS_PRIVATEFUNCTIONS_H_ */