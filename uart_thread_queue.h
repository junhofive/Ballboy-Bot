/*
 * uart_thread_queue.h
 *
 *
 */

#ifndef UART_THREAD_QUEUE_H_
#define UART_THREAD_QUEUE_H_

#include <FreeRTOS.h>

//typedef struct UART_Thread_Queue{
//    char message_queue[10];
//    int val;
//}UART_Thread_Queue;

void createUARTthreadQueue();
void receiveFromUARTthreadQueue(void* retrievedMsg);
BaseType_t sendToUARTthreadQueueFromISR(void *outputMessage);

#endif /* UART_THREAD_QUEUE_H_ */
