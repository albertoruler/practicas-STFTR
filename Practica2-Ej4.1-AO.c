//Ejercicio 3 Práctica 2 - Alberto Ortiz
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/adc.h"

#define STACK_SIZE 4096

SemaphoreHandle_t xMutex;

void tareaMin(void *pvParameters)
{
    int globalMin = 4095;

    while(1)
    {
        vTaskDelay(200/portTICK_PERIOD_MS);

        if(xSemaphoreTake(xMutex, portMAX_DELAY))
        {
            printf("Take MIN: %lu\n",
            (unsigned long)xTaskGetTickCount()*portTICK_PERIOD_MS);

            int min = 4095;
            for(int i=0;i<1000;i++)
            {
                int val = adc1_get_raw(ADC1_CHANNEL_6);
                if(val < min) min = val;
            }

            if(min < globalMin) globalMin = min;

            printf("Minimo global: %d\n", globalMin);

            printf("Give MIN: %lu\n",
            (unsigned long)xTaskGetTickCount()*portTICK_PERIOD_MS);

            xSemaphoreGive(xMutex);
        }
    }
}

void tareaMax(void *pvParameters)
{
    int globalMax = 0;

    while(1)
    {
        vTaskDelay(200/portTICK_PERIOD_MS);

        if(xSemaphoreTake(xMutex, portMAX_DELAY))
        {
            printf("Take MAX: %lu\n",
            (unsigned long)xTaskGetTickCount()*portTICK_PERIOD_MS);

            int max = 0;
            for(int i=0;i<1000;i++)
            {
                int val = adc1_get_raw(ADC1_CHANNEL_6);
                if(val > max) max = val;
            }

            if(max > globalMax) globalMax = max;

            printf("Maximo global: %d\n", globalMax);

            printf("Give MAX: %lu\n",
            (unsigned long)xTaskGetTickCount()*portTICK_PERIOD_MS);

            xSemaphoreGive(xMutex);
        }
    }
}

void tareaMedia(void *pvParameters)
{
    while(1)
    {
        vTaskDelay(200/portTICK_PERIOD_MS);

        if(xSemaphoreTake(xMutex, portMAX_DELAY))
        {
            printf("Take MEDIA: %lu\n",
            (unsigned long)xTaskGetTickCount()*portTICK_PERIOD_MS);

            long suma = 0;
            for(int i=0;i<1000;i++)
            {
                suma += adc1_get_raw(ADC1_CHANNEL_6);
            }

            printf("Media: %ld\n", suma/1000);

            printf("Give MEDIA: %lu\n",
            (unsigned long)xTaskGetTickCount()*portTICK_PERIOD_MS);

            xSemaphoreGive(xMutex);
        }
    }
}

void app_main(void)
{
    printf("Grupo: Alberto y David\n");

    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_5, ADC_ATTEN_DB_11);

    xMutex = xSemaphoreCreateMutex();

    xTaskCreate(tareaMin, "Min_Task", STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(tareaMax, "Max_Task", STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(tareaMedia, "Media_Task", STACK_SIZE, NULL, 1, NULL);
}