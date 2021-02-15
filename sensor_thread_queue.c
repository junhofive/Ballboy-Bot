/*
 * sensor_thread_queue.c
 *
 *  Created on: Feb 6, 2021
 *      Author: JO_Desktop
 */

#include "sensor_thread_queue.h"
#include "timer70.h"
#include "debug.h"

#define QUEUE_LENGTH 50
/* Static Variable */
static QueueHandle_t sensor_thread_queue = NULL;

void createSensorThreadQueue() {
    sensor_thread_queue = xQueueCreate(QUEUE_LENGTH, sizeof(SensorThreadMessage));

    if (sensor_thread_queue == NULL) {
        //error handling
        handleFatalError(SENSOR_QUEUE_NOT_CREATED);
    }
}

void receiveFromSensorThreadQueue(SensorThreadMessage* receivedMsg) {
    if (xQueueReceive(sensor_thread_queue, receivedMsg, portMAX_DELAY)) {

    }
    else {
        //Error, proceed to stop
        handleFatalError(SENSOR_QUEUE_NOT_RECEIVED);
    }
}
#if 0
void sendToSensorThreadQueue(SensorThreadMessage* targetMsg) {
    if (xQueueSend(sensor_thread_queue, target, portMAX_DELAY)) {

    }
    else {
        //Error, proceed to stop
        handleFatalError(SENSOR_QUEUE_NOT_SENT);
    }
}
#endif
BaseType_t sendToSensorThreadQueueFromISR(SensorThreadMessage* targetMessage) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if (xQueueSendFromISR(sensor_thread_queue, targetMessage, &xHigherPriorityTaskWoken)) {

    }
    else{
        //error, proceed to stop
        handleFatalError(SENSOR_QUEUE_NOT_SENT);
    }
    return xHigherPriorityTaskWoken;
}

