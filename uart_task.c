/*
 * uart_task.c
 */
# include <ti/drivers/UART.h>
# include "uart_task.h"
#include "uart_thread_queue.h"
#include "debug.h"
#include "ti_drivers_config.h"
#include <string.h>

void writeToUART(UartThreadMessage* outputMsg)
{
    UART_Handle uart;
    UART_Params parameters;

    UART_Params_init(&parameters);
    parameters.baudRate = 115200;
    parameters.writeMode = UART_MODE_BLOCKING;
    parameters.writeTimeout = UART_WAIT_FOREVER;
    uart = UART_open(CONFIG_UART_1, &parameters);

    if (uart == NULL) {
        handleFatalError(UART_OPEN_ERROR);
    }
    UART_write(uart, (const void *)outputMsg->message, strlen(outputMsg->message));
#if 0
    if (UART_write(uart, outputMsg->message, strlen(outputMsg->message)) == UART_STATUS_ERROR) {
        handleFatalError(UART_WRITE_ERROR);
    }
#endif

    UART_close(uart);

}

 void *uart_task(void *arg){
     dbgEvent(ENTER_UART_TASK);
     UartThreadMessage message;
     dbgEvent(BEFORE_UART_LOOP);
     while(1){
         dbgEvent(BEFORE_RECEIVE_UART_QUEUE);
         message = receiveFromUARTthreadQueue();
         dbgEvent(AFTER_RECEIVE_UART_QUEUE);

         dbgEvent(ENTER_WRITE_TO_UART);
         writeToUART(&message);
         dbgEvent(LEAVE_WRITE_TO_UART);
     }
 }

