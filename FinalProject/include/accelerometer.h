#ifndef ACCELEROMETER_FINALPROJECT_H
#define ACCELEROMETER_H

#include "version.h"
#include "i2c_device.h"
#include "display.h"
#include <stdint.h>

typedef union {
    struct {
        int16_t x;
        int16_t y;
        int16_t z;
    } axis;
    uint16_t data_signed[3];
    uint8_t data_raw[6];
} accelerometer_raw_data;

void calculate_tilt(accelerometer_raw_data * data);
void show_accelerometer(void);


#endif //ACCELEROMETER_H
