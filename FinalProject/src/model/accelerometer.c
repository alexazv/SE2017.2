#include "accelerometer.h"

#define PI 3.141592654

#define MIN 20
#define MIDDLE 45

static struct mb_image map  = MB_IMAGE({ 0, 0, 0, 0, 0 },
                                        { 0, 0, 0, 0, 0 },
                                        { 0, 0, 0, 0, 0 },
                                        { 0, 0, 0, 0, 0 },
                                        { 0, 0, 0, 0, 0 });


void calculate_tilt(accelerometer_raw_data *data){

    double_t x_g = (double_t) (data->axis.x);//-1000.0;
    double_t y_g = (double_t) (data->axis.y);//-35.0;
    double_t z_g = (double_t) (data->axis.z);//-700.0;

    double_t roll = (atan2(y_g, (z_g >= 0 ? 1 : -1)*sqrt((x_g * x_g) + (z_g * z_g))) * 180.0)/PI;
    double_t pitch = (atan2(-x_g, sqrt((y_g * y_g) + (z_g * z_g))) * 180.0)/PI;

    printk("pitch = %d, roll = %d\n", (int)pitch, (int)roll);

    print_tilt(roll, pitch);
}


void print_tilt(double_t roll, double_t pitch){


    //positioned center of the screen
    int column, row;

    if(roll <= MIN){
        row = 2;
    } else if(MIN < roll && roll < MIDDLE){
        row = 4;
    } else{
        row = 0;
    }

    if(pitch <= MIN){
        column = 2;
    } else if(MIN < pitch && pitch < MIDDLE){
        column = 4;
    } else{
        column = 0;
    }

    map.row[row] = (1 << column);

    print_image_to_display(&map);

    map.row[row] = 0;
}

void show_accelerometer(void){
    accelerometer_raw_data data;
    read_from_accelerometer(data.data_raw);

    for(int i = 0; i < 6; i+=2){
        data.data_signed[i/2] = (data.data_raw[i] << 2) | (data.data_raw[i+1] >> 6);
    }

    printk("x =%d, y =%d, z=%d\n", data.axis.x, data.axis.y, data.axis.z);

    calculate_tilt(&data);
    k_sleep(SCREEN_DURATION);
}
