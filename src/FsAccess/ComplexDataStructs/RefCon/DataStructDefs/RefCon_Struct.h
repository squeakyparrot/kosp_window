/**
 * @file Datarefs_Struct.h
 *
 * @brief This file exists as a structure to store pointers that we want to pass
 *        through the refcon.
 *
 * @date 2025-08-02
 *
 * @copyright KOSP Project 2025
 */

#ifndef H_FSACCESS_REFCONSTRUCT_H_
#define H_FSACCESS_REFCONSTRUCT_H_

/* C Library Includes */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* XPLM Includes */

/* Acfutils includes */

/* Custom Includes */
#include "KospWindow/DataStructDefs/KospWindow_Struct.h"
#include "SoundLogic/DataStructDefs/SoundLogic_Struct.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RefCon_Struct {

  /**
   * @details     A pointer to the SoundLogic Struct to pass as the refcon.
   */
  SoundLogic *p_sound_logic;

  /**
   * @details     A pointer to the KospWindow Struct to pass as the refcon.
   */
  KospWindow *p_kosp_window;

} RefCon;

#ifdef __cplusplus
}
#endif

#endif /* H_FSACCESS_REFCONSTRUCT_H_ */
