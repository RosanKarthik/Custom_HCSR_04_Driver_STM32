# HC-SR04 Ultrasonic Sensor Driver for STM32 (HAL-based)

This project provides a reusable driver and example integration for interfacing the **HC-SR04 ultrasonic distance sensor** with STM32 microcontrollers using the **HAL (Hardware Abstraction Layer)**.
This was done using the STM32F446RE Board and STM32-CubeIDE
---

## 📁 Project Structure

```
Core/
├── Inc/
│   ├── hcsr_04.h        # Public header file for the HC-SR04 driver
│
├── Src/
│   ├── hcsr_04.c        # Driver implementation (trigger/echo timing, distance logic)
│   ├── main.c           # Minimal usage example with UART output
```

---

##  What This Code Does

- Measures echo pulse width
- Calculates and returns distance in centimeters
- Can Error handling
- Can be used to outputs distance readings or timeout messages over UART

---

##  Driver Features

- `HCSR04_Init(...)`: Initializes the driver with custom GPIO pins and timer
- `HCSR04_DelayUs(...)`: Delay using hardware timers in microseconds
- `HCSR04_ReadDistance(...)`: Triggers a distance measurement and returns the result via pointer
- `HCSR04_DeInit(...)`: Deinitialize GPIOs and stop the timer

---

##  How to Use the Driver

### 1. Include the Header

```c
#include "hcsr_04.h"
```

### 2. Declare a Driver Instance

```c
HCSR04_InitTypeDef hcsr;
```

### 3. Initialize It (inside `main()`)

```c
HCSR04_Init(&hcsr, GPIOA, GPIOA, GPIO_PIN_3, GPIO_PIN_2, &htim2);
```

This sets:
- Echo pin: PA3  
- Trigger pin: PA2  
- Timer: TIM2

> Change the GPIOs or timer as needed for your board.

### 4. Read Distance in Loop

```c
float dist;
if (HCSR04_ReadDistance(&hcsr, &dist) == HCSR04_OK)
{
    sprintf(msg, "Distance: %.2f cm\r\n", dist);
}
else
{
    sprintf(msg, "Sensor Timeout\r\n");
}
HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
```

---

## Output Example

```
Distance: 23.45 cm
Distance: 25.32 cm
Sensor Timeout
```

---

##  Dependencies

- STM32CubeMX or STM32CubeIDE project with:
  - HAL drivers enabled
  - One general-purpose timer (e.g., TIM2)
  - UART configured for debug output

---
