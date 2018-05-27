/**
 *  @file    display.c
 *  @author  Alexandre Azevedo
 *  @date    27/05/2018
 *
 */


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
} compass_raw_data_t;


/**
 * @brief calculate_direction
 *
 * Calculate north direction based on raw
 * magnetometer data
 *
 * @param data
 * Raw magnetometer data
 *
 * @return
 * The calculated cardinal direction
 */
direction_t calculate_direction(compass_raw_data_t *data);

/**
 * @brief show_compass
 * Show direction of magnetic north on the display
 */
void show_compass(void);

/**
 * @brief compass_direction_sprite_get
 * Get the sprite for a cardinal direction to be shown on the display
 * @param direction
 * Cardinal direction requested
 * @return
 * Sprite for the cardinal direction
 */
struct mb_display * compass_direction_sprite_get(direction_t direction);

#endif //COMPASS_FINALPROJECT_H

