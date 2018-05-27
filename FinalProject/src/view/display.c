/**
 *  @file    display.c
 *  @author  Alexandre Azevedo
 *  @date    25/05/2018
 *
 */

#include "display.h"
#include <stdlib.h>

static struct mb_display *disp;


void print_string_to_display(const char * text, int ms_duration)
{
    disp = mb_display_get();

	mb_display_print(disp, MB_DISPLAY_MODE_DEFAULT | MB_DISPLAY_FLAG_LOOP,
             K_MSEC(ms_duration), text);
}


void print_int_to_display(uint8_t number, int ms_duration)
{
    disp = mb_display_get();

    char text[10];

    snprintf(text, 10, "%d", number);

    mb_display_print(disp, MB_DISPLAY_MODE_DEFAULT | MB_DISPLAY_FLAG_LOOP,
             K_MSEC(ms_duration), text);
}


void print_double_to_display(double number, int ms_duration)
{
    disp = mb_display_get();

    char text[10];

    snprintf(text, 10, "%.2f", number);

    mb_display_print(disp, MB_DISPLAY_MODE_DEFAULT | MB_DISPLAY_FLAG_LOOP,
             K_MSEC(ms_duration), text);
}

void clear_display(){
    disp = mb_display_get();
    mb_display_stop(disp);
}


void print_image_to_display(const struct mb_image *img){
    disp = mb_display_get();
    mb_display_image(disp, MB_DISPLAY_MODE_SINGLE,
                         K_SECONDS(1), img, 1);
}
