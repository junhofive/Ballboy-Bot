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
     UART_params parameters;
     UART_params_init(&parameters);
     parameters.baud_rate = 9600;
     parameters.read_mode = UART_MODE_BLOCKING;
     parameters.write_mode = UART_MODE_BLOCKING;
     UART_handle urt;
         while(1){

             urt = UART_open(CONFIG_UART0, &parameters);
             UART_Thread_Queue retriveMsg;
             read_from_queue(&retrieveMsg);


              uint8_t buffer[100];
              UART_write(urt, buffer, 100);


              UART_close(urt);



         }



 }

