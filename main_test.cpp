#include <Arduino.h>

#include "led.h"
#include "accel.h"
#include "utils.h"

#include "main_test.h"

void main_test_one(void)
{
  unsigned long now, then;

  while (true) {
    // update the accelerometer every 200 ms
    now = millis();

    if (now - then >= 200) {
      accel_update();
      Serial.println("Updated!");

      if (accel_get_leaning_left()) {
        led_indicate_left_on();
      } else {
        led_indicate_left_off();
      }

      if (accel_get_leaning_right()) {
        led_indicate_right_on();
      } else {
        led_indicate_right_off();
      }

      if (utils_is_rear_module()) {
        if (accel_get_stopping()) {
          led_brakelight_on();
        } else {
          led_brakelight_off();
        }
      }
      
      then = now;
    }
  }
}
