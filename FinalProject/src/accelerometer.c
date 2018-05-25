#include "accelerometer.h"

#define ACC_DEV_ADDR     0x1D
#define ACC_WHO_AM_I_REG 0x0D
#define ACC_TEST_VALUE   0x5A

#define PI 3.141592654

static struct i2c_dev acc;

void accelerometer_init(){
    i2c_util_dev_init(&acc, ACC_DEV_ADDR, "ACC", ACC_WHO_AM_I_REG,
                            ACC_TEST_VALUE);

    uint8_t config;

    //accelerometer_standby();

    /*
    //clear FRead bit in CTRL1
    i2c_util_read_bytes(&acc, 0x2A, config, 1);
    config = config | ~1;
    i2c_util_write_bytes(&acc, 0x2A, config, 1);
*/
    accelerometer_active();
}

void accelerometer_standby(){
    uint8_t config;
    //clear active bit
    config = 0x00;
    i2c_util_write_bytes(&acc, 0x2A, &config, sizeof(config));

}

void accelerometer_active(){
    uint8_t config;
    //read from CTRL1
    //i2c_util_read_bytes(&acc, 0x2A, config, 1);

    //set active bit
    config = 0x01;//config | 1;
    i2c_util_write_bytes(&acc, 0x2A, &config, sizeof(config));
}



void read_from_accelerometer(int16_t *dst){
    static uint8_t data[6];

    i2c_util_read_bytes(&acc, 0x01, data, 6);

    for(int i = 0; i < 6; i+=2){
        dst[i/2] = data[i] << 2 | data[i+1] >> 6;
    }



    /*printk("Acc: X = %d, ", dst[0]);

    printk("Y = %d, ", dst[1]);

    printk("Z = %d\n", dst[2]);

    */

}

void calculate(int16_t x, int16_t y, int16_t z){

    printk("x = %d, y = %d, z = %d\n", x, y, z);

      double_t x_g = ((double_t) x)*0.0038;
      double_t y_g = ((double_t) y)*0.0038;
      double_t z_g = ((double_t )z)*0.0038;

      double_t roll = atan(y_g/z_g) * 180.0/PI;
      double_t pitch = atan(x_g/sqrt((y_g * y_g) + (z_g * z_g))) * 180.0/PI;

      printk("pitch = %d, roll = %d\n", (int)pitch, (int)roll);
}
