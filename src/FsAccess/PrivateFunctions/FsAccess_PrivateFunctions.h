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

extern int32_t FsAccess_Init();

extern int32_t FsAccess_Deinit();

extern int32_t FsAccess_GetPluginRootDir(char buffer[256]);

extern float FsAccess_FlightLoopCallback(float inElapsedSinceLastCall,
                                         float inElapsedTimeSinceLastFlightLoop,
                                         int   inCounter,
                                         void *inRefcon);

#ifdef __cplusplus
}
#endif

#endif /* FSACCESS_PRIVATEFUNCTIONS_H_ */