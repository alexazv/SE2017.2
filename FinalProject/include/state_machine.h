#ifndef STATE_MACHINE_FINALPROJECT_H
#define STATE_MACHINE_FINALPROJECT_H

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


void state_machine_change_state(event_t event);

void scroll_Text(void);

void action(void);

void show_temperature(void);

void show_accelerometer();

void show_compass();

mstate_t * get_current_state();

#endif //STATE_MACHINE_FINALPROJECT_H
