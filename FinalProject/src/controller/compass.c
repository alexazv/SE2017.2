#include "compass.h"

#define COMPASS_DEV_ADDR     0x0e
#define COMPASS_WHO_AM_I_REG 0x07
#define COMPASS_TEST_VALUE   0xC4

#define PI 3.141592654

static struct i2c_dev compass;


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
void read_from_compass(compass_raw_data * data){

    configCompass();

    i2c_util_read_bytes(&compass, 0x01, data->data_raw, sizeof(data));

    /*for(int i = 0; i < 6; i+=2){
        data->data_signed[i/2] = (raw_data[i] << 8) | raw_data[i+1];
    }*/


    printk("Compass: X = %d, ", data->axis.x);

    printk("Y = %d, ", data->axis.y);

    printk("Z = %d\n", data->axis.z);

}


//TODO: change to x, y, z
direction_t calculate_direction(compass_raw_data *data){

    printk("Compass: X = %d, ", data->axis.x);

    printk("Y = %d, ", data->axis.y);

    printk("Z = %d\n", data->axis.z);

    double_t x = data->axis.x;
    double_t y = data->axis.y;

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

/**
 * @brief compass_direction_sprite_get
 * Get the sprite for a cardinal direction to be shown on the display
 * @param direction - cardinal direction requested
 * @return
 */
struct mb_display * compass_direction_sprite_get(direction_t direction){

    //printk("%d\n", direction);
    return direction_sprites[direction];
}

