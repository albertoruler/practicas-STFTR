# 🧠 Sistemas Tolerantes a Fallos en Tiempo Real – Prácticas (ESP32 + ESP-IDF)

Este repositorio contiene las prácticas de la asignatura **Sistemas Tolerantes a Fallos en Tiempo Real**, desarrolladas en **lenguaje C** utilizando el framework **ESP-IDF** sobre el microcontrolador **ESP32**, programadas en **Visual Studio Code** con la extensión oficial de Espressif.

Las prácticas se centran en el diseño e implementación de sistemas embebidos en tiempo real utilizando **FreeRTOS**, analizando el comportamiento del sistema ante carga, concurrencia, interrupciones y posibles fallos.

---

## ⚙️ Tecnologías utilizadas

- 💻 Lenguaje: C
- 📟 Plataforma: ESP32
- 🧩 Framework: ESP-IDF
- 🧵 Sistema operativo: FreeRTOS (integrado en ESP-IDF)
- 🔌 IDE: Visual Studio Code + extensión ESP-IDF
- 📡 Periféricos: GPIO, ADC, interrupciones, timers

---

## 📁 Estructura del repositorio

El repositorio está organizado por prácticas y ejercicios:

Practica1/
┣ Practica1-Ej3.1-AO.c
┣ Practica1-Ej4.1-AO.c
┣ Practica1-Ej4.2-AO.c
┗ Practica1-Ej5.1-AO.c

Practica2/
┣ Practica2-Ej2.1-AO.c
┣ Practica2-Ej3.1-AO.c
┣ Practica2-Ej4.1-AO.c
┣ Practica2-Ej5.1-AO.c
┗ Practica2-Ej6.1-AO.c

Practica3/
┣ Practica3-Ej1.1-CodigoBase.c
┣ Practica3-Ej2.1-AO.c
┣ Practica3-Ej2.2-AO.c
┣ Practica3-Ej2.3-AO.c
┣ Practica3-Ej3.1-AO.c
┣ Practica3-Ej4.1-AO.c
┣ Practica3-Ej4.2-AO.c
┣ Practica3-Ej5.1-AO.c
┣ Practica3-Ej6.1-AO.c
┣ Practica3-Ej7.1-AO.c
┗ Practica3-Ej8.1-AO.c

---

# 📚 Descripción de las prácticas

---

## 🟦 Práctica 1 – Introducción a ESP32 y periféricos

En esta práctica se introducen los fundamentos del ESP32 y el uso de periféricos básicos, especialmente el **ADC (convertidor analógico-digital)**.

### 🔧 Ejemplo relevante: Lectura de ADC
adc_oneshot_read(adc1_handle, ADC_CHANNEL, &adc_raw);
voltaje = (adc_raw / 4095.0) * 3.3;

### 🎯 Objetivos

* Configuración del ADC en modo one-shot
* Lectura de señales analógicas
* Conversión de valores a voltaje real
* Gestión de errores con `esp_err_t`

### 🧠 Conceptos trabajados

* Inicialización de periféricos
* Adquisición de datos en tiempo real
* Manejo de errores hardware
* Programación básica en ESP-IDF

---

## 🟨 Práctica 2 – FreeRTOS y planificación de tareas

En esta práctica se trabaja con **concurrencia mediante FreeRTOS**, implementando múltiples tareas con diferentes frecuencias.

### 🔧 Ejemplo relevante: tareas periódicas
xTaskCreate(tareaLED3Hz, "LED_3Hz", STACK_SIZE, NULL, 1, NULL);
xTaskCreate(tareaLED6Hz, "LED_6Hz", STACK_SIZE, NULL, 1, NULL);

### 🎯 Objetivos

* Creación y gestión de tareas en FreeRTOS
* Planificación temporal (tareas periódicas)
* Uso de `vTaskDelayUntil`
* Control de GPIO (LEDs)
* Monitorización del sistema con `vTaskGetRunTimeStats`

### 🧠 Conceptos trabajados

* Concurrencia
* Planificación en tiempo real
* Medición de carga de CPU
* Análisis de rendimiento del sistema
* Comportamiento determinista vs no determinista

---

## 🟥 Práctica 3 – Interrupciones y tolerancia a fallos

En esta práctica se introduce el uso de **interrupciones (ISR)** y su interacción con el sistema en tiempo real.

### 🔧 Ejemplo relevante: ISR con cola
static void IRAM_ATTR isr_handler(void *arg)
{
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

### 🎯 Objetivos

* Configuración de interrupciones GPIO
* Comunicación entre ISR y tareas mediante colas
* Separación entre contexto de interrupción y tareas
* Análisis del impacto de ISR en el sistema

### 🧠 Conceptos trabajados

* ISR (Interrupt Service Routine)
* Colas en FreeRTOS
* Tiempo de respuesta del sistema
* Concurrencia avanzada
* Diseño de sistemas robustos

---

## ⚠️ Tolerancia a fallos en el sistema

A lo largo de las prácticas se analizan situaciones relacionadas con:

* Sobrecarga de CPU
* Latencia en tareas
* Interrupciones frecuentes
* Competencia por recursos compartidos
* Impacto de ISR en tareas críticas

El objetivo es comprender cómo el sistema responde ante condiciones adversas y cómo mantener su comportamiento en tiempo real.

---

## 🚀 Compilación y ejecución (ESP-IDF)
# Configurar entorno
. $HOME/esp/esp-idf/export.sh

# Seleccionar target ESP32
idf.py set-target esp32

# Compilar proyecto
idf.py build

# Flashear al dispositivo
idf.py -p /dev/ttyUSB0 flash

# Monitor serie
idf.py monitor

---

## 👨‍💻 Autor

* Estudiante: Alberto Ortiz
* Asignatura: Sistemas Tolerantes a Fallos en Tiempo Real
* Plataforma: ESP32 + ESP-IDF + FreeRTOS
* IDE: Visual Studio Code
