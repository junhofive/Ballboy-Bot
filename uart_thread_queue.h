/*
 * uart_thread_queue.h
 */

#ifndef UART_THREAD_QUEUE_H_
#define UART_THREAD_QUEUE_H_

#define BUFFER_SIZE 50

#include <FreeRTOS.h>
#include <queue.h>

typedef struct UartThreadMessage {
    char message[BUFFER_SIZE];
} UartThreadMessage;

void createUARTthreadQueue();

UartThreadMessage receiveFromUARTthreadQueue();

void sendToUartThreadQueue(UartThreadMessage* targetMessage);

#endif /* UART_THREAD_QUEUE_H_ */
