/**
 * @file Utils_AnimUtils.h
 *
 * @brief
 *
 * @date 2025-08-01
 *
 * @copyright KOSP Project 2025
 */

#ifndef UTILS_ANIMUTILS_H_
#define UTILS_ANIMUTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief A function that returns a new current value for a number that is
 *        moving towards another number, in an exponentially converging fasion.
 *
 * @param current Current value of the number of interest
 * @param target The destination of the number of interest
 * @param speed An arbitary speed you could set
 * @param dt Time since last call of this function
 * @return double New value for "current"
 */
static inline double AnimUtils_SetAnimValueNoLim(double current,
                                                 double target,
                                                 double speed,
                                                 double dt) {
  return current + ((target - current) * (speed * dt));
}

#ifdef __cplusplus
}
#endif

#endif /* UTILS_ANIMUTILS_H_ */