/*
 * uart_thread_queue.c
 * code stack for the uart_thread_queue
 */

#include <stdio.h>
#include "uart_thread_queue.h"
#include "FreeRTOS.h"
#include <FreeRTOS.h>
#include <queue.h>
#include "debug.h"
#include "ti_drivers_config.h"

#define QUEUE_LENGTH 50

static QueueHandle_t uart_thread_queue = NULL;

void createUARTthreadQueue()
{
   uart_thread_queue = xQueueCreate(QUEUE_LENGTH, sizeof(UartThreadMessage));
   if (uart_thread_queue == NULL){
       handleFatalError(UART_QUEUE_NOT_CREATED);
   }
}
UartThreadMessage receiveFromUARTthreadQueue()
{
    static UartThreadMessage receivedMsg;
    if (xQueueReceive(uart_thread_queue, &receivedMsg, portMAX_DELAY) != pdTRUE) {
        handleFatalError(UART_QUEUE_NOT_RECEIVED);
    }
    return receivedMsg;
}

void sendToUartThreadQueue(UartThreadMessage* targetMessage)
{
    if (xQueueSend(uart_thread_queue, targetMessage, portMAX_DELAY) != pdTRUE) {
        handleFatalError(UART_QUEUE_NOT_SENT);
    }
}
