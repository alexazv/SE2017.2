//Code created by Alexandre Azevedo
//18/05/2018

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
#include "button.h"

#define SCREEN_DURATION 300

typedef enum {
    TEXT_DISPLAY,
    ACCELEROMETER,
    COMPASS,
    THERMOMETER,
    BLUETOOTH
} state_t;

typedef enum {
    BUTTON_A,
    BUTTON_B
} event_t;


typedef struct {
    const char * state_name;
    state_t events[2];
    void (*action)(void);
} mstate_t;

static event_t ce;
volatile static int event_changed;


void buttonA_pressed(struct device *gpiob, struct gpio_callback *cb,
            u32_t pins)
{
    ce = BUTTON_A;
    event_changed = 1;
    printk("Button A pressed\n");
}

void buttonB_pressed(struct device *gpiob, struct gpio_callback *cb,
            u32_t pins)
{
    ce = BUTTON_B;
    event_changed = 1;
    printk("Button B pressed %d\n", event_changed);
}

void scrollText(){
    print_string_to_display("ECOM042.2017.2", SCREEN_DURATION);
}

void showTemperature(){

    double temperature = get_temperature_as_double();

    print_double_to_display(temperature, SCREEN_DURATION);
}

//placeholder
void action(){
    print_string_to_display("PLACEHOLDER", SCREEN_DURATION);
}

int main(){

    button_configure();
    button_A_set_callback(buttonA_pressed);
    button_B_set_callback(buttonB_pressed);


    //static state_t cs = TEXT_DISPLAY;
    static state_t cs = THERMOMETER;

    mstate_t machine[] = {{.state_name = "Text Display", .events = {BLUETOOTH, ACCELEROMETER}, .action = scrollText},
                          {.state_name = "Accelerometer", .events = {TEXT_DISPLAY, COMPASS}, .action = action},
                          {.state_name = "Compass", .events = {ACCELEROMETER, THERMOMETER}, .action = action},
                          {.state_name = "Thermometer", .events = {COMPASS, BLUETOOTH}, .action = showTemperature},
                          {.state_name = "Bluetooth", .events = {THERMOMETER, TEXT_DISPLAY}, .action = action}};

    event_changed = 0;

    machine[cs].action();
    while(1) {
           if(event_changed) {
               cs = machine[cs].events[ce];
               printk("State changed to: %s\n", machine[cs].state_name);
               clear_display();
               machine[cs].action();
               event_changed = 0;
           }
    }

    return 0;
}
