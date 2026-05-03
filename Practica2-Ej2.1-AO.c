//Ejercicio 1 Práctica 2 - Alberto Ortiz
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED1 GPIO_NUM_4
#define LED2 GPIO_NUM_5
#define BUTTON GPIO_NUM_0

#define STACK_SIZE 4096

TaskHandle_t task2Handle = NULL;

void tarea1(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t delay = 333 / portTICK_PERIOD_MS; // 3Hz

    while(1)
    {
        gpio_set_level(LED1, 1);
        vTaskDelay(50/portTICK_PERIOD_MS);
        gpio_set_level(LED1, 0);

        xTaskDelayUntil(&xLastWakeTime, delay);
    }
}

void tarea2(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t delay = 166 / portTICK_PERIOD_MS; // 6Hz

    while(1)
    {
        gpio_set_level(LED2, 1);
        vTaskDelay(30/portTICK_PERIOD_MS);
        gpio_set_level(LED2, 0);

        xTaskDelayUntil(&xLastWakeTime, delay);
    }
}

void app_main(void)
{
    printf("Grupo: Alberto y David\n");

    gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);

    xTaskCreate(tarea1, "LED_3Hz", STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(tarea2, "LED_6Hz", STACK_SIZE, NULL, 1, &task2Handle);

    int lastState = 1;
    int currentState;

    while(1)
    {
        currentState = gpio_get_level(BUTTON);

        if(lastState == 1 && currentState == 0)
        {
            if(eTaskGetState(task2Handle) == eSuspended)
            {
                printf("Reanudando tarea 2 en 3 segundos...\n");
                vTaskDelay(3000/portTICK_PERIOD_MS);
                vTaskResume(task2Handle);
            }
            else
            {
                printf("Suspendiendo tarea 2\n");
                vTaskSuspend(task2Handle);
            }
        }

        printf("Estado tarea 2: %d\n", eTaskGetState(task2Handle));

        lastState = currentState;
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}