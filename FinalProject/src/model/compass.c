#include "compass.h"
#include "i2c_device.h"
#include "display.h"

#define PI 3.141592654

direction_t calculate_direction(compass_raw_data *data){

    printk("Compass: X = %d, ", data->axis.x);
    printk("Y = %d, ", data->axis.y);
    printk("Z = %d, ", data->axis.z);

    double_t x = data->axis.x;
    double_t y = data->axis.y;

    double_t angle = -(atan2(y, x)*180.0)/PI;

    printk("angle = %d\n", (int)angle);

    if(angle < 0)
        angle = 360 + angle;

    if(angle >= 337.5 || angle < 22.5)
        return NORTH;
    else if(angle >= 292.5 && angle < 337.5)
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
    else if(angle >= 22.5 && angle < 67.5)
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

struct mb_display * compass_direction_sprite_get(direction_t direction){

    //printk("%d\n", direction);
    return direction_sprites[direction];
}


void show_compass(void){
   compass_raw_data data;
   read_from_compass(data.data_raw);

   printk("Compass: X = %d, ", data.axis.x);

   printk("Y = %d, ", data.axis.y);

   printk("Z = %d\n", data.axis.z);

   print_image_to_display(
               compass_direction_sprite_get(calculate_direction(&data)));
   k_sleep(100);
}
