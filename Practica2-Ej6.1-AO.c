//Ejercicio 5 Práctica 2 - Alberto Ortiz
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED1 GPIO_NUM_4
#define LED2 GPIO_NUM_5
#define STACK_SIZE 4096

void tareaLED3Hz(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t delay = 333 / portTICK_PERIOD_MS; // 3Hz

    while(1)
    {
        gpio_set_level(LED1, 1);
        vTaskDelay(50 / portTICK_PERIOD_MS);
        gpio_set_level(LED1, 0);

        xTaskDelayUntil(&xLastWakeTime, delay);
    }
}

void tareaLED6Hz(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t delay = 166 / portTICK_PERIOD_MS; // 6Hz

    while(1)
    {
        gpio_set_level(LED2, 1);
        vTaskDelay(30 / portTICK_PERIOD_MS);
        gpio_set_level(LED2, 0);

        xTaskDelayUntil(&xLastWakeTime, delay);
    }
}

void app_main(void)
{
    printf("\n");
    printf("=====================================\n");
    printf("Practica 2 - Ejercicio 6.1\n");
    printf("Grupo: Alberto y David\n");
    printf("=====================================\n\n");

    gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED2, GPIO_MODE_OUTPUT);

    xTaskCreate(tareaLED3Hz, "LED_3Hz", STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(tareaLED6Hz, "LED_6Hz", STACK_SIZE, NULL, 1, NULL);

    char buffer[512];

    while(1)
    {
        vTaskDelay(5000 / portTICK_PERIOD_MS);  // cada 5 segundos

        printf("\n------ Estadisticas CPU ------\n");
        vTaskGetRunTimeStats(buffer);
        printf("%s\n", buffer);
    }
}