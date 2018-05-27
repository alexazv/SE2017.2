/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "button.h"

static struct gpio_callback gpio_cb0;
static struct gpio_callback gpio_cb1;
static struct device *gpiob0;
static struct device *gpiob1;

void button_A_set_callback(gpio_callback_handler_t callback){
    gpio_init_callback(&gpio_cb0, callback, BIT(PIN0));

    gpio_add_callback(gpiob0, &gpio_cb0);
    gpio_pin_enable_callback(gpiob0, PIN0);
}

void button_B_set_callback(gpio_callback_handler_t callback){
    gpio_init_callback(&gpio_cb1, callback, BIT(PIN1));

    gpio_add_callback(gpiob1, &gpio_cb1);
    gpio_pin_enable_callback(gpiob1, PIN1);
}

void button_configure_init(void){
    //printk("Press the user defined button on the board\n");
    gpiob0 = device_get_binding(PORT0);
    gpiob1 = device_get_binding(PORT1);
    if (!gpiob0) {
        printk("error at port 0\n");
        return;
    }

    if (!gpiob1) {
        printk("error at port 1\n");
        return;
    }

    gpio_pin_configure(gpiob0, PIN0,
               GPIO_DIR_IN | GPIO_INT |  PULL_UP0 | EDGE0);

    gpio_pin_configure(gpiob1, PIN1,
               GPIO_DIR_IN | GPIO_INT |  PULL_UP1 | EDGE1);

}
