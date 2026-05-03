//Ejercicio 9 Práctica 3 - Alberto Ortiz

//#define configUSE_TIME_SLICING 0

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define STACK_SIZE (4*1024)
#define ITERATE_3 600000

static portMUX_TYPE spinlock = portMUX_INITIALIZER_UNLOCKED;

//TASK3 CRÍTICA
void task3(void *pv)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while(1)
    {
        taskENTER_CRITICAL(&spinlock);

        for(long i=0;i<ITERATE_3;i++)
            __asm__ __volatile__("NOP");

        taskEXIT_CRITICAL(&spinlock);

        vTaskDelayUntil(&xLastWakeTime,200/portTICK_PERIOD_MS);
    }
}

//ISR TASK
void tarea_ISR(void *pv)
{
    while(1)
    {
        printf("ISR ejecutando\n");
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    xTaskCreate(task3,"T3",STACK_SIZE,NULL,10,NULL);   // misma prioridad
    xTaskCreate(tarea_ISR,"ISR",STACK_SIZE,NULL,10,NULL);
}