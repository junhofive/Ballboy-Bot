/*
 * sensor_task.c
 *
 *  Created on: Feb 6, 2021
 *      Author: JO_Desktop
 */

#include "sensor_task.h"
#include "sensor_thread_queue.h"
#include "sensor_thread_state.h"

#include <stdint.h>
#include <stddef.h>

void *sensor_task(void *arg0) {
    while(1) {
        SensorThreadMessage sensorMessage;
        receiveFromSensorThreadQueue(&sensorMessage);

        enterStateMachine(&sensorMessage);
    }
}
