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

📁 Practica1
├── Practica1-Ej3.1-AO.c
├── Practica1-Ej4.1-AO.c
├── Practica1-Ej4.2-AO.c
└── Practica1-Ej5.1-AO.c

📁 Practica2
├── Practica2-Ej2.1-AO.c
├── Practica2-Ej3.1-AO.c
├── Practica2-Ej4.1-AO.c
├── Practica2-Ej5.1-AO.c
└── Practica2-Ej6.1-AO.c

📁 Practica3
├── Practica3-Ej1.1-CodigoBase.c
├── Practica3-Ej2.1-AO.c
├── Practica3-Ej2.2-AO.c
├── Practica3-Ej2.3-AO.c
├── Practica3-Ej3.1-AO.c
├── Practica3-Ej4.1-AO.c
├── Practica3-Ej4.2-AO.c
├── Practica3-Ej5.1-AO.c
├── Practica3-Ej6.1-AO.c
├── Practica3-Ej7.1-AO.c
└── Practica3-Ej8.1-AO.c

---

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
