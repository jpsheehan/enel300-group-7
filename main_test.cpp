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
    led_headlight_on();
  } else {
    Serial.println("Module is configured as rear bike light.");
  }

  while (true) {
    // update the accelerometer every 200 ms
    now = millis();

    if (now - then >= 200) {
      accel_update();
      
      if (accel_get_is_leaning_left() && accel_get_is_upright()) {
        led_indicate_left_on();
      } else {
        led_indicate_left_off();
      }

      if (accel_get_is_leaning_right() && accel_get_is_upright()) {
        led_indicate_right_on();
      } else {
        led_indicate_right_off();
      }

      if (utils_is_rear_module()) {
        if (accel_get_is_stopping() && accel_get_is_upright()) {
          led_brakelight_on();
        } else {
          led_brakelight_off();
        }
      }
      
      then = now;
    }
  }
}
