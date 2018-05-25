#include "accelerometer.h"

#define ACC_DEV_ADDR     0x1D
#define ACC_WHO_AM_I_REG 0x0D
#define ACC_TEST_VALUE   0x5A

static struct i2c_dev acc;

void accelerometer_init(){
    i2c_util_dev_init(&acc, ACC_DEV_ADDR, "ACC", ACC_WHO_AM_I_REG,
                            ACC_TEST_VALUE);
}

void accelerometer_standby(){
    uint8_t config;
    //read from CTRL1
    i2c_util_read_bytes(&acc, 0x2A, config, 1);

    //clear active bit
    config = config & (~1);
    i2c_util_write_bytes(&acc, 0x2A, config, sizeof(config));

}

void accelerometer_active(){
    uint8_t config;
    //read from CTRL1
    i2c_util_read_bytes(&acc, 0x2A, config, 1);

    //set active bit
    config = config | 1;
    i2c_util_write_bytes(&acc, 0x2A, config, sizeof(config));
}

void configAccelerometer(){
    uint8_t config;
    config = 0x0;
    i2c_util_write_bytes(&acc, 0x2A, config, sizeof(config));
    config = 0x0;
    i2c_util_write_bytes(&acc, 0x2A, config, sizeof(config));

    config = 1;
    i2c_util_write_bytes(&acc, 0x2A, config, sizeof(config));

    uint8_t data;
    i2c_util_read_bytes(&acc, 0x2B, data, 1);
    printk("Acc: CTRL = %d\n", config);

}

void read_from_accelerometer(uint16_t *dst){
    static uint8_t data[6];

    accelerometer_standby();

    //clear FRead bit in CTRL1
    i2c_util_read_bytes(&acc, 0x2A, data, 1);
    data[0] = data[0] | ~1;
    i2c_util_write_bytes(&acc, 0x2A, data[0], 1);

    accelerometer_active();

    i2c_util_read_bytes(&acc, 0x01, data, 6);

    for(int i = 0; i < 6; i+=2){
        dst[i/2] = (data[i+1] << 8) | data[i];
    }


    printk("Acc: X = %d, ", (data[1] << 8) | data[0]);

    printk("Y = %d, ", (data[3] << 8) | data[2]);

    printk("Z = %d\n", (data[5] << 8) | data[4]);

    //return (data[1] << 8) | data[0];
}
