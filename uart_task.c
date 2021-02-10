/*
 * uart_task.c
 *
 */
# include <ti/drivers/UART.h>
# include "uart_task.h"
#include "uart_thread_queue.h"
//int main(){

// this function will be executed by each thread
 void *uart_task(void *arg){
     UART_init();
     UART_Params parameters;
     UART_Params_init(&parameters);
     parameters.baudRate = 9600;
     parameters.readMode = UART_MODE_BLOCKING;
     parameters.writeMode = UART_MODE_BLOCKING;
     UART_Handle urt;
     //dbgEvent(DLOC_UART_ISR_BEGIN);
         while(1){

             urt = UART_open(0, &parameters);
             UART_Thread_Queue retrieveMsg;
             read_from_queue(&retrieveMsg);


              uint8_t buffer[100];
              UART_write(urt, buffer, 100);


              UART_close(urt);



         }



 }

