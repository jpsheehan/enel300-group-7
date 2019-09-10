#include <Arduino.h>

#include "led.h"

#define LED_HIGH (mosfet_type == LED_NMOS ? HIGH : LOW)
#define LED_LOW  (mosfet_type == LED_NMOS ? LOW : HIGH)
#define LED_PWM_OUTPUT(var) ((var && (timer_count % 2 == 0)) ? LED_HIGH : LED_LOW)

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

// if the prescaler or the frequency changes, you will need to change the led_pwm_value
// if the prescaler changes, you must change the related line in led_init
static const int led_pwm_freq = 50; // Hz (the actual timer frequency will be twice this)
static const int led_pwm_prescaler = 64;
static const int led_pwm_value = 2500; // = F_CPU / (led_pwm_freq * led_pwm_prescaler * 2)

static led_mosfet_type mosfet_type;

static int timer_count = 0;

//static int indicate_frequency = 2;

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

ISR(TIMER1_COMPA_vect)
{
  int i;

//  Serial.println(timer_count);
  
  // handle the headlight pins
  if (headlight_changed || headlight) {
    for (i = 0; i < PINS_HEADLIGHT_LEN; i++) {
      digitalWrite(headlight_pins[i], LED_PWM_OUTPUT(headlight));
    }
    headlight_changed = false;
  }

  // handle the brakelight pins
  if (brakelight_changed || brakelight) {
    for (i = 0; i < PINS_BRAKELIGHT_LEN; i++) {
      digitalWrite(brakelight_pins[i], LED_PWM_OUTPUT(brakelight));
    }
    brakelight_changed = false;
  }

  // TODO: handle the indicate left pin frequency and duty cycle
  if (indicate_left_changed || indicate_left) {
    for (i = 0; i < PINS_INDICATE_LEFT_LEN; i++) {
      digitalWrite(indicate_left_pins[i], LED_PWM_OUTPUT(indicate_left));
    }
    indicate_left_changed = false;
  }

  // TODO: handle the indicate right pin frequency and duty cycle
  if (indicate_right_changed || indicate_right) {
    for (i = 0; i < PINS_INDICATE_RIGHT_LEN; i++) {
      digitalWrite(indicate_right_pins[i], LED_PWM_OUTPUT(indicate_right));
    }
    indicate_right_changed = false;
  }

  timer_count = (timer_count + 1) % led_pwm_value;
}

void led_init(led_mosfet_type type)
{
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
}
