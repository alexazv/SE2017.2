/**
 *  @file    display.c
 *  @author  Alexandre Azevedo
 *  @date    27/05/2018
 *
 */


#ifndef ACCELEROMETER_FINALPROJECT_H
#define ACCELEROMETER_H

#include "version.h"
#include "i2c_device.h"
#include "display.h"
#include <stdint.h>
#include <math.h>


typedef union {

    /**
     * @brief
     * Raw data for the raw values
     * of the accelerometer as 3 separate
     * 16-bit values
     */
    struct {
        int16_t x;
        int16_t y;
        int16_t z;
    } axis;
    /**
     * @brief data_signed
     *
     * Raw data for the raw values
     * of the accelerometer as a 16-bit
     * array
     */
    uint16_t data_signed[3];
    /**
     * @brief data_raw
     *
     * Raw data for the raw values
     * of the accelerometer with each
     * value separated in two 8-bit integer,
     * as it is read from the device
     */
    uint8_t data_raw[6];
} accelerometer_raw_data_t;

/**
 * @brief calculate_tilt
 * Calculate roll and pitch of the device in degrees based on raw values
 * @param x_raw - raw x value
 * @param y_raw - raw y value
 * @param z_raw - raw z value
 */
static void calculate_tilt(accelerometer_raw_data_t * data);

/**
 * @brief print_tilt
 * Show current tilt as a pixel on the display
 * @param roll - roll of device
 * @param pitch - pitch of the device
 */
void show_accelerometer(void);

/**
 * @brief show_accelerometer
 * Show current tilt as a pixel on the display
 */
static void print_tilt(double_t roll, double_t pitch);


#endif //ACCELEROMETER_H
