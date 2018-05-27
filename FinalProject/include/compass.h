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

typedef union {
    struct {
        int16_t x;
        int16_t y;
        int16_t z;
    } axis;
    uint16_t data_signed[3];
    uint8_t data_raw[6];
} compass_raw_data;

direction_t calculate_direction(compass_raw_data *data);

struct mb_display * compass_direction_sprite_get(direction_t direction);

void compass_init(void);

void read_from_compass(compass_raw_data *data);

#endif //COMPASS_FINALPROJECT_H

