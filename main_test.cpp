#include <Arduino.h>

#include "led.h"
#include "accel.h"
#include "utils.h"

#include "main_test.h"

void main_test_one(void)
{
  unsigned long now, then = 0;

  if (utils_is_front_module()) {
    Serial.println("Module is configured as front bike light.");
  } else {
    Serial.println("Module is configured as rear bike light.");
  }

  Serial.println("Running main loop...");
  
  led_headlight_on();

  while (true) {
    // update the accelerometer every 200 ms
    now = millis();

    if (now - then >= 200) {
      accel_update();

      // LEFT LEAN
      if (accel_get_is_leaning_left()) {
        led_indicate_left_on();
      } else {
        led_indicate_left_off();
      }

      // RIGHT LEAN
      if (accel_get_is_leaning_right()) {
        led_indicate_right_on();
      } else {
        led_indicate_right_off();
      }

      // BRAKING
      if (utils_is_rear_module() && accel_get_is_stopping() && accel_get_is_upright()) {
        led_brakelight_on();
      }
      
      then = now;
    }
  }
}
