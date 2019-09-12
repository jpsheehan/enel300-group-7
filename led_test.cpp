#include <Arduino.h>

#include "led_test.h"
#include "led.h"
#include "utils.h"

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

void led_test_two(void)
{
  led_indicate_left_on();
  led_indicate_right_on();

  while (true) { continue; }
}

void led_test_three(void)
{
  led_indicate_left_on();
  led_indicate_right_on();
  
  if (utils_is_front_module()) {
      led_headlight_on();
  } else {
      led_brakelight_on();
  }

  while (true) { continue; }
}

void led_test_four(void)
{
  while (true) { led_knightrider(100); }
}

void led_test_five(void)
{
  while (true) {
    if (utils_is_rear_module()) {
      led_brakelight_on();
      led_indicate_left_off();
      led_indicate_right_off();
    } else {
      led_brakelight_off();
      led_indicate_right_on();
      led_indicate_left_on();
    }
  }
}

void led_test_six(void)
{
  led_force_all_on();
  
  while (true) {
    continue;
  }
}
