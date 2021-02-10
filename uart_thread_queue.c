/*
 * uart_thread_queue.c
 *
 *
 */

#include <stdio.h>
#include "uart_thread_queue.h"
#include "FreeRTOS.h"

void create_UART_Queue()
{

    QueueHandle_t queue = xQueueCreate(10, sizeof(UART_Thread_Queue));
    if (queue == NULL){
        //error handling
    }
}
void read_from_queue(void* retrievedMsg)
{
    QueueHandle_t queue;

        if (xQueueReceive(queue, &messageQueue, portMAX_DELAY)
        {

        }else{
            // error handling
        }

}



Base_Type_t write_queue(void *outputMessage)
{
    BaseType_t compareParam = pdFALSE;
    c_struct *message;
    message = (c_struct *) pvParam;
    if (xQueueSend(uart_thread_queue, (void *) &message, (portTickType) 0) != pdPASS)
            {

            }

}
// create queue
// read from queue
// write queue
