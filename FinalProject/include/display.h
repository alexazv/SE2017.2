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

void print_string_to_screen(const char * text, int ms_duration);

void print_double_to_display(double number, int ms_duration);

#endif //DISPLAY_FINALPROJECT_H
