#ifndef UTILS_H_
#define UTILS_H_

#include <stdbool.h>

#include "hardware.h"

// define some printing functions that depend on the presence
// of the debug flag
#if IS_DBG
  #define UTILS_PRINT_DBG(str) Serial.print(str)
  #define UTILS_PRINTLN_DBG(str) Serial.println(str)
#else
  #define UTILS_PRINT_DBG(str) __asm__("nop\n\t")
  #define UTILS_PRINTLN_DBG(str) __asm__("nop\n\t")
#endif

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
