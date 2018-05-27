/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "display.h"
#include <stdlib.h>

static struct mb_display *disp;

/**
 * @brief print_string_to_display
 * Scrolls text on the display
 * @param text - Text to be shown
 * @param ms_duration - Duration of one character
 */
void print_string_to_display(const char * text, int ms_duration)
{
    disp = mb_display_get();

	mb_display_print(disp, MB_DISPLAY_MODE_DEFAULT | MB_DISPLAY_FLAG_LOOP,
             K_MSEC(ms_duration), text);
}

/**
 * @brief print_int_to_display
 * Scrolls a number on the screen
 * @param number Integer to be shown on the display
 * @param ms_duration - Duration of one character
 */
void print_int_to_display(uint8_t number, int ms_duration)
{
    disp = mb_display_get();

    char text[10];

    snprintf(text, 10, "%d", number);

    mb_display_print(disp, MB_DISPLAY_MODE_DEFAULT | MB_DISPLAY_FLAG_LOOP,
             K_MSEC(ms_duration), text);
}

/**
 * @brief print_double_to_display
 * Displays a floating-point number on the display
 * @param number - Double to be shown on display
 * @param ms_duration - Duration of one character
 */
void print_double_to_display(double number, int ms_duration)
{
    disp = mb_display_get();

    char text[10];

    //int success =
            snprintf(text, 10, "%d", (int)number);

    //printk("%d\n", success);

    mb_display_print(disp, MB_DISPLAY_MODE_DEFAULT | MB_DISPLAY_FLAG_LOOP,
             K_MSEC(ms_duration), text);
}

void clear_display(){
    disp = mb_display_get();
    mb_display_stop(disp);
}

/**
 * @brief print_image_to_display
 * Shows an image on the display for 1 second
 * @param img - Image to be displayed
 */
void print_image_to_display(const struct mb_image *img){
    disp = mb_display_get();
    mb_display_image(disp, MB_DISPLAY_MODE_SINGLE,
                         K_SECONDS(1), img, 1);
        //k_sleep(K_SECONDS(1));
}
