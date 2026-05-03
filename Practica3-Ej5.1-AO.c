//Ejercicio 7 Práctica 3 - Alberto Ortiz

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_clk_tree.h"

//PERIODOS
#define TASK1_T 200
#define TASK2_T 200
#define TASK3_T 200
#define TASK4_T 200
#define TASK5_T 200

//CARGA
#define ITERATE_1 500000
#define ITERATE_2 500000
#define ITERATE_3 500000
#define ITERATE_4 500000
#define ITERATE_5 500000

#define PULSADOR 0
#define STACK_SIZE (4*1024)

void tarea(void *pv, int id, int iter, int delay)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(1)
    {
        printf("T%d I %llu\n", id, esp_timer_get_time()/1000);

        for(long i=0;i<iter;i++) __asm__ __volatile__("NOP");

        printf("T%d O %llu\n", id, esp_timer_get_time()/1000);

        xTaskDelayUntil(&xLastWakeTime, delay/portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    xTaskCreate((TaskFunction_t)tarea,"T1",STACK_SIZE,(void*)1,1,NULL);
    xTaskCreate((TaskFunction_t)tarea,"T2",STACK_SIZE,(void*)2,1,NULL);
    xTaskCreate((TaskFunction_t)tarea,"T3",STACK_SIZE,(void*)3,1,NULL);
    xTaskCreate((TaskFunction_t)tarea,"T4",STACK_SIZE,(void*)4,1,NULL);
    xTaskCreate((TaskFunction_t)tarea,"T5",STACK_SIZE,(void*)5,2,NULL); // prioridad mayor
}