/*
 * adaptive_bike_lights.ino
 * 
 * Written by ENEL300 2019 Group 7:
 *  - Jesse Sheehan <jps111@uclive.ac.nz>
 *  - Will Cowper <@uclive.ac.nz>
 *  - Manu Hamblyn <@uclive.ac.nz>
 *  
 * A hardware module to provide indication to other road users about the intentions
 * of the cyclist.
 */

#include "accel.h"
#include "led.h"
#include "utils.h"

void setup() {
  accel_init();
  led_init();
  utils_init();
}

void loop() {
  led_indicate_left_on();
  delay(500);
  led_indicate_left_off();
  delay(500);

  if (utils_is_front_module()) {
    led_headlight_on();
    delay(500);
    led_headlight_off();
    delay(500);
  } else {
    led_brakelight_on();
    delay(500);
    led_brakelight_off();
    delay(500);
  }
  
  led_indicate_right_on();
  delay(500);
  led_indicate_right_off();
  delay(500);
}