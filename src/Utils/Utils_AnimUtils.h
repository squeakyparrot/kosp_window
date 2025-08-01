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