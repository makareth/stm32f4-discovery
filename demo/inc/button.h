#pragma once

#include "stm32f4xx_hal.h"

#define SPI1_CLK_ENABLE() __HAL_RCC_SPI1_CLK_ENABLE();

#define SPI1_GPIOA_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPI1_GPIOE_CLK_ENABLE()      __HAL_RCC_GPIOE_CLK_ENABLE()

#define BUTTON_PIN 				GPIO_PIN_0 
#define BUTTON_PORTA_GPIO_PORT 		GPIOA



uint8_t Button_Init(void);
