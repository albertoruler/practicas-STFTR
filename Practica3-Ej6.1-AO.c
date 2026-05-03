//Ejercicio 8 Práctica 3 - Alberto Ortiz

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_timer.h"

//CONFIG
#define PULSADOR 0
#define STACK_SIZE (4*1024)
#define ITERATE_ISR 200000

QueueHandle_t gpio_evt_queue;

//ISR
static void IRAM_ATTR isr_handler(void *arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

//TAREA ISR
void tarea_ISR(void *arg)
{
    uint32_t io_num;
    while(1)
    {
        if(xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY))
        {
            printf("\n*************** ISR ***************\n");

            for(long i=0;i<ITERATE_ISR;i++)
                __asm__ __volatile__("NOP");
        }
    }
}

//TAREA NORMAL
void tarea(void *pv)
{
    while(1)
    {
        printf("RUN %llu\n", esp_timer_get_time()/1000);
        for(long i=0;i<200000;i++)
            __asm__ __volatile__("NOP");
        vTaskDelay(200/portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL<<PULSADOR,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = true,
        .intr_type = GPIO_INTR_NEGEDGE
    };
    gpio_config(&io_conf);

    gpio_evt_queue = xQueueCreate(10,sizeof(uint32_t));

    gpio_install_isr_service(0);
    gpio_isr_handler_add(PULSADOR, isr_handler, (void*)PULSADOR);

    xTaskCreate(tarea_ISR,"ISR",STACK_SIZE,NULL,10,NULL);
    xTaskCreate(tarea,"T1",STACK_SIZE,NULL,1,NULL);
}