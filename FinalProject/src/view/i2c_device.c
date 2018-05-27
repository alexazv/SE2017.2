#define ACC_DEV_ADDR     0x1D
#define ACC_WHO_AM_I_REG 0x0D
#define ACC_TEST_VALUE   0x5A

#define COMPASS_DEV_ADDR     0x0e
#define COMPASS_WHO_AM_I_REG 0x07
#define COMPASS_TEST_VALUE   0xC4

#include "i2c_device.h"

static struct i2c_dev acc;
static struct i2c_dev compass;


/**
 * @brief accelerometer_init
 *
 * Configure the accelerometer device for use
 */
void accelerometer_init(void){
    i2c_util_dev_init(&acc, ACC_DEV_ADDR, "ACC", ACC_WHO_AM_I_REG,
                            ACC_TEST_VALUE);
    accelerometer_active();
}

/**
 * @brief accelerometer_standby
 *
 * Change accelerometer device status to "standby"
 */
void accelerometer_standby(void){
    uint8_t config;
    //clear active bit
    config = 0x00;
    i2c_util_write_bytes(&acc, 0x2A, &config, sizeof(config));

}

/**
 * @brief accelerometer_active
 * Change accelerometer device status to active
 */
void accelerometer_active(void){
    uint8_t config;
    //read from CTRL1
    //i2c_util_read_bytes(&acc, 0x2A, config, 1);

    //set active bit
    config = 0x01;//config | 1;
    i2c_util_write_bytes(&acc, 0x2A, &config, sizeof(config));
}

/**
 * @brief read_from_accelerometer
 * Read the raw x, y and z values from the accelerometer device
 * @param dst - destination of the x, y, z data.
 */
void read_from_accelerometer(uint8_t * data){

    i2c_util_read_bytes(&acc, 0x01, data, 6);
}

/**
 * @brief compass_init
 *
 * Configure the magnetometer device for use
 */
void compass_init(void){
    i2c_util_dev_init(&compass, COMPASS_DEV_ADDR, "COMPASS",
                            COMPASS_WHO_AM_I_REG, COMPASS_TEST_VALUE);
}

//TODO: split in active/standby
void compass_active(){

}

void configCompass(){
    uint8_t config;

    //standby
    config = 0;
    i2c_util_write_bytes(&compass, 0x10, &config, sizeof(config));

    //continuous read
    config = 0x80;
    i2c_util_write_bytes(&compass, 0x11, &config, sizeof(config));

    //wake
    config = 0x01;
    i2c_util_write_bytes(&compass, 0x10, &config, sizeof(config));
}

/**
 * @brief read_from_compass
 * Read the raw x, y and z values from the magnetometer device
 *
 * @param data - destination for the raw x, y, z data.
 */
void read_from_compass(uint8_t *data){

    configCompass();

    i2c_util_read_bytes(&compass, 0x01, data, sizeof(data));
}
