#include <Arduino.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

#include "accel.h"
#include "hardware.h"
#include "utils.h"

#define LEAN_ANGLE(angle) ((angle) / 90.0f)
#define GET_ACC_VALUE(acc) ((acc) / 9.80f)
#define MODULE_COEFFICIENT (utils_is_rear_module() ? -1 : 1)

static const float indicate_angle = 30.0f; // degrees
static const float min_stopping_acc = 5.0f; // m/s^2
static const float upright_angle_tolerance = 45.0f; // degrees

MPU6050 mpu6050(Wire);

void accel_init(void)
{
  Serial.print("Initialising accelerometer module... ");
  
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets();

  Serial.println("Done!");
}

void accel_update(void)
{
  mpu6050.update();
}

float accel_get_acc_x(void)
{
  return mpu6050.getAccX();
}

float accel_get_acc_y(void)
{
  return mpu6050.getAccY();
}

float accel_get_acc_z(void)
{
  return mpu6050.getAccZ();
}

float accel_get_gyro_x(void)
{
  return mpu6050.getGyroX();
}

float accel_get_gyro_y(void)
{
  return mpu6050.getGyroY();
}

float accel_get_gyro_z(void)
{
  return mpu6050.getGyroZ();
}

float accel_get_acc_angle_x(void)
{
  return mpu6050.getAccAngleX();
}

float accel_get_acc_angle_y(void)
{
  return mpu6050.getAccAngleY();
}

float accel_get_gyro_angle_x(void)
{
  return mpu6050.getGyroAngleX();
}

float accel_get_gyro_angle_y(void)
{
  return mpu6050.getGyroAngleY();
}

float accel_get_gyro_angle_z(void)
{
  return mpu6050.getGyroAngleZ();
}

float accel_get_angle_x(void)
{
  return mpu6050.getAngleX();
}

float accel_get_angle_y(void)
{
  return mpu6050.getAngleY();
}

float accel_get_angle_z(void)
{
  return mpu6050.getAngleZ();
}

// TODO: return the z acceleration without the gravity component
float accel_get_normalised_acc_z(void)
{
  return accel_get_acc_z();
}

/**
 * Business Logic:
 */

bool accel_get_is_leaning_left(void)
{
  return accel_get_acc_angle_y() <= -indicate_angle;
}

bool accel_get_is_leaning_right(void)
{
  return accel_get_acc_angle_y() >= indicate_angle;
}

bool accel_get_is_stopping(void)
{
  return accel_get_acc_z() < GET_ACC_VALUE(min_stopping_acc) * MODULE_COEFFICIENT;
}

//bool accel_get_is_laying_flat(void)
//{
//  return (accel_get_acc_angle_x() + 180 >= 180 - flat_angle_tolerance) && (accel_get_acc_angle_x() + 180 <= 180 + flat_angle_tolerance);
//}

bool accel_get_is_upright(void)
{
  return (-90.0f - upright_angle_tolerance) <= accel_get_acc_angle_x() && accel_get_acc_angle_x() <= (-90.0f + upright_angle_tolerance);
}
