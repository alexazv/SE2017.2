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

    configCompass();

}

void configCompass(){
    uint8_t config;

    //standby
    config = 0;
    i2c_util_write_bytes(&compass, 0x10, config, sizeof(config));

    //continuous read
    config = config =  0x80;
    i2c_util_write_bytes(&compass, 0x11, config, sizeof(config));

    //wake
    config = 0x01;
    i2c_util_write_bytes(&compass, 0x10, config, sizeof(config));
}

uint8_t read_from_accelerometer(){
    static uint8_t data[6];

    i2c_util_read_bytes(&acc, 0x01, data, 6);
    printk("Acc: X = %d, ", (data[1] << 8) | data[0]);

    printk("Y = %d, ", (data[3] << 8) | data[2]);

    printk("Z = %d\n", (data[5] << 8) | data[4]);

    return (data[1] << 8) | data[0];
}

void read_from_compass(uint16_t *dst){
    static uint8_t data[6];

    configCompass();

    i2c_util_read_bytes(&compass, 0x01, data, sizeof(data));

    for(int i = 0; i < 6; i+=2){
        dst[i/2] = (data[i+1] << 8) | data[i];
    }

    printk("Compass: X = %d, ", (data[1] << 8) | data[0]);

    printk("Y = %d, ", (data[3] << 8) | data[2]);

    printk("Z = %d\n", (data[5] << 8) | data[4]);
}
