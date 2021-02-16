/*
 * debug.c
 *
 *  Created on: Feb 9, 2021
 *      Author: Terry Li
 */

// Refer to decimal to binary document:C Program to convert Decimal to Binary, URL: https://www.javatpoint.com/c-program-to-convert-decimal-to-binary

#include "debug.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <ti/drivers/GPIO.h>
#include "ti_drivers_config.h"
#include <ti/drivers/Power.h>
#include <ti/drivers/UART.h>
#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>
#include <ti/drivers/dpl/HwiP.h>

void dbgEvent(unsigned int event) {
    if (event <= 127){
        GPIO_write(CONFIG_GPIO_7, 1);

        GPIO_write(CONFIG_GPIO_6, event & BIT_6);

        GPIO_write(CONFIG_GPIO_5, event & BIT_5);

        GPIO_write(CONFIG_GPIO_4, event & BIT_4);

        GPIO_write(CONFIG_GPIO_3, event & BIT_3);

        GPIO_write(CONFIG_GPIO_2, event & BIT_2);

        GPIO_write(CONFIG_GPIO_1, event & BIT_1);

        GPIO_write(CONFIG_GPIO_0, event & BIT_0);

        GPIO_write(CONFIG_GPIO_7, 0);
#if 0

        GPIO_write(CONFIG_GPIO_7, 1);

        if (event & BIT_SEVEN)
            GPIO_write(CONFIG_GPIO_6, 1);
        else
            GPIO_write(CONFIG_GPIO_6, 0);

        if (event & BIT_SIX)
            GPIO_write(CONFIG_GPIO_5, 1);
        else
            GPIO_write(CONFIG_GPIO_5, 0);

        if (event & BIT_FIVE)
            GPIO_write(CONFIG_GPIO_4, 1);
        else
            GPIO_write(CONFIG_GPIO_4, 0);

        if (event & BIT_FOUR)
            GPIO_write(CONFIG_GPIO_3, 1);
        else
            GPIO_write(CONFIG_GPIO_3, 0);

        if (event & BIT_THREE)
            GPIO_write(CONFIG_GPIO_2, 1);
        else
            GPIO_write(CONFIG_GPIO_2, 0);

        if (event & BIT_TWO)
            GPIO_write(CONFIG_GPIO_1, 1);
        else
            GPIO_write(CONFIG_GPIO_1, 0);

        if (event & BIT_ONE)
            GPIO_write(CONFIG_GPIO_0, 1);
        else
            GPIO_write(CONFIG_GPIO_0, 0);

        GPIO_write(CONFIG_GPIO_7, 0);
#endif
    }
    else{
        handleFatalError(event);
    }
}

void handleFatalError(unsigned int eventLabel) {


    /* Disable hardware interrupts */
    //enterCriticalSection();
    uintptr_t key1;
    key1 = HwiP_disable();

    /* Disable threads */
    vTaskSuspendAll();

    dbgEvent(eventLabel);

    // loop for blinking
    while (1) {
        GPIO_toggle(CONFIG_GPIO_LED_0);
    }
}

