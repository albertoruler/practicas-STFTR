//Ejercicio 3 Práctica 4 - Alberto Ortiz

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#define STACK_SIZE 4096

SemaphoreHandle_t sem;

void tareaL(void *pvParameters)
{
    while (1)
    {
        printf("L: S %llu\n", esp_timer_get_time()/1000);

        xSemaphoreTake(sem, portMAX_DELAY);

        printf("L: I %llu\n", esp_timer_get_time()/1000);

        for (long i = 0; i < 8000000; i++)
            __asm__ __volatile__("NOP");

        printf("L: O %llu\n", esp_timer_get_time()/1000);

        xSemaphoreGive(sem);

        printf("L: X %llu\n", esp_timer_get_time()/1000);

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void tareaM(void *pvParameters)
{
    while (1)
    {
        printf("    M: S %llu\n", esp_timer_get_time()/1000);

        for (long i = 0; i < 10000000; i++)
            __asm__ __volatile__("NOP");

        printf("    M: X %llu\n", esp_timer_get_time()/1000);

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void tareaH(void *pvParameters)
{
    while (1)
    {
        vTaskDelay(50 / portTICK_PERIOD_MS);

        printf("        H: S %llu\n", esp_timer_get_time()/1000);

        xSemaphoreTake(sem, portMAX_DELAY);

        printf("        H: I %llu\n", esp_timer_get_time()/1000);

        xSemaphoreGive(sem);

        printf("        H: O %llu\n", esp_timer_get_time()/1000);
    }
}

void app_main(void)
{
    sem = xSemaphoreCreateBinary();
    xSemaphoreGive(sem);

    xTaskCreate(tareaL, "L", STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(tareaM, "M", STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(tareaH, "H", STACK_SIZE, NULL, 3, NULL);
}