#ifndef BUTTON_FINALPROJECT_H
#define BUTTON_FINALPROJECT_H

#include <zephyr.h>
#include <board.h>
#include <device.h>
#include <gpio.h>
#include <misc/util.h>
#include <misc/printk.h>


//Configure Button A
/* change this to use another GPIO port */
#ifdef SW0_GPIO_NAME
#define PORT0	SW0_GPIO_NAME
#else
#error SW0_GPIO_NAME needs to be set in board.h
#endif

/* change this to use another GPIO pin */
#ifdef SW1_GPIO_PIN
#define PIN0     SW0_GPIO_PIN
#else
#error SW0_GPIO_PIN needs to be set in board.h
#endif

/* change to use another GPIO pin interrupt config */
#ifdef SW0_GPIO_INT_CONF
#define EDGE0    SW0_GPIO_INT_CONF
#else
/*
 * If SW0_GPIO_INT_CONF not defined used default EDGE value.
 * Change this to use a different interrupt trigger
 */
#define EDGE0    (GPIO_INT_EDGE | GPIO_INT_ACTIVE_LOW)
#endif

/* change this to enable pull-up/pull-down */
#ifdef SW1_GPIO_PIN_PUD
#define PULL_UP0 SW0_GPIO_PIN_PUD
#else
#define PULL_UP0 0
#endif


//Configure Button B
/* change this to use another GPIO port */
#ifdef SW1_GPIO_NAME
#define PORT1	SW1_GPIO_NAME
#else
#error SW1_GPIO_NAME needs to be set in board.h
#endif

/* change this to use another GPIO pin */
#ifdef SW1_GPIO_PIN
#define PIN1     SW1_GPIO_PIN
#else
#error SW1_GPIO_PIN needs to be set in board.h
#endif

/* change to use another GPIO pin interrupt config */
#ifdef SW1_GPIO_INT_CONF
#define EDGE1    SW1_GPIO_INT_CONF
#else
/*
 * If SW1_GPIO_INT_CONF not defined used default EDGE value.
 * Change this to use a different interrupt trigger
 */
#define EDGE1    (GPIO_INT_EDGE | GPIO_INT_ACTIVE_LOW)
#endif

/* change this to enable pull-up/pull-down */
#ifdef SW1_GPIO_PIN_PUD
//#define PULL_UP SW0_GPIO_PIN_PUD
#define PULL_UP1 SW1_GPIO_PIN_PUD
#else
#define PULL_UP1 0
#endif


/* Sleep time */
#define SLEEP_TIME	500

/**
 * @brief button_B_set_callback
 * Sets a ISR to be called when button B is triggered
 * @param callback - ISR to be called
 */
void button_A_set_callback(gpio_callback_handler_t callback);

/**
 * @brief button_A_set_callback
 * Sets a ISR to be called when button A is triggered
 * @param callback - ISR to be called
 */
void button_B_set_callback(gpio_callback_handler_t callback);

/**
 * @brief button_configure_init
 * Configure ports for buttons A and B
 *
 */
void button_configure_init(void);


#endif //DISPLAY_FINALPROJECT_H
