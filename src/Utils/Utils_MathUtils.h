/**
 * @file Utils_MathUtils.h
 *
 * @brief
 *
 * @date 2025-08-01
 *
 * @copyright KOSP Project 2025
 */

#ifndef UTILS_MATHUTILS_H_
#define UTILS_MATHUTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

static inline int min_int(int a, int b) { return a < b ? a : b; }
static inline int max_int(int a, int b) { return a > b ? a : b; }

#ifdef __cplusplus
}
#endif

#endif /* UTILS_MATHUTILS_H_ */