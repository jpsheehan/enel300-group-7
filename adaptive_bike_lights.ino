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

#include "led_test.h"
#include "accel_test.h"
#include "main_test.h"

void setup() {

  // setup the serial port
  Serial.begin(SERIAL_BAUD_RATE);

  // setup the utilities module
  utils_init();

  // setup the led module
  led_init(LED_NMOS);

  // give some visual feedback while calibrating the accelerometer
  led_hazard_on();

  // setup the accelerometer module
  accel_init();

  led_hazard_off();
}

void loop() {
//  main_test_one();
//  led_test_one();
  led_test_two();
}
