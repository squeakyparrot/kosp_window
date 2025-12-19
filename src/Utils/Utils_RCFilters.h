/**
 * @file Utils_RCFilters.h
 *
 * @brief Low Pass and High Pass Filters
 *
 * @date 2025-12-19
 *
 * @copyright KOSP Project 2025
 */

#ifndef UTILS_RCFILTERS_H_
#define UTILS_RCFILTERS_H_

/* C Library Includes */
#include <math.h>
#include <stdint.h>

/* Acfutils Includes */
#include "acfutils/assert.h"
#include "acfutils/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief LOW PASS FILTER
 *
 */

typedef struct {
  int32_t initialised;
  double  lastOutput;
  double  timeConstant_s;
} LowPassFilter;

/* Initialise with a chosen time constant */
static inline int32_t
RCFilters_initLowPassFilter(LowPassFilter *p_lowPassFilter_in,
                            double         timeConstant_s_in) {

  /* Sanity check */
  VERIFY(p_lowPassFilter_in != NULL);
  VERIFY(timeConstant_s_in > 0);

  p_lowPassFilter_in->lastOutput     = 0;
  p_lowPassFilter_in->timeConstant_s = timeConstant_s_in;
  p_lowPassFilter_in->initialised    = B_TRUE;
  return B_TRUE;
}

static inline double RCFilters_updateLowPassFilter(
    LowPassFilter *p_lowPassFilter_in, double input, double dt) {

  /* Sanity check */
  VERIFY(p_lowPassFilter_in != NULL);
  VERIFY(p_lowPassFilter_in->initialised);
  VERIFY(dt > 0);

  /* Do the filter maths */
  double alpha = dt / (dt + p_lowPassFilter_in->timeConstant_s);
  p_lowPassFilter_in->lastOutput =
      alpha * input + (1 - alpha) * p_lowPassFilter_in->lastOutput;

  /* Return the new output value */
  return p_lowPassFilter_in->lastOutput;
}

/**
 * @brief HIGH PASS FILTER
 *
 */

typedef struct {
  int32_t initialised;
  double  lastOutput;
  double  lastInput;
  double  timeConstant_s;
} HighPassFilter;

/* Initialise with a chosen time constant */
static inline int32_t
RCFilters_initHighPassFilter(HighPassFilter *p_highPassFilter_in,
                             double          timeConstant_s_in) {

  /* Sanity check */
  VERIFY(p_highPassFilter_in != NULL);
  VERIFY(timeConstant_s_in > 0);

  p_highPassFilter_in->lastInput      = 0;
  p_highPassFilter_in->lastOutput     = 0;
  p_highPassFilter_in->timeConstant_s = timeConstant_s_in;
  p_highPassFilter_in->initialised    = B_TRUE;
  return B_TRUE;
}

static inline double RCFilters_updateHighPassFilter(
    HighPassFilter *p_highPassFilter_in, double input, double dt) {

  /* Sanity check */
  VERIFY(p_highPassFilter_in != NULL);
  VERIFY(p_highPassFilter_in->initialised);
  VERIFY(dt > 0);

  /* Do the filter maths */
  double alpha = p_highPassFilter_in->timeConstant_s /
                 (dt + p_highPassFilter_in->timeConstant_s);
  p_highPassFilter_in->lastOutput =
      alpha * (p_highPassFilter_in->lastOutput + input -
               p_highPassFilter_in->lastInput);

  /* Update for next round */
  p_highPassFilter_in->lastInput = input;

  /* Return the new output value */
  return p_highPassFilter_in->lastOutput;
}

#ifdef __cplusplus
}
#endif

#endif /* UTILS_RCFILTERS_H_ */