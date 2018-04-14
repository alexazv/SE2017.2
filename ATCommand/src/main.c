#include <stdio.h>
#include "ICATCommand.h"
#include "ICLEDMatrix.h"


int main() {

    IC_LED_matrix_init();
    printk("LEDMATRIX INITIALIZED\n");
    ICATCommandStart();

    //IC_LED_matrix_draw_heart((uint8_t**)NULL, 0);

    /*while(1){
        printk("I AM ALIVE");
    }*/

    ICATCommandAddCommand("HEART", IC_LED_matrix_draw_heart, 0, VOID);
    ICATCommandAddCommand("TIME", IC_LED_matrix_set_time_active, 1, INTEGER);
    ICATCommandAddCommand("HOURS", IC_LED_matrix_draw_hours, 2, INTEGER, INTEGER);
    ICATCommandAddCommand("STRING", IC_LED_matrix_draw_string, 1, STRING);
    ICATCommandAddCommand("NAME", IC_LED_matrix_draw_name, 2, STRING, STRING);
    ICATCommandAddCommand("DATE", IC_LED_matrix_draw_name, 3, INTEGER, STRING, INTEGER);

    //listCommands();

    return 0;
}