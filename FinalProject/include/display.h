//Code by Alexandre Azevedo
//Code created in 19/05/2018

#ifndef DISPLAY_FINALPROJECT_H
#define DISPLAY_FINALPROJECT_H

#include <zephyr.h>
#include <misc/printk.h>
#include <board.h>
#include <gpio.h>
#include <device.h>
#include <display/mb_display.h>

void print_string_to_display(const char * text, int ms_duration);

void print_int_to_display(uint8_t number, int ms_duration);

void print_double_to_display(double number, int ms_duration);

void print_image_to_display(const struct mb_image *img);

void clear_display();

#endif //DISPLAY_FINALPROJECT_H
