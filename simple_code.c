/*
 * Copyright (c) 2015-2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== uartecho.c ========
 */
#include <pthread.h>
#include <stdint.h>
#include <stddef.h>
#include <FreeRTOS.h>
#include <task.h>
#include "debug.h"
#include "sensor_task.h"
#include "uart_task.h"
#include "sensor_thread_queue.h"
#include "uart_thread_queue.h"
#include "timer70.h"
#include "timer500.h"

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/ADC.h>
#include <ti/drivers/Timer.h>

/* Driver configuration */
#include "ti_drivers_config.h"

#define THREADSTACKSIZE   (768)

/*
 *  ======== mainThread ========
 */
void setAllGPIOsToZero() {
    GPIO_write(CONFIG_GPIO_7, 0);
    GPIO_write(CONFIG_GPIO_6, 0);
    GPIO_write(CONFIG_GPIO_5, 0);
    GPIO_write(CONFIG_GPIO_4, 0);
    GPIO_write(CONFIG_GPIO_3, 0);
    GPIO_write(CONFIG_GPIO_2, 0);
    GPIO_write(CONFIG_GPIO_1, 0);
    GPIO_write(CONFIG_GPIO_0, 0);
}

void *mainThread(void *arg0)
{
    dbgEvent(ENTER_MAIN_THREAD);
#if 0
    pthread_t           timer70_thread, timer500_thread, sensor_thread, uart_thread;
    pthread_attr_t      attrs;
    struct sched_param  priParam;
    int                 retc;
#endif
    pthread_t           timer70_thread, timer500_thread, sensor_thread, uart_thread;
    pthread_attr_t      attrs;
    struct sched_param  priParam;
    int                 retc;
    int                 detachState;

    /* Call driver init functions */

    UART_init();
    ADC_init();
    Timer_init();

    setAllGPIOsToZero();

#if 0
    pthread_attr_init(&attrs);
    detachState = PTHREAD_CREATE_DETACHED;
    retc = pthread_attr_setdetachstate(&attrs, detachState);
    if (retc != 0) {
        /* pthread_attr_setdetachstate() failed */
        while (1);
    }
    retc |= pthread_attr_setstacksize(&attrs, THREADSTACKSIZE);
    if (retc != 0) {
        /* pthread_attr_setstacksize() failed */
        while (1);
    }
    priParam.sched_priority = 1;
    pthread_attr_setschedparam(&attrs, &priParam);
    retc = pthread_create(&timer500_thread, &attrs, timer500Thread, NULL);
    if (retc != 0) {
        /* pthread_create() failed */
        while (1);
    }
#endif


    pthread_attr_init(&attrs);
    priParam.sched_priority = 1;
    retc = pthread_attr_setschedparam(&attrs, &priParam);
    retc |= pthread_attr_setstacksize(&attrs, THREADSTACKSIZE);
    retc = pthread_create(&timer70_thread, &attrs, timer70Thread, NULL);

    if (retc != 0) {
        /* pthread_create() failed */
        handleFatalError(PTHREAD_NOT_CREATED);
    }

    retc = pthread_create(&timer500_thread, &attrs, timer500Thread, NULL);
    if (retc != 0) {
        /* pthread_create() failed */
        handleFatalError(PTHREAD_NOT_CREATED);
    }

    retc = pthread_create(&sensor_thread, &attrs, sensor_task, NULL);
    if (retc != 0) {
        /* pthread_create() failed */
        handleFatalError(PTHREAD_NOT_CREATED);
    }
#if 0
    retc = pthread_create(&uart_thread, &attrs, uart_task, NULL);
    if (retc != 0) {
        /* pthread_create() failed */
        handleFatalError(PTHREAD_NOT_CREATED);
    }
#endif
    return (NULL);
}
