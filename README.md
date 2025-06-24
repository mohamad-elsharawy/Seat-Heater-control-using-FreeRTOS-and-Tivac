# 🔥 Automotive Seat Heater Control System – FreeRTOS on TM4C123GH6PM

This project demonstrates a modular embedded automotive seat heating control system using **FreeRTOS** on the **Tiva-C TM4C123GH6PM** microcontroller (ARM Cortex-M4F).  
All drivers and layers are built entirely from scratch in **bare-metal C**, showcasing advanced embedded software design, layered architecture, and real-time task management.

---

## 💡 Features

- 🚗 Automotive seat heater system — adjustable via push buttons
- ⚙️ Built on **FreeRTOS** — task scheduling, queues, mutexes, semaphores
- 🧠 Event-driven system — efficient CPU usage with inter-task communication
- 🔄 Modular architecture — easy to scale to multiple seats
- 🔐 Resource protection — mutex for UART, semaphore for ADC
- 📊 CPU Load Monitoring — runtime measurement using custom logic
- 📂 Layered architecture: **Application**, **HAL**, **MCAL**
- 🔌 Full configuration: Static, Link-time, Post-build
- 💻 UART-based terminal display of system status

---

## 🧰 Hardware / Tools Used

| Item               | Description                        |
|--------------------|------------------------------------|
| **MCU**            | TM4C123GH6PM (Tiva-C LaunchPad)    |
| **Architecture**   | ARM Cortex-M4F                     |
| **RTOS**           | FreeRTOS                           |
| **Sensor**         | LM35 Analog Temperature Sensor     |
| **Inputs**         | Push Buttons                       |
| **Outputs**        | LEDs (Heater Level Indicators)     |
| **IDE / Toolchain**| Code Composer Studio / ARM-GCC     |
| **Debug Output**   | UART Terminal over USB             |

---

## 📐 Software Architecture

Application/
│ ├── Application.c / .h / _cfg.h / _PBcfg.c
│ ├── FreeRTOSConfig.h
│ └── tm4c123gh6pm_startup_ccs.c ← Startup code provided by TI
│
HAL/
│ ├── ECU/
│ ├── LED/
│ ├── Push button/
│ ├── LM35 temperature sensor/
│
MCAL/
│ ├── UART/
│ ├── ADC/
│ ├── Timer/
│ ├── DIO/
│ ├── PORT/
│ ├── NVIC/
│

---

## 🧪 RTOS Features Used

- ✅ `xTaskCreate()` – Multiple periodic and event-driven tasks
- ✅ `xQueueSend() / xQueueReceive()` – Task communication
- ✅ `xSemaphoreCreateMutex()` – Protect shared UART
- ✅ `xSemaphoreCreateBinary()` – ADC resource control
- ✅ `xQueueSendFromISR()` – ISR to task signaling
- ✅ `portYIELD_FROM_ISR()` – Immediate context switch from ISRs
- ✅ `vTaskSetApplicationTaskTag()` – For runtime CPU tracking

---

## 📋 Drivers Built From Scratch

| Layer  | Driver                    | Description                              |
|--------|---------------------------|------------------------------------------|
| MCAL   | UART                      | Interrupt-based, non-blocking TX         |
|        | ADC                       | 10-bit conversion, LM35 support          |
|        | Timer                     | Runtime tick tracking                    |
|        | DIO / PORT                | Digital I/O abstraction                  |
|        | NVIC                      | Interrupt enable/disable abstraction     |
| HAL    | Push Button               | Interrupt-driven input                   |
|        | LM35 Temperature Sensor   | Conversion start + interrupt read        |
|        | LED Driver                | Control intensity indicators             |
|        | Terminal Display          | UART interface wrapper for UI            |

---

## 🧠 Tasks Implemented

- `SeatControlTask` – Controls seat heater intensity based on current temp and mode
- `UpdateSeatButtonTask` – Handles user input via button press
- `UpdateSeatTempTask` – Reads temperature sensor data and updates system
- `LM35TempSensor_StartConversion_Task` – Periodically starts ADC conversions
- `DisplayTask` – Shows seat status and heater mode via UART
- `RunTimeMeasurmentsTask` – Monitors CPU usage (configurable)

---

## 📊 Example Output

```text
Seat: 0
Heater mode: Medium
Temperature: 39
CPU Load = 17%
```

## 👨‍💻 Author

**Mohamed Elsharawy**  
Embedded Software Engineer 

📝 **Legal Notice**: The startup code file `tm4c123gh6pm_startup_ccs.c` is provided by Texas Instruments and used in compliance with their license. This file is **not open-source** and should not be modified or redistributed under GPL or similar licenses. Refer to the header in the file for details.





