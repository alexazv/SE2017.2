#ifndef I2C_DEVICE_FINALPROJECT_H
#define I2C_DEVICE_FINALPROJECT_H

#include "version.h"
#include "i2c_util.h"
#include <stdint.h>

/**
 * @brief accelerometer_init
 *
 * Configure the accelerometer device for use
 */
void accelerometer_init(void);

/**
 * @brief accelerometer_standby
 *
 * Change accelerometer device status to "standby"
 */
void accelerometer_standby(void);

/**
 * @brief accelerometer_active
 * Change accelerometer device status to active
 */
void accelerometer_active(void);

/**
 * @brief read_from_accelerometer
 * Read the raw x, y and z values from the accelerometer device
 * @param dst - destination of the x, y, z data.
 */
void read_from_accelerometer(uint8_t *data);

/**
 * @brief compass_init
 *
 * Configure the magnetometer device for use
 */
void compass_init(void);

/**
 * @brief compass_active
 *
 *Change magnometer device status to "active"
 */
void compass_active(void);

/**
 * @brief compass_standby
 *
 * Change magnetometer device status to "standby"
 */
void compass_standby(void);
/**
 * @brief read_from_compass
 * Read the raw x, y and z values from the magnetometer device
 *
 * @param data - destination for the raw x, y, z data.
 */
void read_from_compass(uint8_t * data);



#endif //I2C_DEVICE_FINALPROJECT_H
