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

typedef enum {
    TIMER70_MESSAGE,
    TIMER500_MESSAGE
} messageType;

typedef struct SensorThreadMessage {
    messageType message_type;
    int   value;
} SensorThreadMessage;

void createSensorThreadQueue();

SensorThreadMessage receiveFromSensorThreadQueue();

BaseType_t sendToSensorThreadQueueFromISR(SensorThreadMessage* targetMessage);

#endif /* SENSOR_THREAD_QUEUE_H_ */
