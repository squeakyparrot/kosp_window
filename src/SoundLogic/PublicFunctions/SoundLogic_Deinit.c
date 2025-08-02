/**
 * @file FsAccess_FlightLoopCallback.c
 *
 * @brief
 *
 * @date 2025-07-22
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
#include "acfutils/assert.h"
#include "acfutils/dr.h"
#include "acfutils/log.h"

/* Custom Includes */
#include "SoundLogic/DataStructDefs/SoundLogic_Struct.h"

int32_t SoundLogic_Deinit(SoundLogic *p_sound_logic) {

  dr_delete(&(p_sound_logic->d_liftoffTrigger));
  dr_delete(&(p_sound_logic->d_touchdownTrigger));
  dr_delete(&(p_sound_logic->d_flapStressFactor));

  return B_TRUE;
}