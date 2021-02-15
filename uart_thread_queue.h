/*
 * uart_thread_queue.h
 */

#ifndef UART_THREAD_QUEUE_H_
#define UART_THREAD_QUEUE_H_

#include <FreeRTOS.h>

char message[20]; // Received C string

void createUARTthreadQueue();

void receiveFromUARTthreadQueue(char* retrievedMsg);

BaseType_t sendToUART(char* outputMsg);

#endif /* UART_THREAD_QUEUE_H_ */
