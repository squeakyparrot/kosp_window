/**
 * @file SoundLogic_PrivateFunctions.h
 *
 * @brief
 *
 * @date 2025-08-01
 *
 * @copyright KOSP Project 2025
 */

#ifndef SOUNDLOGIC_PRIVATEFUNCTIONS_H_
#define SOUNDLOGIC_PRIVATEFUNCTIONS_H_

/* C Library Includes */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "FsAccess/ComplexDataStructs/Datarefs/DataStructDefs/Datarefs_Struct.h"

extern int32_t SoundLogic_UpdateAirTimes(Datarefs *p_datarefs);

extern int32_t SoundLogic_UpdateFlapStress(Datarefs *p_datarefs);

#ifdef __cplusplus
}
#endif

#endif /* SOUNDLOGIC_PRIVATEFUNCTIONS_H_ */