/**
 *  @file    display.c
 *  @author  Alexandre Azevedo
 *  @date    27/05/2018
 *
 */

#define ACC_DEV_ADDR     0x1D
#define ACC_WHO_AM_I_REG 0x0D
#define ACC_TEST_VALUE   0x5A

#define COMPASS_DEV_ADDR     0x0e
#define COMPASS_WHO_AM_I_REG 0x07
#define COMPASS_TEST_VALUE   0xC4

#include "i2c_device.h"

static struct i2c_dev acc;
static struct i2c_dev compass;

void accelerometer_init(void){
    i2c_util_dev_init(&acc, ACC_DEV_ADDR, "ACC", ACC_WHO_AM_I_REG,
                            ACC_TEST_VALUE);
    accelerometer_active();
}


void accelerometer_standby(void){
    uint8_t config;
    //clear active bit
    config = 0x00;
    i2c_util_write_bytes(&acc, 0x2A, &config, sizeof(config));
}


void accelerometer_active(void){
    uint8_t config;
    //read from CTRL1
    //i2c_util_read_bytes(&acc, 0x2A, config, 1);

    //set active bit
    config = 0x01;//config | 1;
    i2c_util_write_bytes(&acc, 0x2A, &config, sizeof(config));
}


void read_from_accelerometer(uint8_t * data){

    i2c_util_read_bytes(&acc, 0x01, data, 6);
}


void compass_init(void){
    i2c_util_dev_init(&compass, COMPASS_DEV_ADDR, "COMPASS",
                            COMPASS_WHO_AM_I_REG, COMPASS_TEST_VALUE);

    compass_standby();

    //continuous read
    uint8_t config = 0x80;
    i2c_util_write_bytes(&compass, 0x11, &config, sizeof(config));

    compass_active();
}

void compass_active(void){
    //wake
    uint8_t config = 0x01;
    i2c_util_write_bytes(&compass, 0x10, &config, sizeof(config));
}

void compass_standby(void){
    //standby
    uint8_t config = 0x00;
    i2c_util_write_bytes(&compass, 0x10, &config, sizeof(config));

}

void read_from_compass(uint8_t *data){

    i2c_util_read_bytes(&compass, 0x01, data, sizeof(data));
}
