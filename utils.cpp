#include <Arduino.h>

#include "hardware.h"
#include "utils.h"

bool utils_is_rear_module(void)
{
  return ~digitalRead(PIN_IS_REAR);
}

bool utils_is_front_module(void)
{
  return digitalRead(PIN_IS_REAR);
}

void utils_init(void)
{
  pinMode(PIN_IS_REAR, INPUT_PULLUP);
}
