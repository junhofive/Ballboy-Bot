/*
 * uart_thread_queue.c
 *
 *
 */

#include <stdio.h>
#include "uart_thread_queue.h"
#include "FreeRTOS.h"

static QueueHandle_t queue = NULL;
void create_UART_Queue()
{

   queue = xQueueCreate(10, sizeof(UART_Thread_Queue));
    if (queue == NULL){
        //error handling
    }
}
void read_from_queue(void* retrievedMsg)
{
    //QueueHandle_t queue;

        if (xQueueReceive(queue, retrievedMsg, portMAX_DELAY))
        {

        }else{
            // error handling
        }

}



BaseType_t write_queue(void *outputMessage)
{
    BaseType_t HighPriorityEnable = pdFALSE;

    if (xQueueSendFromISR(queue, outputMessage, &HighPriorityEnable))
            {

            }else{
                //error handling
            }
    return HighPriorityEnable;
}
// create queue
// read from queue
// write queue
