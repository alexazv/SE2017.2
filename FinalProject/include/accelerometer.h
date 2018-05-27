#ifndef ACCELEROMETER_FINALPROJECT_H
#define ACCELEROMETER_H

#include "version.h"
#include "i2c_util.h"
#include <stdint.h>
#include <math.h>
#include "display.h"

typedef struct accelerometer_data{
    int16_t x;
    int16_t y;
    int16_t z;
}accelerometer_raw_data;

void accelerometer_init(void);
void accelerometer_standby(void);
void accelerometer_active(void);
void calculate_tilt(int16_t x_raw, int16_t y_raw, int16_t z_raw);
void read_from_accelerometer(int16_t * dst);


#endif //ACCELEROMETER_H
