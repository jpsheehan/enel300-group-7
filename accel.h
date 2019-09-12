#ifndef ACCEL_H_
#define ACCEL_H_

/**
 * Initialises the accelerometer.
 */
void accel_init(void);

/**
 * Reads the sensor data into memory.
 */
void accel_update(void);

/**
 * Writes all the data from the accelerometer to the serial port.
 */
void accel_dump(void);

#endif
