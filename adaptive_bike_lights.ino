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

static const int update_frequency = 10; // Hz

static unsigned long now, then = 0;

/**
 * Prints some version and author information
 */
void print_prelude(void)
{
  UTILS_PRINTLN_DBG("Adaptive Bike Light System - VisiBIKE");
  UTILS_PRINTLN_DBG("Written by Jesse Sheehan, Will Cowper, Manu Hamblyn");
  UTILS_PRINTLN_DBG("");

  // Print some info
  UTILS_PRINT_DBG("Firmware compiled on ");
  UTILS_PRINT_DBG(__DATE__);
  UTILS_PRINT_DBG(" at ");
  UTILS_PRINT_DBG(__TIME__);
  UTILS_PRINTLN_DBG("");
  UTILS_PRINTLN_DBG("");
  
}

void setup() {
  
  // setup the serial port
  Serial.begin(SERIAL_BAUD_RATE);

  print_prelude();

  // setup the utilities module
  utils_init();

  // setup the led module
  led_init(LED_PMOS);

  // give some visual feedback while calibrating the accelerometer
  led_hazard_on();

  // setup the accelerometer module
  accel_init();

  // turn off the hazard lights
  led_hazard_off();

  // print some information to the serial port
  UTILS_PRINTLN_DBG("");
  if (utils_is_front_module()) {
    UTILS_PRINTLN_DBG("Module is configured as front bike light.");
  } else {
    UTILS_PRINTLN_DBG("Module is configured as rear bike light.");
  }
  
  UTILS_PRINTLN_DBG("");
  UTILS_PRINTLN_DBG("Running main loop...");

  // turn the "headlight" on (this is the brakelight on the rear module)
  led_headlight_on();
}

void loop() {
  now = millis();

  if (now - then >= 1000.0f / update_frequency) {
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
    if (utils_is_rear_module() && accel_get_is_stopping()) {
      led_brakelight_on();
    }
    
    then = now;
  }
}
