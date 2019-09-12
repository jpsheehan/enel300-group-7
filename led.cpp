#include <Arduino.h>

#include "led.h"
#include "utils.h"

#define LED_HIGH (mosfet_type == LED_NMOS ? HIGH : LOW)
#define LED_LOW  (mosfet_type == LED_NMOS ? LOW : HIGH)
#define LED_PWM_OUTPUT(var) (((var) && (timer_count % 2 == 0)) ? LED_HIGH : LED_LOW)

/**
 * LIGHT FLAGS:
 */
static bool indicate_left = false;
static bool indicate_right = false;
static bool brakelight = false;
static bool headlight = false;


/**
 * PULSE FLAGS:
 */
static bool indicate_pulse = false;
static bool headlight_pulse = false;

/**
 * PULSE FREQUENCIES:
 */
static const float indicate_freq = 1.75f;
static const float headlight_freq = 10.0f;

/**
 * LIGHT CHANGED FLAGS:
 */
static bool indicate_left_changed = false;
static bool indicate_right_changed = false;
static bool brakelight_changed = false;
static bool headlight_changed = false;
static bool hazard_changed = false;
static bool all_changed = false;

/**
 * LED PIN ARRAYS:
 */
static const int headlight_pins[PINS_HEADLIGHT_LEN] = { PINS_HEADLIGHT };
static const int brakelight_pins[PINS_BRAKELIGHT_LEN] = { PINS_BRAKELIGHT };
static const int indicate_left_pins[PINS_INDICATE_LEFT_LEN] = { PINS_INDICATE_LEFT };
static const int indicate_right_pins[PINS_INDICATE_RIGHT_LEN] = { PINS_INDICATE_RIGHT };

/**
 * ISR PWM STUFF:
 */
// if the prescaler or the frequency changes, you will need to change the led_pwm_value
// if the prescaler changes, you must change the related line in led_init
static const int led_pwm_freq = 50; // Hz (the actual timer frequency will be twice this)
static const int led_pwm_prescaler = 64;
static const int led_pwm_value = 2500; // = F_CPU / (led_pwm_freq * led_pwm_prescaler * 2)

static const unsigned long brakelight_delay = 1000;

static led_mosfet_type mosfet_type;

static unsigned timer_count = 0;

static unsigned long brakelight_start = 0;

void led_knightrider(int delay_ms)
{  
  int i;
  
  // left to right
  for (i = 0; i < PINS_INDICATE_LEFT_LEN; i++) {
    digitalWrite(indicate_left_pins[i], LED_HIGH);
    delay(delay_ms);
    digitalWrite(indicate_left_pins[i], LED_LOW);
  }
  for (i = 0; i < PINS_BRAKELIGHT_LEN; i++) {
    digitalWrite(brakelight_pins[i], LED_HIGH);
    delay(delay_ms);
    digitalWrite(brakelight_pins[i], LED_LOW);
  }
  for (i = 0; i < PINS_INDICATE_RIGHT_LEN - 1; i++) {
    digitalWrite(indicate_right_pins[i], LED_HIGH);
    delay(delay_ms);
    digitalWrite(indicate_right_pins[i], LED_LOW);
  }

  // right to left
  for (i = PINS_INDICATE_RIGHT_LEN - 1; i >= 0; --i) {
    digitalWrite(indicate_right_pins[i], LED_HIGH);
    delay(delay_ms);
    digitalWrite(indicate_right_pins[i], LED_LOW);
  }
  for (i = PINS_BRAKELIGHT_LEN - 1; i >= 0; --i) {
    digitalWrite(brakelight_pins[i], LED_HIGH);
    delay(delay_ms);
    digitalWrite(brakelight_pins[i], LED_LOW);
  }
  for (i = PINS_INDICATE_LEFT_LEN - 2; i >= 0; --i) {
    digitalWrite(indicate_left_pins[i], LED_HIGH);
    delay(delay_ms);
    digitalWrite(indicate_left_pins[i], LED_LOW);
  }
}

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
  brakelight_start = millis();
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

ISR(TIMER1_COMPA_vect)
{
  int i;
  unsigned long now = millis();

  // indicator pulsing
  if (timer_count % (int)((2 * led_pwm_freq) / indicate_freq) == 0) {
    indicate_pulse = !indicate_pulse;
    indicate_left_changed = true;
    indicate_right_changed = true;
  }

  // headlight pulsing
  if (timer_count % (int)((2 * led_pwm_freq) / headlight_freq) == 0) {
    headlight_pulse = !headlight_pulse;
    headlight_changed = true;
  }

  // brakelight on or off
  if (brakelight && (now - brakelight_start) >= brakelight_delay) {
    brakelight = false;
    brakelight_changed = true;
  }
  
  // handle the headlight pins
  if (headlight_changed || headlight || all_changed) {
    for (i = 0; i < PINS_HEADLIGHT_LEN; i++) {
      digitalWrite(headlight_pins[i], LED_PWM_OUTPUT(headlight && headlight_pulse));
    }
    headlight_changed = false;
  }

  // handle the brakelight pins
  if (brakelight_changed || brakelight || all_changed) {
    for (i = 0; i < PINS_BRAKELIGHT_LEN; i++) {
      digitalWrite(brakelight_pins[i], LED_PWM_OUTPUT(brakelight));
    }
    brakelight_changed = false;
  }

  // handle the indicate left pins
  if (indicate_left_changed || indicate_left || all_changed) {
    for (i = 0; i < PINS_INDICATE_LEFT_LEN; i++) {
      digitalWrite(indicate_left_pins[i], LED_PWM_OUTPUT(indicate_left && indicate_pulse));
    }
    indicate_left_changed = false;
  }

  // handle the indicate right pins
  if (indicate_right_changed || indicate_right || all_changed) {
    for (i = 0; i < PINS_INDICATE_RIGHT_LEN; i++) {
      digitalWrite(indicate_right_pins[i], LED_PWM_OUTPUT(indicate_right && indicate_pulse));
    }
    indicate_right_changed = false;
  }
  
  all_changed = false;
  timer_count++;
}

void led_init(led_mosfet_type type)
{
  UTILS_PRINT_DBG("Initialising LED module... ");
  
  int i;

  mosfet_type = type;

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

  all_changed = true;

  led_force_all_off();

  // initialise the ISR
  noInterrupts();

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = led_pwm_value;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS11) | (1 << CS10); // prescaler of 64
  TIMSK1 |= (1 << OCIE1A);  
  
  interrupts();

  UTILS_PRINTLN_DBG("Done!");
}

void led_force_all_on(void)
{
  int i;
  for (i = 0; i < PINS_HEADLIGHT_LEN; i++) {
    digitalWrite(headlight_pins[i], LED_HIGH);
  }

  if (utils_is_rear_module()) {
    for (i = 0; i < PINS_BRAKELIGHT_LEN; i++) {
      digitalWrite(brakelight_pins[i], LED_HIGH);
    }
  } else {
    for (i = 0; i < PINS_INDICATE_LEFT_LEN; i++) {
      digitalWrite(indicate_left_pins[i], LED_HIGH);
    }
  }

  for (i = 0; i < PINS_INDICATE_RIGHT_LEN; i++) {
    digitalWrite(indicate_right_pins[i], LED_HIGH);
  }
}

void led_force_all_off(void)
{
  int i;
  for (i = 0; i < PINS_HEADLIGHT_LEN; i++) {
    digitalWrite(headlight_pins[i], LED_LOW);
  }

  if (utils_is_rear_module()) {
    for (i = 0; i < PINS_BRAKELIGHT_LEN; i++) {
      digitalWrite(brakelight_pins[i], LED_LOW);
    }
  } else {
    for (i = 0; i < PINS_INDICATE_LEFT_LEN; i++) {
      digitalWrite(indicate_left_pins[i], LED_LOW);
    }
  }

  for (i = 0; i < PINS_INDICATE_RIGHT_LEN; i++) {
    digitalWrite(indicate_right_pins[i], LED_LOW);
  }
}

void led_hazard_on(void)
{
  led_indicate_left_on();
  led_indicate_right_on();
}

void led_hazard_off(void)
{
  led_indicate_left_off();
  led_indicate_right_off();
}

// undefine the macros so we don't pollute the macro table
#undef LED_PWM_OUTPUT
#undef LED_LOW
#undef LED_HIGH
