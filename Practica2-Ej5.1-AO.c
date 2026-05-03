//Ejercicio 4 Práctica 2 - Alberto Ortiz
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "driver/adc.h"

#define LED1 GPIO_NUM_4
#define LED2 GPIO_NUM_5
#define BUTTON GPIO_NUM_0
#define STACK_SIZE 4096

SemaphoreHandle_t xSemaphore;

void tarea1(void *pvParameters)
{
    while(1)
    {
        gpio_set_level(LED1, 1);
        vTaskDelay(50/portTICK_PERIOD_MS);
        gpio_set_level(LED1, 0);
        vTaskDelay(50/portTICK_PERIOD_MS);
    }
}

void tarea2(void *pvParameters)
{
    int lastState = 1;
    int currentState;

    while(1)
    {
        currentState = gpio_get_level(BUTTON);

        if(lastState == 1 && currentState == 0)
        {
            printf("¡Botón pulsado!\n");
            gpio_set_level(LED2, !gpio_get_level(LED2));
            xSemaphoreGive(xSemaphore);
        }

        lastState = currentState;
        vTaskDelay(50/portTICK_PERIOD_MS);
    }
}

void tarea3(void *pvParameters)
{
    while(1)
    {
        if(xSemaphoreTake(xSemaphore, portMAX_DELAY))
        {
            long suma = 0;
            for(int i=0;i<10;i++)
            {
                suma += adc1_get_raw(ADC1_CHANNEL_6);
            }
            printf("Promedio ADC: %ld\n", suma/10);
        }
    }
}

void app_main(void)
{
    printf("Grupo: Alberto y David\n");

    gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);

    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);

    xSemaphore = xSemaphoreCreateBinary();

    xTaskCreate(tarea1, "LED_10Hz", STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(tarea2, "Button_Task", STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(tarea3, "ADC_Task", STACK_SIZE, NULL, 1, NULL);
}