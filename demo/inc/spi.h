#pragma once

#include "stm32f4xx_hal.h"

#define SPI1_CLK_ENABLE() __HAL_RCC_SPI1_CLK_ENABLE();

#define SPI1_GPIOA_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPI1_GPIOE_CLK_ENABLE()      __HAL_RCC_GPIOE_CLK_ENABLE()

#define SPI1_MOSI_PIN 				GPIO_PIN_7 
#define SPI1_SCK_PIN  				GPIO_PIN_5
#define SPI1_MISO_PIN 				GPIO_PIN_6
#define SPI1_CS_PIN 				GPIO_PIN_3
#define SPI1_PORTA_GPIO_PORT 		GPIOA
#define SPI1_PORTE_GPIO_PORT 		GPIOE

extern SPI_HandleTypeDef  hspi;


int16_t SPI_Init(void);
uint8_t write();