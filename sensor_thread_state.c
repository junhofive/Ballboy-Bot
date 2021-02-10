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

#define BUFFER_SIZE 50

typedef enum {
    TIMER70_MESSAGE,
    TIMER500_MESSAGE
} messageType;

typedef enum {
    INIT_AVERAGE,
    UPDATE_AVERAGE
} threadState;

static int sensorTotal = 0, sensorCount = 0;
static threadState currentState = INIT_AVERAGE;

void enterStateMachine(SensorThreadMessage *receivedMessage) {

    messageType newMessage;
    if (strcmp(receivedMessage->message_type, "TIMER70_MESSAGE") == 0) {
        newMessage = TIMER70_MESSAGE;
    }
    if (strcmp(receivedMessage->message_type, "TIMER500_MESSAGE") == 0) {
        newMessage = TIMER500_MESSAGE;
    }
    switch (currentState) {
        case INIT_AVERAGE:
            dbgEvent(ENTERING_INIT_AVERAGE);
            if (newMessage == TIMER500_MESSAGE) {
                currentState = UPDATE_AVERAGE;
            }
            dbgEvent(LEAVING_INIT_AVERAGE);
            break;
        case UPDATE_AVERAGE:
            dbgEvent(ENTERING_UPDATE_AVERAGE);
            if (newMessage == TIMER70_MESSAGE) {
                if (receivedMessage->value != NULL) {
                    sensorCount += 1;
                    sensorTotal += receivedMessage->value;
                    char messageBuffer[BUFFER_SIZE];
                    snprintf(messageBuffer, BUFFER_SIZE, "Sensor = %d %d\n", receivedMessage->value, sensorCount);
                    // Send to UART queue

                }
            }
            if (newMessage == TIMER500_MESSAGE) {
                int averageSensorValue = 0;

                if (sensorCount != 0) {
                    averageSensorValue = sensorTotal / sensorCount;
                }

                char messageBuffer[BUFFER_SIZE];
                snprintf(messageBuffer, BUFFER_SIZE, "Sensor Avg = %d; Time = %d\n", averageSensorValue, receivedMessage->value);
                // Send to UART queue

                currentState = INIT_AVERAGE;
            }
            dbgEvent(LEAVING_UPDATE_AVERAGE);
            break;
    }
}
