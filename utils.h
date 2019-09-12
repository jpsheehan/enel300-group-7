#ifndef UTILS_H_
#define UTILS_H_

#include <stdbool.h>

//#include "hardware.h"

//#define UTILS_PRINT_DBG(str) #if IS_DBG \
//  Serial.print(str) \
//#endif

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
