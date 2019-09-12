#include <Arduino.h>

#include "hardware.h"
#include "utils.h"

bool utils_is_rear_module(void)
{
  return digitalRead(PIN_IS_REAR) == LOW;
}

bool utils_is_front_module(void)
{
  return digitalRead(PIN_IS_REAR) == HIGH;
}

void utils_init(void)
{
  UTILS_PRINT_DBG("Initialising utils module... ");
  
  pinMode(PIN_IS_REAR, INPUT_PULLUP);

  UTILS_PRINTLN_DBG("Done!");
}
