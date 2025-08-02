/**
 * @file FsAccess_InternalData.c
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
#include "XPLMProcessing.h"

/* Acfutils includes */

/* Custom Includes */
#include "FsAccess/ComplexDataStructs/Datarefs/DataStructDefs/Datarefs_Struct.h"
#include "FsAccess/ComplexDataStructs/RefCon/DataStructDefs/RefCon_Struct.h"
#include "FsAccess/DataStructDefs/FsAccess_Struct.h"

/**
 * @brief Instance of the FsAccess struct.
 *        Refer to the header for description.
 *
 */
FsAccess fs_access;

/**
 * @brief Instance of the Datarefs struct.
 *        Refer to the header for description.
 *
 */
Datarefs datarefs;

/**
 * @brief Instance of the RefCon struct.
 *        Refer to the header for description.
 *
 */
RefCon refcon;