/*
 * debug.c
 *
 *  Created on: Feb 9, 2021
 *      Author: Terry Li
 */

// Refer to decimal to binary document:C Program to convert Decimal to Binary, URL: https://www.javatpoint.com/c-program-to-convert-decimal-to-binary

#include <stdint.h>
#include <stddef.h>
#include <ti/drivers/GPIO.h>
#include "ti_drivers_config.h"

void dbgEvent(unsigned int event){

    GPIO_init();
    unsigned int digit = 0;
    // check if the value of the event is valid
    if (event <= 127){

        // set the 8th ping high
        GPIO_write(CONFIG_GPIO_7, 1);

        while (event != 0){
            int value = event % 2;
            event = event / 2;

            // set the corresponding digit to value
            if (digit == 0){
                GPIO_write(CONFIG_GPIO_0, value);
            }
            if (digit == 1){
                GPIO_write(CONFIG_GPIO_1, value);
            }
            if (digit == 2){
                GPIO_write(CONFIG_GPIO_2, value);
            }
            if (digit == 3){
                GPIO_write(CONFIG_GPIO_3, value);
            }
            if (digit == 4){
                GPIO_write(CONFIG_GPIO_4, value);
            }
            if (digit == 5){
                GPIO_write(CONFIG_GPIO_5, value);
            }
            if (digit == 6){
                GPIO_write(CONFIG_GPIO_6, value);
            }
            digit += 1;
        }

        // set the 8th ping low after the event is written
        GPIO_write(CONFIG_GPIO_7, 0);
    }
    else{
        // fail
    }
}

