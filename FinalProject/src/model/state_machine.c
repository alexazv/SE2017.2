/**
 *  @file    display.c
 *  @author  Alexandre Azevedo
 *  @date    27/05/2018
 *
 */


#include "state_machine.h"
#include <stdint.h>

#include <stdio.h>
#include <zephyr.h>
#include <misc/printk.h>
#include <board.h>
#include <gpio.h>
#include <device.h>
#include <stdlib.h>

#include <display/mb_display.h>

#include "thermometer.h"
#include "display.h"
#include "compass.h"
#include "accelerometer.h"
#include "state_machine.h"

#define SCREEN_DURATION 300

static state_t current_state = TEXT_DISPLAY;
//static state_t cs = COMPASS;
//static state_t cs = ACCELEROMETER;

static state_machine_t machine[] = {{.state_name = "Text Display", .events = {BLUETOOTH, ACCELEROMETER}, .action = scroll_Text},
                       {.state_name = "Accelerometer", .events = {TEXT_DISPLAY, COMPASS}, .action = show_accelerometer},
                       {.state_name = "Compass", .events = {ACCELEROMETER, THERMOMETER}, .action = show_compass},
                       {.state_name = "Thermometer", .events = {COMPASS, BLUETOOTH}, .action = show_temperature},
                       {.state_name = "Bluetooth", .events = {THERMOMETER, TEXT_DISPLAY}, .action = bluetooth}};

void state_machine_change_state(event_t event){
    current_state = machine[current_state].events[event];
    printk("State changed to: %s\n", machine[current_state].state_name);
}


void scroll_Text(void){
    print_string_to_display("ECOM042.2017.2", SCREEN_DURATION);
    k_sleep(17*SCREEN_DURATION);
}

void bluetooth(void){
    print_string_to_display("BLE", SCREEN_DURATION);
    k_sleep(5*SCREEN_DURATION);
}


void show_temperature(void){

    uint8_t temperature = (uint8_t)thermometer_get_temperature_as_double();
    print_int_to_display(temperature, SCREEN_DURATION);
    k_sleep(6*SCREEN_DURATION);
}

state_machine_t * get_current_state(void){
     return &machine[current_state];
}
