#include "accelerometer.h"
#include <math.h>

#define PI 3.141592654

#define MIN 20
#define MIDDLE 45

static struct mb_image map  = MB_IMAGE({ 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0 });



/**
 * @brief calculate_tilt
 * Calculate roll and pitch of the device in degrees based on raw values
 * @param x_raw - raw x value
 * @param y_raw - raw y value
 * @param z_raw - raw z value
 */
void calculate_tilt(accelerometer_raw_data *data){

    double_t x_g = ((double_t) (data->axis.x >> 6))*0.0038;
    double_t y_g = ((double_t) (data->axis.y >> 6))*0.0038;
    double_t z_g = ((double_t) (data->axis.z >> 6))*0.0038;

    double_t roll = atan(y_g/sqrt((x_g * x_g) + (z_g * z_g))) * 180.0/PI;
    double_t pitch = atan(x_g/sqrt((y_g * y_g) + (z_g * z_g))) * 180.0/PI;

    printk("pitch = %d, roll = %d\n", (int)pitch, (int)roll);

    print_tilt(roll, pitch);
}


/**
 * @brief print_tilt
 * Show current tilt as a pixel on the display
 * @param roll - roll of device
 * @param pitch - pitch of the device
 */
void print_tilt(double_t roll, double_t pitch){

    //positioned center of center
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

/**
 * @brief show_accelerometer
 * Show current tilt as a pixel on the display
 */
void show_accelerometer(void){
    accelerometer_raw_data data;
    read_from_accelerometer(data.data_raw);

    for(int i = 0; i < 6; i+=2){
        data.data_signed[i/2] = data.data_raw[i] << 2 | data.data_raw[i+1] >> 6;
    }

    calculate_tilt(&data);
    k_sleep(SCREEN_DURATION);
}
