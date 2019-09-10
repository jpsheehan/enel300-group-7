#ifndef UTILS_H_
#define UTILS_H_

#include <stdbool.h>

/**
 * Returns true if this is a rear module.
 */
bool utils_is_rear_module(void);

/**
 * Returns true if this is a front module.
 */
bool utils_is_front_module(void);

/**
 * Initialises the utility functions.
 */
void utils_init(void);

#endif
