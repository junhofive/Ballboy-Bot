/*
 * uart_task.c
 */
# include <ti/drivers/UART.h>
# include "uart_task.h"
#include "uart_thread_queue.h"
#include "debug.h"

// The goal (from milestone description): Receive messages containing C-strings and output them to the UART.

BaseType_t sendToUART(char* outputMsg)
{
    dbgEvent(BEFORE_SEND_UART);
    BaseType_t HighPriorityEnable = pdFALSE;

    uint8_t buffer[100];
    UART_Handle uart;
    UART_Params parameters;

    UART_init();
    UART_Params_init(&parameters);
    // Specify the parameters if needed
    params.baudRate = 9600;
    params.readMode = UART_MODE_BLOCKING;
    params.writeMode = UART_MODE_BLOCKING;
    uart = UART_open(CONFIG_UART_0, &parameters);

    if (uart == NULL) {
        handleFatalError(UART_NOT_OPEN);

    }

    // get the message string, and send to UART
    UART_write(uart, outputMsg, 20); // 20 since set the string size to 20 in header file
    /*if(UART_write(uart, outputMsg, 20) == UART_STATUS_ERROR){
        handleFatalError(UART)
    }*/
    dbgEvent(AFTER_SEND_UART);
    return HighPriorityEnable;
}
 void *uart_task(void *arg){
     dbgEvent(ENTER_UART_TASK);
     while(1){
         receiveFromUARTthreadQueue(&message);
         sendToUART(&message);
     }
 }

