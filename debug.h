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


/*
#define PTHREAD_DETACHSTATE_ERROR   0x0
#define PTHREAD_STACKSIZE_ERROR     0x1
#define ENTERING_TASK               0x2
#define BEFORE_LOOP_TASK            0x3
#define BEFORE_SEND_SENSOR_QUEUE    0x4
#define BEFORE_RECV_SENSOR_QUEUE    0x5
#define AFTER_SEND_SENSOR_QUEUE     0x6
#define AFTER_RECV_SENSOR_QUEUE     0x7
#define BEFORE_SEND_UART_QUEUE      0x8
#define BEFORE_RECV_UART_QUEUE      0x9
#define AFTER_SEND_UART_QUEUE       0xa
#define AFTER_RECV_UART_QUEUE       0xb
#define ENTERING_TIMER              0xc
#define LEAVING_TIMER               0xd
#define BEFORE_SEND_SENSOR_ISR      0xe
#define BEFORE_SEND_UART_ISR        0xf
#define AFTER_SEND_SENSOR_ISR       0x10
#define AFTER_SEND_UART_ISR         0x11
#define SENSOR_QUEUE_NOT_CREATED    0X12
#define SENSOR_QUEUE_NOT_SENT       0x13
#define SENSOR_QUEUE_NOT_RECV       0x14
#define UART_QUEUE_NOT_CREATED      0x15
#define UART_QUEUE_NOT_SENT         0x16
#define UART_QUEUE_NOT_RECV         0x17
#define ADC_CONVERSION_ERROR        0x18
#define ENTERING_INIT_AVERAGE       0x19
#define LEAVING_INIT_AVERAGE        0x1a
#define ENTERING_UPDATE_AVERAGE     0x1b
#define LEAVING_UPDATE_AVERAGE      0x1c
#define PTHREAD_NOT_CREATED         0x1d
#define ADC_NOT_OPEN                0x1e
#define TIMER_NOT_INITIALIZED       0x1f
#define TIMER_NOT_OPEN              0x20
#define ENTERING_TIMER_FIVE         0x21
#define LEAVING_TIMER_FIVE          0x22

#define UART_NOT_OPEN               0x30
#define FREERTOS_STACK_OVERFLOW     0x40
*/


void dbgEvent(unsigned int event);
void handleFatalError(unsigned int eventLabel);
#endif /* DEBUG_H_ */
