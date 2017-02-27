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
uint8_t SPI_Write(uint8_t *txData, uint8_t *rxData, uint8_t len);
uint8_t SPI_Read(uint8_t *txData, uint8_t *rxData);
uint8_t SPI_DMA_bind();
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi) ;
SPI_HandleTypeDef* SPI_GetHandle();

DMA_HandleTypeDef* DMA_Tx_GetHandle();
DMA_HandleTypeDef* DMA_Rx_GetHandle();

void HAL_DMA_TxCpltCallback(DMA_HandleTypeDef *hspi);
void HAL_DMA_TxHalfCpltCallback(DMA_HandleTypeDef *hspi);
void HAL_DMA_ErrorCallback(DMA_HandleTypeDef *hdma);

void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi);
