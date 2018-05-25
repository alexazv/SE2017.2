#include "compass_direction.h"

#define PI 3.141592654

direction_t calculate_direction(int16_t * data){
    double_t x = data[0];
    double_t y = data[1];

    double_t angle = x == 0? (y < 0 ? 90 : 0) : atan(y/x)*(180.0/PI);

    if(angle >= 337.25 || angle < 22.5)
        return NORTH;
    else if(angle >= 0 && angle < 67.5)
        return NORTHTEAST;
    else if(angle >= 67.5 && angle < 112.5)
        return EAST;
    else if(angle >= 112.5 && angle < 157.5)
        return SOUTHEAST;
    else if(angle >= 157.5 && angle < 202.5)
        return SOUTH;
    else if(angle >= 202.5 && angle < 247.5)
        return SOUTHWEST;
    else if(angle >= 247.5 && angle < 292.5)
        return WEST;
    else
        return NORTHWEST;
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

static struct mb_image * direction_sprites[] = {&north, &west, &south, &east,
                                        &north_west, &north_east,
                                         &south_west, &south_east};

struct mb_display * direction_sprite(direction_t direction){
    return direction_sprites[direction];
}
