/**
 * @file FsAccess_PublicFunctions.h
 *
 * @brief
 *
 * @date 2025-07-28
 *
 * @copyright KOSP Project 2025
 */

#ifndef FSACCESS_PUBLICFUNCTIONS_H_
#define FSACCESS_PUBLICFUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Entry point of the plugin, calls all other modules' init functions.
 *        Should be called on XPluginStart.
 *
 * @return int32_t True on success, false on fail.
 */
extern int32_t FsAccess_Init();

/**
 * @brief Exit point of the plugin, calls all other modules' deinit functions.
 *        Should be called on XPluginStop.
 *
 * @return int32_t True on success, false on fail.
 */
extern int32_t FsAccess_Deinit();

#ifdef __cplusplus
}
#endif

#endif /* FSACCESS_PUBLICFUNCTIONS_H_ */