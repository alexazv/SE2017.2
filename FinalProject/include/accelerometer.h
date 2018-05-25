#ifndef ACCELEROMETER_FINALPROJECT_H
#define ACCELEROMETER_H

#include "version.h"
#include "i2c_util.h"
#include <stdint.h>
#include <math.h>
#include "display.h"

void accelerometer_init();
void accelerometer_standby();
void accelerometer_active();
void calculate(int16_t x, int16_t y, int16_t z);
void read_from_accelerometer(int16_t * dst);


#endif //ACCELEROMETER_H
