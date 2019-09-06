#include <Arduino.h>
#include <Wire.h>

#include "accel.h"
#include "hardware.h"

void accel_init()
{
  Wire.begin();
}
