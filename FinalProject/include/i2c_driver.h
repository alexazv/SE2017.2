#ifndef I2C_FINALPROJECT_H
#define I2C_FINALPROJECT_H

#include "version.h"
#include "i2c_util.h"

void i2c_init();

uint8_t read_from_accelerometer();

uint8_t read_from_compass();

#endif //I2C_FINALPROJECT_H
