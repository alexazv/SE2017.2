#ifndef I2C_DEVICE_FINALPROJECT_H
#define I2C_DEVICE_FINALPROJECT_H

#include "version.h"
#include "i2c_util.h"
#include <stdint.h>

void accelerometer_init(void);

void accelerometer_init(void);
void accelerometer_standby(void);
void accelerometer_active(void);
void compass_init(void);

//TODO: split in active/standby
void compass_active();

void configCompass();
void read_from_compass(uint8_t * data);
void read_from_accelerometer(uint8_t *data);

#endif //I2C_DEVICE_FINALPROJECT_H
