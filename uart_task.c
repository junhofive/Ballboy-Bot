/*
 * uart_task.c
 */
# include <ti/drivers/UART.h>
# include "uart_task.h"
#include "uart_thread_queue.h"
#include "debug.h"

// The goal (from milestone description): Receive messages containing C-strings and output them to the UART.

 void *uart_task(void *arg){
     while(1){
         receiveFromUARTthreadQueue(&message);
         sendToUART(&message);
     }
 }

//__________________________________________________________________________________________
// this function will be executed by each thread
/*
 void *uart_task(void *arg){
     dbgEvent(ENTER_UART_TASK);

     UART_init();
     UART_Params parameters;
     UART_Params_init(&parameters);
     parameters.baudRate = 9600;
     parameters.readMode = UART_MODE_BLOCKING;
     parameters.writeMode = UART_MODE_BLOCKING;
     UART_Handle urt;

     dbgEvent(BEFORE_LOOP_TASK);

     while(1){

         urt = UART_open(0, &parameters);
         if (urt == NULL)
         {
             handleFatalError(UART_NOT_OPEN);
         }
         //UART_Thread_Queue retrieveMsg;
         //read_from_queue(&retrieveMsg);

         uint8_t buffer[100];
         UART_write(urt, buffer, 100);
         UART_close(urt);
     }

     dbgEvent(LEAVE_UART_TASK);
 }
*/
