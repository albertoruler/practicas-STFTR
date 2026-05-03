//Ejercicio 10 (Voluntario) Práctica 3 - Alberto Ortiz

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "driver/gpio.h"

#define STACK_SIZE (4*1024)
#define PULSADOR 0

EventGroupHandle_t event_group;

#define BIT1 (1<<0)
#define BIT2 (1<<1)
#define BIT3 (1<<2)

//TASK1
void task1(void *pv)
{
    while(1)
    {
        EventBits_t bits = xEventGroupWaitBits(event_group,BIT1,pdTRUE,pdFALSE,0);

        if(!(bits & BIT1))
            printf("Task1 ejecutando\n");

        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}

//TASK2
void task2(void *pv)
{
    while(1)
    {
        EventBits_t bits = xEventGroupWaitBits(event_group,BIT2,pdTRUE,pdFALSE,0);

        if(!(bits & BIT2))
            printf("Task2 ejecutando\n");

        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}

//TASK3
void task3(void *pv)
{
    while(1)
    {
        EventBits_t bits = xEventGroupWaitBits(event_group,BIT3,pdTRUE,pdFALSE,0);

        if(!(bits & BIT3))
            printf("Task3 ejecutando\n");

        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    event_group = xEventGroupCreate();

    gpio_set_direction(PULSADOR, GPIO_MODE_INPUT);

    xTaskCreate(task1,"T1",STACK_SIZE,NULL,1,NULL);
    xTaskCreate(task2,"T2",STACK_SIZE,NULL,1,NULL);
    xTaskCreate(task3,"T3",STACK_SIZE,NULL,1,NULL);

    int prev=1;

    while(1)
    {
        int curr = gpio_get_level(PULSADOR);

        if(curr==0 && prev==1)
        {
            xEventGroupSetBits(event_group, BIT1|BIT2|BIT3);
        }

        prev=curr;
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}