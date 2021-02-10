/*
 * sensor_thread_queue.c
 *
 *  Created on: Feb 6, 2021
 *      Author: JO_Desktop
 */

#include "FreeRTOS.h"
#include "sensor_thread_queue.h"
#include "timer70.h"

#include "queue.h"

#define QUEUE_LENGTH 10
/* Static Variable */
static QueueHandle_t sensor_thread_queue = NULL;

void createSensorThreadQueue() {
    sensor_thread_queue = xQueueCreate(QUEUE_LENGTH, sizeof(SensorThreadMessage));

    if (sensor_thread_queue == NULL) {
        //error handling
    }
}

void receiveFromSensorThreadQueue(void* receivedMsg) {
    SensorThreadMessage* someMessage = (SensorThreadMessage* ) receivedMsg;

    if (xQueueReceive(sensor_thread_queue, someMessage, portMAX_DELAY)) {

    }
    else {
        //Error, proceed to stop
    }

}

BaseType_t sendToSensorThreadQueueFromISR(void *targetMessage) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    c_struct *message;
    message = (c_struct *)pvParameters;
    if (xQueueSend(sensor_thread_queue, (void *) &message, (portTickType) 0) != pdPASS) {

    }
}
