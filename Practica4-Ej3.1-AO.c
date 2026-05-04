//Ejercicio 2 Práctica 4 - Alberto Ortiz

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_timer.h"

#define STACK_SIZE 4096
#define ITER_A 2000000
#define ITER_B 2000000

SemaphoreHandle_t xMutex1;
SemaphoreHandle_t xMutex2;

void TareaA(void *pvParameters)
{
    while(1)
    {
        if(xSemaphoreTake(xMutex1, 1000/portTICK_PERIOD_MS))
        {
            printf("A coge M1 %llu ms\n", esp_timer_get_time()/1000);

            vTaskDelay(1/portTICK_PERIOD_MS);

            if(xSemaphoreTake(xMutex2, 1000/portTICK_PERIOD_MS))
            {
                printf("A coge M2 %llu ms\n", esp_timer_get_time()/1000);

                for(long i=0;i<ITER_A;i++)
                    __asm__("NOP");

                xSemaphoreGive(xMutex2);
            }
            else printf("A falla M2 %llu ms\n", esp_timer_get_time()/1000);

            xSemaphoreGive(xMutex1);
        }

        vTaskDelay(200/portTICK_PERIOD_MS);
    }
}

void TareaB(void *pvParameters)
{
    while(1)
    {
        if(xSemaphoreTake(xMutex2, 1000/portTICK_PERIOD_MS))
        {
            printf("B coge M2 %llu ms\n", esp_timer_get_time()/1000);

            vTaskDelay(1/portTICK_PERIOD_MS);

            if(xSemaphoreTake(xMutex1, 1000/portTICK_PERIOD_MS))
            {
                printf("B coge M1 %llu ms\n", esp_timer_get_time()/1000);

                for(long i=0;i<ITER_B;i++)
                    __asm__("NOP");

                xSemaphoreGive(xMutex1);
            }
            else printf("B falla M1 %llu ms\n", esp_timer_get_time()/1000);

            xSemaphoreGive(xMutex2);
        }

        vTaskDelay(200/portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    xMutex1 = xSemaphoreCreateMutex();
    xMutex2 = xSemaphoreCreateMutex();

    xTaskCreate(TareaA,"A",STACK_SIZE,NULL,1,NULL);
    xTaskCreate(TareaB,"B",STACK_SIZE,NULL,1,NULL);
}