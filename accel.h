#ifndef ACCEL_H_
#define ACCEL_H_

#include <stdbool.h>

/**
 * Initialises the accelerometer.
 */
void accel_init(void);

/**
 * Reads the sensor data into memory.
 */
void accel_update(void);

/**
 * TODO: Comment all of the following please.
 */

float accel_get_acc_x(void);

float accel_get_acc_y(void);

float accel_get_acc_z(void);

float accel_get_gyro_x(void);

float accel_get_gyro_y(void);

float accel_get_gyro_z(void);

float accel_get_acc_angle_x(void);

float accel_get_acc_angle_y(void);

float accel_get_gyro_angle_x(void);

float accel_get_gyro_angle_y(void);

float accel_get_gyro_angle_z(void);

float accel_get_angle_x(void);

float accel_get_angle_y(void);

float accel_get_angle_z(void);

//float accel_get_normalised_acc_z(void);

/**
 * Returns true if the module is laying flat.
 */
//bool accel_get_is_laying_flat(void);

/**
 * Returns true if the module is leaning left (>= 45 degrees).
 */
bool accel_get_is_leaning_left(void);

/**
 * Returns true if the module is leaning right (>= 45 degrees).
 */
bool accel_get_is_leaning_right(void);

/**
 * Returns true if the module is decelerating.
 */
bool accel_get_is_stopping(void);

/**
 * Returns true if the module is upright (+/- 45 degrees).
 */
bool accel_get_is_upright(void);

#endif
