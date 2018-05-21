/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "display.h"
#include <stdlib.h>

static struct mb_display *disp;

void print_string_to_display(const char * text, int ms_duration)
{
    disp = mb_display_get();

    /* Show some scrolling text */
	mb_display_print(disp, MB_DISPLAY_MODE_DEFAULT | MB_DISPLAY_FLAG_LOOP,
             K_MSEC(ms_duration), text);
}

void print_double_to_display(double number, int ms_duration)
{
    disp = mb_display_get();

    char text[10];

    snprintf(text, 50, "%.2g", number);

    mb_display_print(disp, MB_DISPLAY_MODE_DEFAULT | MB_DISPLAY_FLAG_LOOP,
             K_MSEC(ms_duration), text);
}

void clear_display(){
    disp = mb_display_get();
    mb_display_stop(disp);
}
