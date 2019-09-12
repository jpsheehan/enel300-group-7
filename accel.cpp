#include <Arduino.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

#include "accel.h"
#include "hardware.h"

MPU6050 mpu6050(Wire);

void accel_init(void)
{
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
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

bool accel_get_is_leaning_left(void)
{
  return accel_get_acc_x() > 0.5;
}

bool accel_get_is_leaning_right(void)
{
  return accel_get_acc_x() < -0.5;
}

bool accel_get_is_stopping(void)
{
  return accel_get_acc_z() < -0.5;
}

bool accel_get_is_upright(void)
{
  return -135.0f <= accel_get_acc_angle_x() && accel_get_acc_angle_x() <= -45.0f;
}
