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
//  Serial.begin(9600);
  accel_init();
  led_init(LED_NMOS);
  utils_init();
}

/**
 * Blinks each bank of leds on and off individually.
 */
void led_test_one(void)
{
  static unsigned long then = 0;
  unsigned long now = millis();
  unsigned long diff = now - then;

  // have to use this method of "delaying" because delay() actually disables interrupts!
  
  if (diff > 3000) {
    then = now;
    return;
  }

  if (diff > 2500) {
    led_indicate_right_off();
    return;
  }
  if (diff > 2000) {
    led_indicate_right_on();
    return;
  }

  if (diff > 1500) {
    if (utils_is_front_module()) {
        led_headlight_off();
    } else {
        led_brakelight_off();
    }
    return;
  }

  if (diff > 1000) {
    if (utils_is_front_module()) {
        led_headlight_on();
    } else {
        led_brakelight_on();
    }
    return;
  }
  
  if (diff > 500) {
    led_indicate_left_off();
    return;
  } else {
    led_indicate_left_on();
    return;
  }
}

/**
 * Hazard lights!
 */
void led_test_two(void)
{
  led_indicate_left_on();
  led_indicate_right_on();

  while (true) { continue; }
}

/**
 * Ouch! Bright headlights or tail lights!!!
 */
void led_test_three(void)
{
    if (utils_is_front_module()) {
        led_headlight_on();
    } else {
        led_brakelight_on();
    }

    while (true) { continue; }
}

void loop() {
  led_test_three();
}
