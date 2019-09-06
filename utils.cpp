#include <Arduino.h>

#include "hardware.h"
#include "utils.h"

bool utils_is_rear_module()
{
  return ~digitalRead(PIN_IS_REAR);
}

bool utils_is_front_module()
{
  return digitalRead(PIN_IS_REAR);
}

void utils_init()
{
  pinMode(PIN_IS_REAR, INPUT_PULLUP);
}
