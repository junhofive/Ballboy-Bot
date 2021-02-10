/*
 * uart_thread_queue.c
 *
 *
 */

#include <stdio.h>
#include "uart_thread_queue.h"
#include "FreeRTOS.h"
#include <FreeRTOS.h>
#include <queue.h>
#include "debug.h"

#define BUFFER_SIZE 50
#define QUEUE_LENGTH 20

static QueueHandle_t uart_thread_queue = NULL;
void createUARTthreadQueue()
{
   uart_thread_queue = xQueueCreate(QUEUE_LENGTH, BUFFER_SIZE);
   if (uart_thread_queue == NULL){
       handleFatalError(UART_QUEUE_NOT_CREATED);
   }
}
void receiveFromUARTthreadQueue(void* retrievedMsg)
{
    //QueueHandle_t queue;

    if (xQueueReceive(uart_thread_queue, retrievedMsg, portMAX_DELAY)) {

    }
    else {
        // error handling
        handleFatalError(UART_QUEUE_NOT_RECV);
    }

}



BaseType_t sendToUARTthreadQueueFromISR(void *outputMessage)
{
    BaseType_t HighPriorityEnable = pdFALSE;

    if (xQueueSendFromISR(uart_thread_queue, outputMessage, &HighPriorityEnable))
            {

            }else{
                //error handling
                handleFatalError(UART_QUEUE_NOT_SENT);
            }
    return HighPriorityEnable;
}
// create queue
// read from queue
// write queue
