//Ejercicio 1 Práctica 1 - Alberto Ortiz
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_BOOT GPIO_NUM_4
#define LED_BLINK GPIO_NUM_5
#define BUTTON GPIO_NUM_0

void app_main(void)
{
    // Configurar GPIO4 y GPIO5 como salida
    gpio_set_direction(LED_BOOT, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_BLINK, GPIO_MODE_OUTPUT);

    // Configurar GPIO0 como entrada con pull-up
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON, GPIO_PULLUP_ONLY);

    const TickType_t delay_500ms = 500 / portTICK_PERIOD_MS;

    while (1)
    {
        // Leer botón (activo en LOW)
        int button_state = gpio_get_level(BUTTON);

        if (button_state == 0)
            gpio_set_level(LED_BOOT, 1);
        else
            gpio_set_level(LED_BOOT, 0);

        // Parpadeo 1 Hz (500ms ON + 500ms OFF)
        gpio_set_level(LED_BLINK, 1);
        vTaskDelay(delay_500ms);
        gpio_set_level(LED_BLINK, 0);
        vTaskDelay(delay_500ms);
    }
}