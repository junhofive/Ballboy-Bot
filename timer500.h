/*
 * timer500.h
 * Editor: Tianyu Li
 */


#ifndef TIMER500_H_
#define TIMER500_H_

//*************************************************************************************************
#include <ti/drivers/dpl/HwiP.h>
#include "timer500.h"
#include "sensor_thread_queue.h"

void *timer500Thread(void *arg0);
//*************************************************************************************************
#endif /* TIMER500_H_ */
