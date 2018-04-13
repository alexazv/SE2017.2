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

    {
        ICATCommandAddCommand("HEART", IC_LED_matrix_draw_heart, 0, NULL);
    }

    {
        ParameterTypes parameter[2] = {STRING, STRING};
        ICATCommandAddCommand("NAME", IC_LED_matrix_draw_name, 2, &parameter);

    }



    return 0;
}