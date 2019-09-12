#include <Arduino.h>
#include <stdbool.h>

#include "accel.h"
#include "accel_test.h"

void accel_test_one(void)
{
  unsigned long then, now;

  while (true) {
    now = millis();
  
    if (now - then > 2000) {
      accel_update();
      
      Serial.println("=======================================================");
      Serial.print("accX : ");Serial.print(accel_get_acc_x());
      Serial.print("\taccY : ");Serial.print(accel_get_acc_y());
      Serial.print("\taccZ : ");Serial.println(accel_get_acc_z());
    
      Serial.print("gyroX : ");Serial.print(accel_get_gyro_x());
      Serial.print("\tgyroY : ");Serial.print(accel_get_gyro_y());
      Serial.print("\tgyroZ : ");Serial.println(accel_get_gyro_z());
    
      Serial.print("accAngleX : ");Serial.print(accel_get_acc_angle_x());
      Serial.print("\taccAngleY : ");Serial.println(accel_get_acc_angle_y());
    
      Serial.print("gyroAngleX : ");Serial.print(accel_get_gyro_angle_x());
      Serial.print("\tgyroAngleY : ");Serial.print(accel_get_gyro_angle_y());
      Serial.print("\tgyroAngleZ : ");Serial.println(accel_get_gyro_angle_z());
      
      Serial.print("angleX : ");Serial.print(accel_get_angle_x());
      Serial.print("\tangleY : ");Serial.print(accel_get_angle_y());
      Serial.print("\tangleZ : ");Serial.println(accel_get_angle_z());
      Serial.println("=======================================================\n");
  
      then = now;
    }
  }
}

void accel_test_two(void)
{
  unsigned long now, then;

  while (true) {
    now = millis();
    accel_update();

    if (now - then > 200) {
      Serial.print(accel_get_acc_x());
      Serial.print("\t");
      Serial.print(accel_get_acc_y());
      Serial.print("\t");
      Serial.println(accel_get_acc_z());

      then = now;
    }
  }
  
}

void accel_test_three(void)
{
  unsigned long now, then = 0;

  while (true) {
    now = millis();
    accel_update();

    if (now - then >= 200) {
      Serial.print(accel_get_angle_x());
      Serial.print("\t");
      Serial.print(accel_get_angle_y());
      Serial.print("\t");
      Serial.println(accel_get_angle_z());

      then = now;
    }
  }
}

void accel_test_four(void)
{
  unsigned long now, then = 0;

  while (true) {
    now = millis();
    accel_update();

    if (now - then >= 200) {
      Serial.print(accel_get_gyro_angle_x());
      Serial.print("\t");
      Serial.print(accel_get_gyro_angle_y());
      Serial.print("\t");
      Serial.println(accel_get_gyro_angle_z());

      then = now;
    }
  }
}

void accel_test_five(void)
{
  unsigned long now, then = 0;

  while (true) {
    now = millis();
    accel_update();

    if (now - then >= 200) {
      Serial.print(accel_get_acc_angle_x());
      Serial.print("\t");
      Serial.println(accel_get_acc_angle_y());

      then = now;
    }
  }
}

void accel_test_six(void)
{
  unsigned long now, then = 0;

  while (true) {
    now = millis();
    accel_update();

    if (now - then >= 200) {
      Serial.print(accel_get_gyro_x());
      Serial.print("\t");
      Serial.print(accel_get_gyro_y());
      Serial.print("\t");
      Serial.println(accel_get_gyro_z());

      then = now;
    }
  }
}

void accel_test_seven(void)
{
  unsigned long now, then = 0;

  while (true) {
    now = millis();
    accel_update();

    if (now - then >= 200) {
      Serial.print(accel_get_acc_z());
      Serial.print("\t");
      Serial.print(accel_get_acc_angle_x() + 180.0f);
      Serial.print("\t");
      Serial.print(sin(accel_get_acc_angle_x()) * accel_get_acc_angle_x());
      Serial.print("\t");
      Serial.println(accel_get_acc_z() + cos(accel_get_acc_angle_x()));

      then = now;
    }
  }
}
