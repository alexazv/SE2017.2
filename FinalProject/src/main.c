//Code created by Alexandre Azevedo
//18/05/2018

#include "button.h"
#include "state_machine.h"

static event_t ce;
volatile static int event_changed;

/**
 * @brief buttonA_pressed
 * ISR to be called when button A is pressed
 *
 * @param gpiob
 * @param cb
 * @param pins
 */
void buttonA_pressed(struct device *gpiob, struct gpio_callback *cb,
            u32_t pins)
{
    state_machine_change_state(BUTTON_A);
    /*ce = BUTTON_A;
    event_changed = 1;
    k_wakeup(k_current_get());
    clear_display();*/
    printk("Button A pressed\n");
}
/**
 * @brief buttonB_pressed
 * ISR to be called when button B is pressed
 * @param gpiob
 * @param cb
 * @param pins
 */
void buttonB_pressed(struct device *gpiob, struct gpio_callback *cb,
            u32_t pins)
{
    ce = BUTTON_B;
    state_machine_change_state(BUTTON_B);
    //event_changed = 1;
    //k_wakeup(k_current_get());
    //clear_display();
    printk("Button B pressed\n");
}

int main(){

   /*SYS_LOG_WRN("Firmware version: v%d.%d.%d",
                   VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD);*/

    button_configure_init();
    button_A_set_callback(buttonA_pressed);
    button_B_set_callback(buttonB_pressed);

    compass_init();
    accelerometer_init();

    while(1){

        get_current_state()->action();

    }


    return 0;
}

