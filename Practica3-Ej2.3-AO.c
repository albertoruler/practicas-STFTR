//Ejercicio 3 Práctica 3 - Alberto Ortiz

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_clk_tree.h"

//Periodos (ms)
#define TASK1_T  200
#define TASK2_T  50
#define TASK3_T  200
#define TASK4_T  200
#define TASK5_T  200

//Carga computacional
#define ITERATE_1  100000
#define ITERATE_2  100000
#define ITERATE_3  100000
#define ITERATE_4  100000
#define ITERATE_5  100000

//GPIO
#define PULSADOR          0
#define GPIO_OUTPUT_IO_0  4
#define GPIO_OUTPUT_IO_1  5

#define STACK_SIZE  (4 * 1024)

bool flag_stats = false;
void imprime_estadisticas(void);

// TASK 1
void vTaskCode1(void *pvParameters)
{
    TickType_t       xLastWakeTime;
    const TickType_t xDelayTicks = TASK1_T / portTICK_PERIOD_MS;

    xLastWakeTime = xTaskGetTickCount();
    while (1) {
        if (!flag_stats)
            printf("\tI\t\t\t\t\t%llu\n", esp_timer_get_time() / 1000);

        for (long i = 0; i < ITERATE_1; i++)
            __asm__ __volatile__("NOP");

        if (!flag_stats)
            printf("\tO\t\t\t\t\t%llu\n", esp_timer_get_time() / 1000);

        xTaskDelayUntil(&xLastWakeTime, xDelayTicks);
    }
}

// TASK 2
void vTaskCode2(void *pvParameters)
{
    TickType_t       xLastWakeTime;
    const TickType_t xDelayTicks = TASK2_T / portTICK_PERIOD_MS;

    xLastWakeTime = xTaskGetTickCount();
    while (1) {
        if (!flag_stats)
            printf("\t\tI\t\t\t\t%llu\n", esp_timer_get_time() / 1000);

        for (long i = 0; i < ITERATE_2; i++)
            __asm__ __volatile__("NOP");

        if (!flag_stats)
            printf("\t\tO\t\t\t\t%llu\n", esp_timer_get_time() / 1000);

        xTaskDelayUntil(&xLastWakeTime, xDelayTicks);
    }
}

// TASK 3
void vTaskCode3(void *pvParameters)
{
    TickType_t       xLastWakeTime;
    const TickType_t xDelayTicks = TASK3_T / portTICK_PERIOD_MS;

    xLastWakeTime = xTaskGetTickCount();
    while (1) {
        if (!flag_stats)
            printf("\t\t\tI\t\t\t%llu\n", esp_timer_get_time() / 1000);

        for (long i = 0; i < ITERATE_3; i++)
            __asm__ __volatile__("NOP");

        if (!flag_stats)
            printf("\t\t\tO\t\t\t%llu\n", esp_timer_get_time() / 1000);

        xTaskDelayUntil(&xLastWakeTime, xDelayTicks);
    }
}

// TASK 4
void vTaskCode4(void *pvParameters)
{
    TickType_t       xLastWakeTime;
    const TickType_t xDelayTicks = TASK4_T / portTICK_PERIOD_MS;

    xLastWakeTime = xTaskGetTickCount();
    while (1) {
        if (!flag_stats)
            printf("\t\t\t\tI\t\t%llu\n", esp_timer_get_time() / 1000);

        for (long i = 0; i < ITERATE_4; i++)
            __asm__ __volatile__("NOP");

        if (!flag_stats)
            printf("\t\t\t\tO\t\t%llu\n", esp_timer_get_time() / 1000);

        xTaskDelayUntil(&xLastWakeTime, xDelayTicks);
    }
}

// TASK 5
void vTaskCode5(void *pvParameters)
{
    TickType_t       xLastWakeTime;
    const TickType_t xDelayTicks = TASK5_T / portTICK_PERIOD_MS;

    xLastWakeTime = xTaskGetTickCount();
    while (1) {
        if (!flag_stats)
            printf("\t\t\t\t\tI\t%llu\n", esp_timer_get_time() / 1000);

        for (long i = 0; i < ITERATE_5; i++)
            __asm__ __volatile__("NOP");

        if (!flag_stats)
            printf("\t\t\t\t\tO\t%llu\n", esp_timer_get_time() / 1000);

        xTaskDelayUntil(&xLastWakeTime, xDelayTicks);
    }
}

// APP MAIN
void app_main(void)
{
    gpio_set_direction(GPIO_OUTPUT_IO_0, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_OUTPUT_IO_1, GPIO_MODE_OUTPUT);

    gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL << PULSADOR,
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = true,
        .pull_down_en = false,
    };
    gpio_config(&io_conf);

    TaskHandle_t xHandle1 = NULL;
    TaskHandle_t xHandle2 = NULL;
    TaskHandle_t xHandle3 = NULL;
    TaskHandle_t xHandle4 = NULL;
    TaskHandle_t xHandle5 = NULL;

    //Todas prioridad 1
    xTaskCreate(vTaskCode1, "TASK1", STACK_SIZE, NULL, 1, &xHandle1);
    xTaskCreate(vTaskCode2, "TASK2", STACK_SIZE, NULL, 1, &xHandle2);
    xTaskCreate(vTaskCode3, "TASK3", STACK_SIZE, NULL, 1, &xHandle3);
    xTaskCreate(vTaskCode4, "TASK4", STACK_SIZE, NULL, 1, &xHandle4);
    xTaskCreate(vTaskCode5, "TASK5", STACK_SIZE, NULL, 1, &xHandle5);

    int entrada_digital_t0 = 0;
    int entrada_digital_t1 = 0;

    while (1) {
        entrada_digital_t0 = gpio_get_level(PULSADOR);
        if ((entrada_digital_t0 == 0) && (entrada_digital_t1 == 1))
            imprime_estadisticas();
        entrada_digital_t1 = entrada_digital_t0;
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

// ESTADÍSTICAS
void imprime_estadisticas(void)
{
    char     Buff[512]      = {0};
    char     task_list[512] = {0};
    uint32_t cpu_freq_hz    = 0;

    vTaskList(task_list);
    vTaskGetRunTimeStats(Buff);
    esp_clk_tree_src_get_freq_hz(SOC_CPU_CLK_SRC_PLL,
                                  ESP_CLK_TREE_SRC_FREQ_PRECISION_CACHED,
                                  &cpu_freq_hz);

    printf("**************************************\n");
    printf("Estado de las tareas:\n%s\n", task_list);
    printf("%s ", Buff);
    printf("La CPU se ha configurado a : %lu MHz\n", cpu_freq_hz / 1000000);
    printf("TIME SLICE: %d Hz, %.1f ms\n",
           configTICK_RATE_HZ, (float)(1000.0 / configTICK_RATE_HZ));
    printf("**************************************\n");
}