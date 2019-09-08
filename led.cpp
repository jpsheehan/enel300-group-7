#include <Arduino.h>

#include "led.h"

/**
 * LIGHT FLAGS:
 */
static bool indicate_left = false;
static bool indicate_right = false;
static bool brakelight = false;
static bool headlight = false;

/**
 * LIGHT CHANGED FLAGS:
 */
static bool indicate_left_changed = false;
static bool indicate_right_changed = false;
static bool brakelight_changed = false;
static bool headlight_changed = false;

/**
 * LED PIN ARRAYS:
 */
static const int headlight_pins[PINS_HEADLIGHT_LEN] = { PINS_HEADLIGHT };
static const int brakelight_pins[PINS_BRAKELIGHT_LEN] = { PINS_BRAKELIGHT };
static const int indicate_left_pins[PINS_INDICATE_LEFT_LEN] = { PINS_INDICATE_LEFT };
static const int indicate_right_pins[PINS_INDICATE_RIGHT_LEN] = { PINS_INDICATE_RIGHT };

//static int indicate_frequency = 2;
//static int indicate_duty_cycle = 50;

static unsigned long last_update = 0;

void led_indicate_left_on(void)
{
  if (indicate_left == false) {
    indicate_left_changed = true;
  }
  indicate_left = true;
}

void led_indicate_left_off(void)
{
  if (indicate_left == true) {
    indicate_left_changed = true;
  }
  indicate_left = false;
}

bool led_is_indicate_left_on(void)
{
  return indicate_left;
}

void led_indicate_right_on(void)
{
  if (indicate_right == false) {
    indicate_right_changed = true;
  }
  indicate_right = true;
}

void led_indicate_right_off(void)
{
  if (indicate_right == true) {
    indicate_right_changed = true;
  }
  indicate_right = false;
}

bool led_is_indicate_right_on(void)
{
  return indicate_right;
}

void led_brakelight_on(void)
{
  if (brakelight == false) {
    brakelight_changed = true;
  }
  brakelight = true;
}

void led_brakelight_off(void)
{
  if (brakelight == true) {
    brakelight_changed = true;
  }
  brakelight = false;
}

bool led_is_brakelight_on(void)
{
  return brakelight;
}

void led_headlight_on(void)
{
  if (headlight == false) {
    headlight_changed = true;
  }
  headlight = true;
}

void led_headlight_off(void)
{
  if (headlight == true) {
    headlight_changed = true;
  }
  headlight = false;
}

bool led_is_headlight_on(void)
{
  return headlight;
}

void led_update(void)
{
  int i;
  unsigned long now, diff;

  // get some time information (needed for frequency/duty cycle calculations)
  now = millis();
  diff = now - last_update;

  // handle the headlight pins
  if (headlight_changed) {
    for (i = 0; i < PINS_HEADLIGHT_LEN; i++) {
      digitalWrite(headlight_pins[i], headlight ? HIGH : LOW);
    }
    headlight_changed = false;
  }

  // handle the brakelight pins
  if (brakelight_changed) {
    for (i = 0; i < PINS_BRAKELIGHT_LEN; i++) {
      digitalWrite(brakelight_pins[i], brakelight ? HIGH : LOW);
    }
    brakelight_changed = false;
  }

  // TODO: handle the indicate left pin frequency and duty cycle
  if (indicate_left_changed) {
    for (i = 0; i < PINS_INDICATE_LEFT_LEN; i++) {
      digitalWrite(indicate_left_pins[i], indicate_left ? HIGH : LOW);
    }
    indicate_left_changed = false;
  }

  // TODO: handle the indicate right pin frequency and duty cycle
  if (indicate_right_changed) {
    for (i = 0; i < PINS_INDICATE_RIGHT_LEN; i++) {
      digitalWrite(indicate_right_pins[i], indicate_right ? HIGH : LOW);
    }
    indicate_right_changed = false;
  }

  last_update = now;
}

void led_init(void)
{
  int i;

  // initialise left indicator pins
  for (i = 0; i < PINS_INDICATE_LEFT_LEN; i++) {
    pinMode(indicate_left_pins[i], OUTPUT);
  }
  
  // initialise right indicator pins
  for (i = 0; i < PINS_INDICATE_RIGHT_LEN; i++) {
    pinMode(indicate_right_pins[i], OUTPUT);
  }
  
  // initialise headlight pins
  for (i = 0; i < PINS_HEADLIGHT_LEN; i++) {
    pinMode(headlight_pins[i], OUTPUT);
  }
  
  // initialise brakelight pins
  for (i = 0; i < PINS_BRAKELIGHT_LEN; i++) {
    pinMode(brakelight_pins[i], OUTPUT);
  }
}
