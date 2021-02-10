/*
 * sensor_thread_queue.h
 *
 *  Created on: Feb 6, 2021
 *      Author: JO_Desktop
 */

#ifndef SENSOR_THREAD_QUEUE_H_
#define SENSOR_THREAD_QUEUE_H_

#include <FreeRTOS.h>
#include <queue.h>

#define MESSAGE_LENGTH 20

typedef struct SensorThreadMessage {
    char  message_type[MESSAGE_LENGTH];
    int   value;
} SensorThreadMessage;

void createSensorThreadQueue();

void receiveFromSensorThreadQueue(SensorThreadMessage* receivedMsg);

BaseType_t sendToSensorThreadQueueFromISR(void *targetMessage);

#endif /* SENSOR_THREAD_QUEUE_H_ */
