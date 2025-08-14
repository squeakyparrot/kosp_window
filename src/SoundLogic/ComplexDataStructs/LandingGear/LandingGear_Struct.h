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

/**
 * @brief Structure that represents a single landing gear and its time since
 *        various interactions.
 *
 */
typedef struct LandingGear_Struct {

  /**
   * @details     Time in sim time of the last liftoff
   *
   * @unit        seconds
   * @frame       N/A
   * @sense       N/A
   */
  double offGroundTime;

  /**
   * @details     Time in sim time of the last touchdown
   *
   * @unit        seconds
   * @frame       N/A
   * @sense       N/A
   */
  double onGroundTime;

  /**
   * @details     Time elapsed since the last time the wheel lifted off
   *
   * @unit        seconds
   * @frame       N/A
   * @sense       N/A
   */
  double timeSinceLiftoff;

  /**
   * @details     Time elapsed since the last time the wheel touched down
   *
   * @unit        seconds
   * @frame       N/A
   * @sense       N/A
   */
  double timeSinceTouchdown;

} LandingGear;

#ifdef __cplusplus
}
#endif

#endif /* H_LANDINGGEAR_STRUCT_H_ */