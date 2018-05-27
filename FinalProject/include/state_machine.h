/**
 *  @file    display.c
 *  @author  Alexandre Azevedo
 *  @date    25/05/2018
 *
 */

#ifndef STATE_MACHINE_FINALPROJECT_H
#define STATE_MACHINE_FINALPROJECT_H

typedef
/**
/** * @brief state_t
 * Enum of possible device states
/** */
enum {
    TEXT_DISPLAY,
    ACCELEROMETER,
    COMPASS,
    THERMOMETER,
    BLUETOOTH
} state_t;


typedef
/**
/** * @brief event_t
 *  Enum of triggerable events
 *
/** */enum {
    BUTTON_A,
    BUTTON_B
} event_t;

typedef

struct {
    const char * state_name;
    state_t events[2];
    void (*action)(void);
} state_machine_t;

/**
 * @brief scroll_Text
 * Shows "ECOM042.2017.2" scrolling in the display
 */
void state_machine_change_state(event_t event);

void scroll_Text(void);

//TODO: implement bluetooth function
static void bluetooth(void);

/**
 * @brief
 *Shows current temperature in Celsius on the display
 */
void show_temperature(void);

/**
 * @brief get_current_state
 * Get the current machine state from the state machine
 * @return
 * Current machine state from the state machine
 */
state_machine_t * get_current_state(void);

#endif //STATE_MACHINE_FINALPROJECT_H
