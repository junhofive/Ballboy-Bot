/*
 * timer500.c
 * Editor: Tianyu Li
 */

#include "timer500.h"
#include <FreeRTOS.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <queue.h>
#include <FreeRTOSConfig.h>

#include <ti/drivers/ADC.h>
#include <ti/drivers/Timer.h>
#include <ti/drivers/GPIO.h>
#include "ti_drivers_config.h"

void timer500Callback(Timer_Handle myHandle, int_fast16_t status);

void *timer500Thread(void *arg0){
    // set the message type
    struct message msg;
    struct messgae *ptr_msg;
    ptr_msg = &msg; // set up a pointer to msg struct

    strcpy(msg.message_type, "TIMER500_MESSAGE");

    Timer_Handle timer500;
    Timer_Params params;

    Timer_init();

    Timer_Params_init(&params);
    params.period = 500000; // 500000 microsecond = 500 ms
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timer500Callback;

    timer500 = Timer_open(TIMER_500, &params);

    if (timer500 == NULL) {
       /* Failed to initialized timer */
       while (1) {}
    }

    if (Timer_start(timer500) == Timer_STATUS_ERROR) {
       /* Failed to start timer */
       while (1) {}
    }
}

/*
 * This is the callback function for timer 500.
 * Period = 500 ms
 */
void timer500Callback(Timer_Handle myHandle, int_fast16_t status, struct message *ptr_msg){
    bool inISR = HwiP_inISR(); // in order to determine in ISR or not

    TickType_t tick_count;
    if (inISR == True){
        tick_count = xTaskGetTickCountFromISR();
    }
    else{
        tick_count = xTaskGetTickCount();
    }

    // convert tick_count to microseconds
    // See FreeRTOSConfig.h for tick rate
    // Rate = 1000 Hz for now -> 1ms period -> 1000 microsecond
    int elapsed_time = 1000 * tick_count;

    ptr_msg->elapsed_time = elapsed_time;

    // send to message queue
    xQueueSendFromISR(SensorThreadMessage, ptr_msg);
}
