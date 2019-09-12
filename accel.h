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

bool accel_get_leaning_left(void);

bool accel_get_leaning_right(void);

bool accel_get_stopping(void);

#endif
