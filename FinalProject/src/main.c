#include stdio.h

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
    state_t events[2];
    void (*action)(void);
} mstate_t;

static event_t ce = STOP;
static int event_changed = 0;

void ISR() {
    //ce = *;
}

void action(){}

int main(){

    static state_t cs = TEXT_DISPLAY;

    mstate_t machine[] = {{.events = {BLUETOOTH, ACCELEROMETER}, .action = action},
                          {.events = {TEXT_DISPLAY, COMPASS}, .action = action},
                          {.events = {ACCELEROMETER, THERMOMETER}, .action = action},
                          {.events = [COMPASS, BLUETOOTH], .action = action},
                          {.events = {THERMOMETER, TEXT_DISPLAY}, .action = action}};

    while(1) {
           if(event_changed) {
               cs = machine[cs].events[ce];
           }

           machine[cs].action();
       }
       return 0;

    return 0;
}
