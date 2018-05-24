#ifndef COMPASS_DIRECTION_FINALPROJECT_H
#define COMPASS_DIRECTION_FINALPROJECT_H

#include <stdint.h>
#include "math.h"
#include "display.h"
#include <misc/printk.h>

typedef enum {
    NORTH,
    WEST,
    SOUTH,
    EAST,
    NORTHWEST,
    NORTHTEAST,
    SOUTHWEST,
    SOUTHEAST
} direction_t;

direction_t calculate_direction(int16_t *data);

struct mb_display * direction_sprite(direction_t direction);

#endif //COMPASS_DIRECTION_FINALPROJECT_H
