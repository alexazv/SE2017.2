//Code by Alexandre Azevedo
//Code created in 19/05/2018

#ifndef THERMOMETER_FINALPROJECT_H
#define THERMOMETER_FINALPROJECT_H

#include <zephyr.h>
#include <sensor.h>
#include <stdio.h>

/**
 * @brief thermometer_get_temperature_as_double
 * Read current temperature in celsius from the thermometer device
 *
 * @return Temperature in celsius
 */
double thermometer_get_temperature_as_double(void);

#endif //THERMOMETER_FINALPROJECT_H
