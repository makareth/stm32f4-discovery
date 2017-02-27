#pragma once

#include "stm32f4xx_hal.h"

int16_t DMA_Init_Tx(void);
int16_t DMA_Init_Rx(void);

DMA_HandleTypeDef* DMA_GetTxHandle();
DMA_HandleTypeDef* DMA_GetRxHandle();

