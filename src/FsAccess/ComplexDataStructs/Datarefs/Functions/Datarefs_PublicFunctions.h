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
#include "FsAccess/ComplexDataStructs/Datarefs/DataStructDefs/Datarefs_Struct.h"
#include "FsAccess/DataStructDefs/FsAccess_Struct.h"

#ifndef DATAREFS_PRIVATEFUNCTIONS_H_
#define DATAREFS_PRIVATEFUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int32_t Datarefs_init(Datarefs *p_datarefs_inout);

#ifdef __cplusplus
}
#endif

#endif /* DATAREFS_PRIVATEFUNCTIONS_H_ */