//Code by Alexandre Azevedo
//Code created in 19/05/2018

#ifndef DISPLAY_FINALPROJECT_H
#define DISPLAY_FINALPROJECT_H

#define SCREEN_DURATION 300

#include <zephyr.h>
#include <misc/printk.h>
#include <board.h>
#include <gpio.h>
#include <device.h>
#include <display/mb_display.h>


/**
 * @brief print_string_to_display
 * Scrolls text on the display
 * @param text - Text to be shown
 * @param ms_duration - Duration of one character
 */
void print_string_to_display(const char * text, int ms_duration);

/**
 * @brief print_int_to_display
 * Scrolls a number on the screen
 * @param number Integer to be shown on the display
 * @param ms_duration - Duration of one character
 */
void print_int_to_display(uint8_t number, int ms_duration);

/**
 * @brief print_double_to_display
 * Displays a floating-point number on the display
 * @param number - Double to be shown on display
 * @param ms_duration - Duration of one character
 */
void print_double_to_display(double number, int ms_duration);

/**
 * @brief print_image_to_display
 * Shows an image on the display for 1 second
 * @param img - Image to be displayed
 */
void print_image_to_display(const struct mb_image *img);

/**
 * @brief clear_display
 *
 * Resets the display
 *
 */
void clear_display();

#endif //DISPLAY_FINALPROJECT_H
