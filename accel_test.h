#ifndef ACCEL_TEST_H_
#define ACCEL_TEST_H_

/**
 * Dumps all the accelerometer information to the serial port every second.
 */
void accel_test_one(void);

/**
 * Dumps the acceleration information for the serial plotter.
 */
void accel_test_two(void);

/**
 * Dumps the angle information for the serial plotter.
 */
void accel_test_three(void);

/**
 * Dumps the gyro angle information for the serial plotter.
 */
void accel_test_four(void);

/**
 * Dumps the accelerometer angle information for the serial plotter.
 */
void accel_test_five(void);

#endif
