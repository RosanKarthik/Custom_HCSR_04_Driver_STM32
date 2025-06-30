/*
 * hcsr_04.c
 *
 *  Created on: Jun 30, 2025
 *      Author: Rosan Karthik
 */
#include "hcsr_04.h"

void HCSR04_DelayUs(TIM_HandleTypeDef * tim, uint16_t us){
	__HAL_TIM_SET_COUNTER(tim,0);
	while(__HAL_TIM_GET_COUNTER(tim)<us){
		__NOP();
	}
}

void HCSR04_Init(
		HCSR04_InitTypeDef * HCSR,
		GPIO_TypeDef * _EchoGPIOx,
		GPIO_TypeDef * _TrigGPIOx,
		uint16_t _EchoPin,
		uint16_t _TrigPin,
		TIM_HandleTypeDef * _TIM
	){
	HCSR->distance=0;
	HCSR->_EchoGPIOx=_EchoGPIOx;
	HCSR->_TrigGPIOx=_TrigGPIOx;
	HCSR->_EchoPin=_EchoPin;
	HCSR->_TrigPin=_TrigPin;
	HCSR->_TIM=_TIM;
	HAL_TIM_Base_Start(HCSR->_TIM);
}

void HCSR04_DeInit(HCSR04_InitTypeDef * HCSR){
	HAL_GPIO_DeInit(HCSR->_EchoGPIOx,HCSR->_EchoPin);
	HAL_GPIO_DeInit(HCSR->_TrigGPIOx,HCSR->_TrigPin);
	HAL_TIM_Base_Stop(HCSR->_TIM);
}

HCSR04_StatusTypeDef HCSR04_ReadDistance(HCSR04_InitTypeDef * HCSR,float *distance){
	uint16_t t_taken=0;
	uint16_t timeout;
	HAL_GPIO_WritePin(HCSR->_TrigGPIOx,HCSR->_TrigPin,GPIO_PIN_RESET);
	HCSR04_DelayUs(HCSR->_TIM,2);
	HAL_GPIO_WritePin(HCSR->_TrigGPIOx,HCSR->_TrigPin,GPIO_PIN_SET);
	HCSR04_DelayUs(HCSR->_TIM,10);
	HAL_GPIO_WritePin(HCSR->_TrigGPIOx,HCSR->_TrigPin,GPIO_PIN_RESET);

	timeout = 10000;
	while (!HAL_GPIO_ReadPin(HCSR->_EchoGPIOx, HCSR->_EchoPin)) {
		if (timeout-- == 0) return HCSR04_TIMEOUT;
		HCSR04_DelayUs(HCSR->_TIM, 1);
	}

	timeout = 30000;  // echo HIGH time — max distance
	while (HAL_GPIO_ReadPin(HCSR->_EchoGPIOx, HCSR->_EchoPin)) {
		if (timeout-- == 0) return HCSR04_TIMEOUT;
		t_taken++;
		HCSR04_DelayUs(HCSR->_TIM, 1);
	}

	*distance=t_taken/58.0f;
	HCSR->distance=*distance;
	return HCSR04_OK;
}

