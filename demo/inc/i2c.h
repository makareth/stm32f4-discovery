#pragma once

#include "stm32f4xx_hal.h"

#define I2C1_CLK_ENABLE() __HAL_RCC_I2C1_CLK_ENABLE();

#define I2C1_GPIOA_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define I2C1_GPIOB_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2C1_GPIOC_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define I2C1_GPIOD_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

#define I2C1_WS_PIN					GPIO_PIN_4
#define I2C1_SDA_PIN 				GPIO_PIN_9 
#define I2C1_SCL_PIN  				GPIO_PIN_6
#define I2C1_RESET_PIN				GPIO_PIN_4

#define I2C1_MCK_PIN				GPIO_PIN_7
#define I2C1_SCK_PIN				GPIO_PIN_10
#define I2C1_SD_PIN 				GPIO_PIN_12

#define I2C1_PORTA_GPIO_PORT		GPIOA
#define I2C1_PORTB_GPIO_PORT		GPIOB
#define I2C1_PORTD_GPIO_PORT		GPIOD
#define I2C1_PORTC_GPIO_PORT		GPIOC

extern I2C_HandleTypeDef  hi2c;


void I2C_Init(void);
void HAL_I2C_MspInit(I2C_HandleTypeDef *h);

int8_t I2C_Write(uint16_t DevAddress, uint8_t *pData, uint16_t Size);
int8_t I2C_Read(uint16_t DevAddress, uint8_t reg, uint8_t *pData, uint16_t Size);

I2C_HandleTypeDef* I2C_GetHandle();

void I2S3_Init(void);
I2S_HandleTypeDef* I2S_GetI2SHandle();