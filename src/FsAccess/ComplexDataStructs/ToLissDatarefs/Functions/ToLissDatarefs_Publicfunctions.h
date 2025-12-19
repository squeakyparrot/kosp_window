/**
 * @file Datarefs_PublicFunctions.h
 *
 * @brief
 *
 * @date 2025-07-23
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

/* Acfutils includes */
#include <acfutils/dr.h>

/* Custom Includes */
#include "FsAccess/ComplexDataStructs/ToLissDatarefs/DataStructDefs/ToLissDatarefs_Struct.h"
#include "FsAccess/DataStructDefs/FsAccess_Struct.h"

#ifndef H_TOLISSDATAREFS_PRIVATEFUNCTIONS_H_
#define H_TOLISSDATAREFS_PRIVATEFUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Fetches the datarefs from ToLiss, and if success, fill the handles
 *        into the ToLissDatarefs struct, and set the isInitialised flag to
 *        true.
 *        If not found, the isInitialised flag of the struct will be set to
 *        false.
 *        This should be called recursively until initialised.
 *        The reason it is not passed as a ptr to the struct is for
 *        encapsulation of the handle.
 *
 * @param inRefcon an X Plane standard refcon
 * @return int32_t
 */
extern int32_t ToLissDatarefs_lazyInit(void *inRefcon);

/**
 * @brief Handy function to check if the datarefs are already initialised by
 *        a third party, through the refcon passed through an XPLM callback.
 *        The reason it is not passed as a ptr to the struct is for
 *        encapsulation of the handle.
 *
 * @param inRefcon
 * @return int32_t
 */
extern int32_t ToLissDatarefs_isInitialised(void *inRefcon);

#ifdef __cplusplus
}
#endif

#endif /* H_TOLISSDATAREFS_PRIVATEFUNCTIONS_H_ */