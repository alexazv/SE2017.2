/*
 * Copyright (c) 2016 ARM Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "thermometer.h"

#define ERROR -1

static struct device *temp_dev;

double get_temperature_as_double(){
    temp_dev = device_get_binding("TEMP_0");
    if (!temp_dev) {
        printf("error: no temp device\n");
        return -1;
    }

    struct sensor_value temp_value;

    int r = sensor_sample_fetch(temp_dev);
    if (r) {
        printf("sensor_sample_fetch failed return: %d\n", r);
        return -1;
    }

    r = sensor_channel_get(temp_dev, SENSOR_CHAN_TEMP,
                   &temp_value);
    if (r) {
        printf("sensor_channel_get failed return: %d\n", r);
        return -1;
    }

    return sensor_value_to_double(&temp_value);
}
