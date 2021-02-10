/*
 * uart_thread_queue.h
 *
 *
 */

#ifndef UART_THREAD_QUEUE_H_
#define UART_THREAD_QUEUE_H_

#include <FreeRTOS.h>
#include <queue.h>

typedef struct UART_Thread_Queue{
    char message_queue[10];
    int val;
}UART_Thread_Queue;


void create_UART_Queue();
void read_from_queue(void* retrievedMsg);
BaseType_t write_queue(void *outputMessage);

#endif /* UART_THREAD_QUEUE_H_ */
