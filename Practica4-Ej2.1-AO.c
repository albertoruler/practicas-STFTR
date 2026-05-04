// Ejercicio 1 Práctica 4 - Alberto Ortiz

#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"

#define STACK_SIZE 4096

#define ITERATE_1 5500000
#define ITERATE_2 4000000
#define ITERATE_3 3000000
#define ITERATE_4 3000000
#define ITERATE_5 3000000

#define TASK1_T 90
#define TASK2_T 200
#define TASK3_T 400
#define TASK4_T 400
#define TASK5_T 400

void tarea(void *pvParameters)
{
    int id = (int)(intptr_t) pvParameters;

    int iter = 0;
    int periodo = 100;

    switch(id){
        case 1: iter = ITERATE_1; periodo = TASK1_T; break;
        case 2: iter = ITERATE_2; periodo = TASK2_T; break;
        case 3: iter = ITERATE_3; periodo = TASK3_T; break;
        case 4: iter = ITERATE_4; periodo = TASK4_T; break;
        case 5: iter = ITERATE_5; periodo = TASK5_T; break;
    }

    TickType_t xLastWakeTime = xTaskGetTickCount();

    while(1)
    {
        printf("T%d IN  %llu ms\n", id, esp_timer_get_time()/1000);

        for(long i = 0; i < iter; i++){
            __asm__ __volatile__("NOP");
        }

        printf("T%d OUT %llu ms\n", id, esp_timer_get_time()/1000);

        xTaskDelayUntil(&xLastWakeTime, periodo / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    xTaskCreate(tarea, "T1", STACK_SIZE, (void*)1, 5, NULL);
    xTaskCreate(tarea, "T2", STACK_SIZE, (void*)2, 1, NULL);
    xTaskCreate(tarea, "T3", STACK_SIZE, (void*)3, 1, NULL);
    xTaskCreate(tarea, "T4", STACK_SIZE, (void*)4, 1, NULL);
    xTaskCreate(tarea, "T5", STACK_SIZE, (void*)5, 1, NULL);
}