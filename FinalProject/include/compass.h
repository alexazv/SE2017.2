#ifndef COMPASS_FINALPROJECT_H
#define COMPASS_FINALPROJECT_H

#include <stdint.h>
#include "math.h"
#include "display.h"
#include <misc/printk.h>
#include "version.h"
#include "i2c_util.h"

typedef enum {
    NORTH,
    WEST,
    SOUTH,
    EAST,
    NORTHWEST,
    NORTHTEAST,
    SOUTHWEST,
    SOUTHEAST,
    UNDEFINED
} direction_t;

direction_t calculate_direction(int16_t *data);

struct mb_display * direction_sprite(direction_t direction);

void compass_init();

void read_from_compass(int16_t *dst);

#endif //COMPASS_FINALPROJECT_H

