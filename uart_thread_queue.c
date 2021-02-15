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

#define BUFFER_SIZE 50
#define QUEUE_LENGTH 50

static QueueHandle_t uart_thread_queue = NULL;

void createUARTthreadQueue()
{
   uart_thread_queue = xQueueCreate(QUEUE_LENGTH, BUFFER_SIZE);
   if (uart_thread_queue == NULL){
       handleFatalError(UART_QUEUE_NOT_CREATED);
   }
}
void receiveFromUARTthreadQueue(char* retrievedMsg)
{
    dbgEvent(BEFORE_RECV_UART_QUEUE);

    if (xQueueReceive(uart_thread_queue, retrievedMsg, portMAX_DELAY)) {

    }
    else {
        // error handling
        handleFatalError(UART_QUEUE_NOT_RECV);
    }
    dbgEvent(AFTER_RECV_UART_QUEUE);
}

BaseType_t sendToUART(char* outputMsg)
{
    dbgEvent(BEFORE_SEND_UART_ISR);
    BaseType_t HighPriorityEnable = pdFALSE;

    if (xQueueSendFromISR(uart_thread_queue, outputMsg, &HighPriorityEnable)){

    }else{
        //error handling
        handleFatalError(UART_QUEUE_NOT_SENT);
    }
    dbgEvent(AFTER_SEND_UART_ISR);
    return HighPriorityEnable;
}
