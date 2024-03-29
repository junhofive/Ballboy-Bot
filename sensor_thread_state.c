/*
 * sensor_thread_state.c
 *
 *  Created on: Feb 9, 2021
 *      Author: JO_Desktop
 */

#include "sensor_thread_state.h"
#include "uart_thread_queue.h"
#include "sensor_task.h"
#include "debug.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <ti/drivers/dpl/HwiP.h>

typedef enum {
    INIT_AVERAGE,
    UPDATE_AVERAGE
} threadState;

static int sensorTotal = 0, sensorCount = 0;
static threadState currentState = INIT_AVERAGE;

void enterStateMachine(SensorThreadMessage *receivedMessage) {

    switch (currentState) {
        case INIT_AVERAGE:
            dbgEvent(INIT_AVERAGE_STATE);
            if (receivedMessage->message_type == TIMER500_MESSAGE) {
                currentState = UPDATE_AVERAGE;
                dbgEvent(LEAVE_INIT_AVERAGE_STATE);
            }

            break;
        case UPDATE_AVERAGE:
            dbgEvent(UPDATE_AVERAGE_STATE);
            if (receivedMessage->message_type == TIMER70_MESSAGE) {
                if (receivedMessage->value != NULL) {
                    sensorCount += 1;
                    sensorTotal += receivedMessage->value;
                    static char messageBuffer[BUFFER_SIZE];
                    snprintf(messageBuffer, BUFFER_SIZE, "Sensor = %d %d\n", receivedMessage->value, sensorCount);
                    // Send to UART queue
                    UartThreadMessage sendMessage;
                    strcpy(sendMessage.message, messageBuffer);
                    dbgEvent(BEFORE_SEND_TYPE70_MSG);
                    sendToUartThreadQueue(&sendMessage);
                    dbgEvent(AFTER_SEND_TYPE70_MSG);
                }
            }
            if (receivedMessage->message_type == TIMER500_MESSAGE) {
                int averageSensorValue = 0;

                if (sensorCount != 0) {
                    averageSensorValue = sensorTotal / sensorCount;
                }

                static char messageBuffer[BUFFER_SIZE];
                snprintf(messageBuffer, BUFFER_SIZE, "Sensor Avg = %d; Time = %d\n", averageSensorValue, receivedMessage->value);
                // Send to UART queue
                UartThreadMessage sendMessage;
                strcpy(sendMessage.message, messageBuffer);
                dbgEvent(BEFORE_SEND_TYPE500_MSG);
                sendToUartThreadQueue(&sendMessage);
                dbgEvent(AFTER_SEND_TYPE500_MSG);

                dbgEvent(LEAVE_UPDATE_AVERAGE_STATE);
                currentState = INIT_AVERAGE;

            }

            break;
    }
}
