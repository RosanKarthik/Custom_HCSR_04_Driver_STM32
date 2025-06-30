/*
 * hcsr_04.h
 *
 *  Created on: Jun 30, 2025
 *      Author: HAI
 */

#ifndef INC_HCSR_04_H_
#define INC_HCSR_04_H_

#define STM32XXXX_HAL_HEADER_FILE "stm32f4xx_hal.h" //example "stm32g4xx_hal.h"
#define STM32XXXX_HAL_TIM_HEADER_FILE "stm32f4xx_hal_tim.h" //example "stm32g4xx_hal_tim.h"

#include STM32XXXX_HAL_HEADER_FILE
#include STM32XXXX_HAL_TIM_HEADER_FILE

//Status Of The Sensor For Error Handling
typedef enum {
	HCSR04_OK = 0,
	HCSR04_TIMEOUT = 1
} HCSR04_StatusTypeDef;

//Structure To Store Configuration Data For The Sensor
typedef struct{
	float distance;
	GPIO_TypeDef * _EchoGPIOx;
	GPIO_TypeDef * _TrigGPIOx;
	uint16_t _EchoPin;
	uint16_t _TrigPin;
	TIM_HandleTypeDef * _TIM;
}HCSR04_InitTypeDef;

void HCSR04_DelayUs(TIM_HandleTypeDef * tim, uint16_t us);

/**
  * @brief  Intitalizes the HCSR04 Driver.
  * @param	HCSR instance of a HCSR04 driver.
  * @param  _EchoGPIOx where x can be (A..G) to select the GPIO peripheral for STM32xxxx family.
  * @param  _EchoPin specifies the pin Echo is connected.
  * @param  _TrigGPIOx where x can be (A..G) to select the GPIO peripheral for STM32xxxx family.
  * @param  _TrigPin specifies the pin Trig is connected.
  * @param 	TIM handler for timer with frequency to count 1us.
  * @retval None
  */
void HCSR04_Init(
		HCSR04_InitTypeDef * HCSR,
		GPIO_TypeDef * _EchoGPIOx,
		GPIO_TypeDef * _TrigGPIOx,
		uint16_t _EchoPin,
		uint16_t _TrigPin,
		TIM_HandleTypeDef * _TIM
	);

/**
  * @brief  DeIntitalizes the HCSR04 Driver.
  * @param	HCSR instance of a HCSR04 driver.
  * @retval None
  */
void HCSR04_DeInit(HCSR04_InitTypeDef *HCSR);

/**
  * @brief  Calculates the distances and stores it in *distance
  * @param	HCSR instance of a HCSR04 driver.
  * @param 	Distance variable to store the output.
  * @retval Returns the status of the sensor.
  */
HCSR04_StatusTypeDef HCSR04_ReadDistance(
	HCSR04_InitTypeDef *hcsr,
	float *distance
);

#endif /* INC_HCSR_04_H_ */
