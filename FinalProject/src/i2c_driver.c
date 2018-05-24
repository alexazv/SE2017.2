/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "version.h"
#include "i2c_util.h"
#include "i2c_driver.h"

static struct i2c_dev acc, compass;

#define ACC_DEV_ADDR     0x1D
#define ACC_WHO_AM_I_REG 0x0D
#define ACC_TEST_VALUE   0x5A

#define COMPASS_DEV_ADDR     0x0e
#define COMPASS_WHO_AM_I_REG 0x07
#define COMPASS_TEST_VALUE   0xC4

void i2c_init(){
    i2c_util_dev_init(&acc, ACC_DEV_ADDR, "ACC", ACC_WHO_AM_I_REG,
                            ACC_TEST_VALUE);
    i2c_util_dev_init(&compass, COMPASS_DEV_ADDR, "COMPASS",
                            COMPASS_WHO_AM_I_REG, COMPASS_TEST_VALUE);
}

uint8_t read_from_accelerometer(){
    static u8_t data[2];
    i2c_util_read_bytes(&acc, 0x02, data, sizeof(data));
    return (data[1] << 8) | data[0];
}

uint8_t read_from_compass(){
    static u8_t data[2];
    i2c_util_read_bytes(&compass, 0x02, data, sizeof(data));
    return (data[1] << 8) | data[0];
}
