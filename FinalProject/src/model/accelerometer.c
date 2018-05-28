/**
 *  @file    display.c
 *  @author  Alexandre Azevedo
 *  @date    27/05/2018
 *
 */

#include "accelerometer.h"

#define PI 3.141592654

static struct mb_image map  = MB_IMAGE({ 0, 0, 0, 0, 0 },
                                        { 0, 0, 0, 0, 0 },
                                        { 0, 0, 0, 0, 0 },
                                        { 0, 0, 0, 0, 0 },
                                        { 0, 0, 0, 0, 0 });


void calculate_tilt(accelerometer_raw_data_t *data){

    double_t x_g = (double_t) (data->axis.x);
    double_t y_g = (double_t) (data->axis.y);
    double_t z_g = (double_t) (data->axis.z);

    double_t roll = (atan2(y_g, sqrt((x_g * x_g) + (z_g * z_g))) * 180.0)/PI;
    double_t pitch = (atan2(x_g, sqrt((y_g * y_g) + (z_g * z_g))) * 180.0)/PI;

    printk("pitch = %d, roll = %d\n", (int)pitch, (int)roll);

    print_tilt(roll, pitch);
}


void print_tilt(double_t roll, double_t pitch){


    //positioned center of the screen
    uint8_t column = 2, row = 2;

    if(7.5 <= roll && roll <= 15){
        //top
        row = 0;
    } else if(roll < 7.5 || (15 <= roll && roll <= 30)){
        //middlde
        row = 2;
    } else{
        //bottom
        row = 4;
    }

    if(7.5 <= pitch && pitch <= 15){
        //left
        column = 0;
    } else if(pitch < 7.5 || (15 <= pitch && pitch <= 30)){
        //middle
        column = 2;
    } else{
        //right
        column = 4;
    }


    map.row[row] = (1 << column);

    print_image_to_display(&map);

    map.row[row] = 0;
}

void show_accelerometer(void){
    accelerometer_raw_data_t data;
    read_from_accelerometer(data.data_raw);

    for(int i = 0; i < 6; i+=2){
        data.data_signed[i/2] = (data.data_raw[i] << 2) | (data.data_raw[i+1] >> 6);
    }

    printk("x =%d, y =%d, z=%d\n", data.axis.x, data.axis.y, data.axis.z);

    calculate_tilt(&data);
    k_sleep(SCREEN_DURATION/2);
}
