/*
 * debug.h
 *
 *  Created on: Feb 10, 2021
 *      Author: JO_Desktop
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#define BIT_6   0x40
#define BIT_5   0x20
#define BIT_4   0x10
#define BIT_3   0x08
#define BIT_2   0x04
#define BIT_1   0x02
#define BIT_0   0x01

/* pthread related errors */
#define PTHREAD_SET_ATTR_FAILED_MAIN_C      0x70
#define PTHREAD_CREATE_FAILED_MAIN_C        0x71
#define PTHREAD_NOT_CREATED                 0x72

/* Main Thread */
#define ENTER_MAIN_THREAD                   0x01

/* Timer 70 */
#define ENTER_TIMER70                       0x10
#define LEAVE_TIMER70                       0x19

/* Timer 500 */
#define ENTER_TIMER500                      0x1a
#define LEAVE_TIMER500                      0x1f

/* Sensor Task */
#define ENTER_SENSOR_TASK                   0x20
#define BEFORE_SENSOR_LOOP                  0x21

/* Sensor FSM */
#define ENTER_STATE_MACHINE                 0x2a
#define INIT_AVERAGE_STATE                  0x2b
#define UPDATE_AVERAGE_STATE                0x2c

#define LEAVE_INIT_AVERAGE_STATE            0x2d
#define LEAVE_UPDATE_AVERAGE_STATE          0x2e
#define LEAVE_STATE_MACHINE                 0x2f

/* Sensor Queue */
#define BEFORE_RECEIVE_SENSOR_QUE           0x31
#define AFTER_RECEIVE_SENSOR_QUE            0x39

#define BEFORE_SEND_TIMER70_MSG             0x3a
#define AFTER_SEND_TIMER70_MSG              0x3b

#define BEFORE_SEND_TIMER500_MSG            0x3e
#define AFTER_SEND_TIMER500_MSG             0x3f


/* Sensor Queue Errors */
#define SENSOR_QUEUE_NOT_CREATED            0x60
#define SENSOR_QUEUE_NOT_RECEIVED           0x61
#define SENSOR_QUEUE_NOT_SENT               0x62

/* Timer70 Errors*/
#define TIMER70_NOT_CREATED                 0x50
#define ADC_NOT_OPEN                        0x51


void dbgEvent(unsigned int event);
void handleFatalError(unsigned int eventLabel);
#endif /* DEBUG_H_ */
