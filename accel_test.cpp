#include <Arduino.h>

#include "accel.h"
#include "accel_test.h"

void accel_test_one(void)
{
  unsigned long then, now;

  while (true) {
    now = millis();
  
    if (now - then > 2000) {
      accel_update();
      accel_dump();
  
      then = now;
    }
  }
}
