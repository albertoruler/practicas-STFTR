//Ejercicio 3 Práctica 1 - Alberto Ortiz
#include <stdio.h>
#include "driver/gpio.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUTTON GPIO_NUM_0

void app_main(void)
{
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON, GPIO_PULLUP_ONLY);

    int64_t t1 = 0;
    int64_t t2 = 0;
    bool first_press = true;

    while (1)
    {
        if (gpio_get_level(BUTTON) == 0)
        {
            if (first_press)
            {
                t1 = esp_timer_get_time();
                first_press = false;
                printf("Primera pulsación detectada\n");
            }
            else
            {
                t2 = esp_timer_get_time();
                printf("Tiempo entre pulsaciones: %lld us\n", (t2 - t1));
                first_press = true;
            }

            vTaskDelay(300 / portTICK_PERIOD_MS); // anti-rebote
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}