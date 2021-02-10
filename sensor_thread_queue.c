/*
 * sensor_thread_queue.c
 *
 *  Created on: Feb 6, 2021
 *      Author: JO_Desktop
 */

#include "sensor_thread_queue.h"
#include "timer70.h"

#define QUEUE_LENGTH 10
/* Static Variable */
static QueueHandle_t sensor_thread_queue = NULL;

void createSensorThreadQueue() {
    sensor_thread_queue = xQueueCreate(QUEUE_LENGTH, sizeof(SensorThreadMessage));

    if (sensor_thread_queue == NULL) {
        //error handling
        while(1) {}
    }
}

void receiveFromSensorThreadQueue(SensorThreadMessage* receivedMsg) {
    //SensorThreadMessage* someMessage = (SensorThreadMessage* ) receivedMsg;

    if (xQueueReceive(sensor_thread_queue, receivedMsg, portMAX_DELAY)) {

    }
    else {
        //Error, proceed to stop
        while(1) {}
    }

}

BaseType_t sendToSensorThreadQueueFromISR(void *targetMessage) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (xQueueSendFromISR(sensor_thread_queue, targetMessage, &xHigherPriorityTaskWoken)) {

    }
    else{
        //error, proceed to stop
        while(1) {}
    }

    return xHigherPriorityTaskWoken;
}
