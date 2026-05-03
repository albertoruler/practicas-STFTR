//Ejercicio 2 Práctica 2 - Alberto Ortiz
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/adc.h"

#define STACK_SIZE 4096
#define QUEUE_SIZE 20
#define WINDOW 10

QueueHandle_t queue;

void tareaADC(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t delay = 200 / portTICK_PERIOD_MS;

    while(1)
    {
        int valor = adc1_get_raw(ADC1_CHANNEL_6);
        xQueueSend(queue, &valor, portMAX_DELAY);

        xTaskDelayUntil(&xLastWakeTime, delay);
    }
}

void tareaFiltro(void *pvParameters)
{
    int buffer[WINDOW] = {0};
    int index = 0;
    int count = 0;
    float suma = 0;
    int valor;

    while(1)
    {
        if(xQueueReceive(queue, &valor, portMAX_DELAY))
        {
            suma -= buffer[index];
            buffer[index] = valor;
            suma += valor;

            index = (index + 1) % WINDOW;
            if(count < WINDOW) count++;

            float media = suma / count;

            printf("Valor: %d | Media: %.2f\n", valor, media);
        }
    }
}

void app_main(void)
{
    printf("Grupo: Alberto y David\n");

    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_5, ADC_ATTEN_DB_11);

    queue = xQueueCreate(QUEUE_SIZE, sizeof(int));

    xTaskCreate(tareaADC, "ADC_Task", STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(tareaFiltro, "Filtro_Task", STACK_SIZE, NULL, 1, NULL);
}