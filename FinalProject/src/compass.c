#include "compass.h"

#define COMPASS_DEV_ADDR     0x0e
#define COMPASS_WHO_AM_I_REG 0x07
#define COMPASS_TEST_VALUE   0xC4

#define PI 3.141592654

static struct i2c_dev compass;

void compass_init(){
    i2c_util_dev_init(&compass, COMPASS_DEV_ADDR, "COMPASS",
                            COMPASS_WHO_AM_I_REG, COMPASS_TEST_VALUE);
}

void compass_active(){

}

void configCompass(){
    uint8_t config;

    //standby
    config = 0;
    i2c_util_write_bytes(&compass, 0x10, &config, sizeof(config));

    //continuous read
    config = config =  0x80;
    i2c_util_write_bytes(&compass, 0x11, &config, sizeof(config));

    //wake
    config = 0x01;
    i2c_util_write_bytes(&compass, 0x10, &config, sizeof(config));
}

//dst must have at least 3 bytes
void read_from_compass(int16_t *dst){
    static uint8_t data[6];

    configCompass();

    i2c_util_read_bytes(&compass, 0x01, data, sizeof(data));

    for(int i = 0; i < 6; i+=2){
        dst[i/2] = (data[i] << 8) | data[i+1];
    }

    printk("Compass: X = %d, ", dst[0]);

    printk("Y = %d, ", dst[1]);

    printk("Z = %d\n", dst[2]);
}

direction_t calculate_direction(int16_t * data){
    double_t x = data[0];
    double_t y = data[1];

    double_t angle = x == 0? (y < 0 ? 90 : 0) : (atan(y/x)*180.0)/PI;

    if(angle < 0)
        angle = 360 + angle;

    if(angle >= 337.25 || angle < 22.5)
        return NORTH;
    else if(angle >= 292.5 && angle < 337.25)
        return NORTHWEST;
    else if(angle >= 247.5 && angle < 292.5)
        return WEST;
    else if(angle >= 202.5 && angle < 247.5)
        return SOUTHWEST;
    else if(angle >= 157.5 && angle < 202.5)
        return SOUTH;
    else if(angle >= 112.5 && angle < 157.5)
        return SOUTHEAST;
    else if(angle >= 67.5 && angle < 112.5)
        return EAST;
    else if(angle >= 0 && angle < 67.5)
        return NORTHTEAST;
    else
        return UNDEFINED;

}

static struct mb_image north  = MB_IMAGE({ 0, 0, 1, 0, 0 },
                                    { 0, 0, 1, 0, 0 },
                                    { 0, 0, 1, 0, 0 },
                                    { 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0 });
static struct mb_image south  = MB_IMAGE({ 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0 },
                                    { 0, 0, 1, 0, 0 },
                                    { 0, 0, 1, 0, 0 },
                                    { 0, 0, 1, 0, 0 });

static struct mb_image west  = MB_IMAGE({ 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0 },
                                    { 1, 1, 1, 0, 0 },
                                    { 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0 });

static struct mb_image east  = MB_IMAGE({ 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0 },
                                    { 0, 0, 1, 1, 1 },
                                    { 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0 });

static struct mb_image north_west  = MB_IMAGE({ 1, 0, 0, 0, 0 },
                                    { 0, 1, 0, 0, 0 },
                                    { 0, 0, 1, 0, 0 },
                                    { 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0 });

static struct mb_image north_east  = MB_IMAGE({ 0, 0, 0, 0, 1 },
                                    { 0, 0, 0, 1, 0 },
                                    { 0, 0, 1, 0, 0 },
                                    { 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0 });

static struct mb_image south_west  = MB_IMAGE({ 1, 0, 0, 0, 0 },
                                    { 0, 1, 0, 0, 0 },
                                    { 0, 0, 1, 0, 0 },
                                    { 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0 });

static struct mb_image south_east  = MB_IMAGE({ 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0 },
                                    { 0, 0, 1, 0, 0 },
                                    { 0, 0, 0, 1, 0 },
                                    { 0, 0, 0, 0, 1 });
static struct mb_image undefined  = MB_IMAGE({ 0, 0, 1, 0, 0 },
                                    { 0, 0, 1, 0, 0 },
                                    { 1, 1, 1, 1, 1 },
                                    { 0, 0, 1, 0, 0 },
                                    { 0, 0, 1, 0, 0 });

static struct mb_image * direction_sprites[] = {&north, &west, &south, &east,
                                        &north_west, &north_east,
                                         &south_west, &south_east, &undefined};

struct mb_display * direction_sprite(direction_t direction){

    //printk("%d\n", direction);
    return direction_sprites[direction];
}

