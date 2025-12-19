/**
 * @file SoundLogic_ConstantDefs.h
 *
 * @brief
 *
 * @date 2025-08-02
 *
 * @copyright KOSP Project 2025
 */

#ifndef H_SOUNDLOGIC_CONSTANTDEFS_H_
#define H_SOUNDLOGIC_CONSTANTDEFS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* the size of the landing gear arrays in X Plane */
#define SOUNDLOGIC_MAX_NUM_LANDING_GEARS (10)

/* How long does it take before it stops debounding, s*/
#define SOUNDLOGIC_GEAR_DEBOUNCE_BUFFER_TIME_S (3)

/* The time constant of the throttle lever high pass filters, s*/
#define SOUNDLOGIC_THROTTLE_LEVER_HIGH_PASS_TIMECONSTANT (0.3)

#ifdef __cplusplus
}
#endif
#endif /* H_SOUNDLOGIC_CONSTANTDEFS_H_ */
