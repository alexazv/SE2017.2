/*
 * Copyright (c) 2016 ARM Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "thermometer.h"

#define ERROR -1

static struct device *thermometer;

double thermometer_get_temperature_as_double(void){
    thermometer = device_get_binding("TEMP_0");
    if (!thermometer) {
        printf("error: no temp device\n");
        return -1;
    }

    struct sensor_value value;

    int sample = sensor_sample_fetch(thermometer);
    if (sample) {
        printf("sensor_sample_fetch failed return: %d\n", sample);
        return -1;
    }

    sample = sensor_channel_get(thermometer, SENSOR_CHAN_TEMP,
                   &value);
    if (sample) {
        printf("sensor_channel_get failed return: %d\n", sample);
        return -1;
    }

    return sensor_value_to_double(&value);
}
