// Ejercicio 5.1 Práctica 1 - Alberto Ortiz
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_err.h"

#define ADC_CHANNEL ADC_CHANNEL_6

void app_main(void)
{
    // Configuración de la unidad ADC
    adc_oneshot_unit_handle_t adc1_handle;
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
    };

    esp_err_t ret = adc_oneshot_new_unit(&init_config, &adc1_handle);
    if (ret != ESP_OK) {
        printf("Error al inicializar ADC: %d\n", ret);
        return;
    }

    // Configuración del canal
    adc_oneshot_chan_cfg_t config = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };

    ret = adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL, &config);
    if (ret != ESP_OK) {
        printf("Error al configurar canal ADC: %d\n", ret);
        return;
    }

    int adc_raw;
    float voltaje;

    while (1)
    {
        ret = adc_oneshot_read(adc1_handle, ADC_CHANNEL, &adc_raw);
        if (ret == ESP_OK) {
            // Convertir a voltaje (0V - 3.3V)
            voltaje = (adc_raw / 4095.0) * 3.3;
            printf("Valor ADC: %d, Voltaje: %.2f V\n", adc_raw, voltaje);
        } else {
            printf("Error leyendo ADC: %d\n", ret);
        }

        vTaskDelay(pdMS_TO_TICKS(200)); // Espera 200 ms
    }
}