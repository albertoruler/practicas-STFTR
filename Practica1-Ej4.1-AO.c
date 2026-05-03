// Ejercicio 2 Práctica 1 - Alberto Ortiz
#include <stdio.h>
#include "driver/gpio.h"
#include "driver/gptimer.h"
#include "esp_err.h"

#define LED GPIO_NUM_4

gptimer_handle_t gp_timer = NULL;

// Callback de interrupción del temporizador
bool IRAM_ATTR timer_callback(gptimer_handle_t timer,
                              const gptimer_alarm_event_data_t *event,
                              void *user_data)
{
    static bool level = false;

    gpio_set_level(LED, level);
    level = !level;

    return true;  // Mantener auto-reload activo
}

void app_main(void)
{
    // Configurar GPIO4 como salida
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    gpio_set_level(LED, 0);  // Inicialmente apagado

    // Configuración del GPTimer
    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1000000,  // 1 MHz → 1 tick = 1 µs
    };

    ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &gp_timer));

    // Configuración de la alarma (cada 250 ms)
    gptimer_alarm_config_t alarm_config = {
        .reload_count = 0,
        .alarm_count = 250000,  // 250000 µs = 250 ms
        .flags = {
            .auto_reload_on_alarm = true
        }
    };

    ESP_ERROR_CHECK(gptimer_set_alarm_action(gp_timer, &alarm_config));

    // Registrar callback
    gptimer_event_callbacks_t cbs = {
        .on_alarm = timer_callback,
    };
    ESP_ERROR_CHECK(gptimer_register_event_callbacks(gp_timer, &cbs, NULL));

    // Habilitar interrupciones del timer
    ESP_ERROR_CHECK(gptimer_enable_intr(gp_timer));

    // Habilitar e iniciar timer
    ESP_ERROR_CHECK(gptimer_enable(gp_timer));
    ESP_ERROR_CHECK(gptimer_start(gp_timer));
}