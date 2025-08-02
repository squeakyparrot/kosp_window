/**
 * @file SoundLogic_Struct.h
 *
 * @brief
 *
 * @date 2025-08-01
 *
 * @copyright KOSP Project 2025
 */

#ifndef H_LANDINGGEAR_STRUCT_H_
#define H_LANDINGGEAR_STRUCT_H_

/* C Library Includes */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* XPLM Includes */

/* Acfutils includes */

/* Custom Includes */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LandingGear_Struct {

  /**
   * @details     actual time since sim start in sec
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  double offGroundTime;

  /**
   * @details     actual time since sim start in sec
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  double onGroundTime;

  /**
   * @details     actual time since sim start in sec
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  double timeSinceLiftoff;

  /**
   * @details     actual time since sim start in sec
   *
   * @unit        N/A
   * @frame       N/A
   * @sense       N/A
   */
  double timeSinceTouchdown;

} LandingGear;

#ifdef __cplusplus
}
#endif

#endif /* H_LANDINGGEAR_STRUCT_H_ */