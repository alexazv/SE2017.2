#ifndef STATE_MACHINE_FINALPROJECT_H
#define STATE_MACHINE_FINALPROJECT_H

typedef enum {
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
} mstate_t;

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
mstate_t * get_current_state(void);

#endif //STATE_MACHINE_FINALPROJECT_H
