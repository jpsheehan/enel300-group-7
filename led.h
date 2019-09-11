#ifndef LED_H_
#define LED_H_

#include <stdbool.h>

#include "hardware.h"

/**
 * PIN TO LIGHT DEFINITIONS:
 */
#define PINS_INDICATE_LEFT        PIN_LED_1
#define PINS_INDICATE_LEFT_LEN    1

#define PINS_INDICATE_RIGHT       PIN_LED_5
#define PINS_INDICATE_RIGHT_LEN   1

#define PINS_HEADLIGHT            PIN_LED_2, PIN_LED_3, PIN_LED_4
#define PINS_HEADLIGHT_LEN        3

#define PINS_BRAKELIGHT           PINS_HEADLIGHT
#define PINS_BRAKELIGHT_LEN       PINS_HEADLIGHT_LEN

typedef enum {
  LED_NMOS,
  LED_PMOS
} led_mosfet_type;

/**
 * Turns the left indicator on.
 */
void led_indicate_left_on(void);

/**
 * Turns the left indicator off.
 */
void led_indicate_left_off(void);

/**
 * Returns true if the left indicator is on.
 */
bool led_is_indicate_left_on(void);

/**
 * Turns the right indicator on.
 */
void led_indicate_right_on(void);

/**
 * Turns the right indicator off.
 */
void led_indicate_right_off(void);

/**
 * Returns true if the right indicator is on.
 */
bool led_is_indicate_right_on(void);

/**
 * Turns the brakelight on.
 */
void led_brakelight_on(void);

/**
 * Turns the brakelight off.
 */
void led_brakelight_off(void);

/**
 * Returns true if the brakelight is on.
 */
bool led_is_brakelight_on(void);

/**
 * Turns the headlight on.
 */
void led_headlight_on();

/**
 * Turns the headlight off.
 */
void led_headlight_off();

/**
 * Returns true if the headlight is on.
 */
bool led_is_headlight_on();

/**
 * Initialises the LED hardware.
 */
void led_init(led_mosfet_type t);

/**
 * You know what this does.
 */
void led_knightrider(int delay_ms);

/**
 * Forces all LEDs on with 100% duty.
 */
void led_force_all_on();

/**
 * Forces all LEDs off.
 */
void led_force_all_off();

#endif
