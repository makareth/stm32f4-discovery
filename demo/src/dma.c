#include "dma.h"
#include "console.h"
#include "error.h"
#include "stm32f4xx.h"

#define TAG "dma"

DMA_HandleTypeDef hdmaTx;
DMA_HandleTypeDef hdmaRx;

int16_t DMA_Init_Tx(void);
int16_t DMA_Init_Rx(void);


DMA_HandleTypeDef* DMA_GetTxHandle()
{
	return &hdmaTx;
}

DMA_HandleTypeDef* DMA_GetRxHandle()
{
	return &hdmaRx;
}

/*int16_t DMA_Init_Tx( void(*TransferErrorCb)(DMA_HandleTypeDef *DmaHandle), void(*TransferCompleteCb)(DMA_HandleTypeDef *DmaHandle))*/
int16_t DMA_Init_Tx()
{
	__HAL_RCC_DMA2_CLK_ENABLE();

	hdmaTx.Instance = DMA2_Stream3;
	hdmaTx.Init.Channel = DMA_CHANNEL_3;
	hdmaTx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	hdmaTx.Init.PeriphInc = DMA_PINC_ENABLE;
	hdmaTx.Init.MemInc = DMA_MINC_ENABLE;
	hdmaTx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdmaTx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdmaTx.Init.Mode = DMA_NORMAL;
	hdmaTx.Init.Priority = DMA_PRIORITY_LOW;
	hdmaTx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	hdmaTx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;

	if(HAL_DMA_Init(&hdmaTx) != HAL_OK)
	{
		my_log(0,TAG,"%s failed error=%d, state=%d\r\n", __FUNCTION__, hdmaTx.ErrorCode, hdmaTx.State);
    	Error_Handler();
	}

    my_log(0,TAG,"%s error=%d, state=%d\r\n", __FUNCTION__, hdmaTx.ErrorCode, hdmaTx.State);
  __HAL_DMA_ENABLE(&hdmaTx);
/*
    HAL_DMA_RegisterCallback(&hdmaTx, HAL_DMA_XFER_CPLT_CB_ID, TransferCompleteCb);
    HAL_DMA_RegisterCallback(&hdmaTx, HAL_DMA_XFER_ERROR_CB_ID, TransferErrorCb);
*/
	/*##-6- Configure NVIC for DMA transfer complete/error interrupts ##########*/
	/* Set Interrupt Group Priority */ 
	HAL_NVIC_SetPriority(DMA_STREAM_IRQ, 0, 0);

	/* Enable the DMA STREAM global Interrupt */
	HAL_NVIC_EnableIRQ(DMA_STREAM_IRQ);

 

	return 0;
}

int16_t DMA_Init_Rx(void)
{
	__HAL_RCC_DMA2_CLK_ENABLE();

	hdmaRx.Instance = DMA2_Stream0;

	hdmaRx.Init.Channel = DMA_CHANNEL_3;
	hdmaRx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdmaRx.Init.PeriphInc = DMA_PINC_ENABLE;
	hdmaRx.Init.MemInc = DMA_MINC_ENABLE;
	hdmaRx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdmaRx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdmaRx.Init.Mode = DMA_NORMAL;
	hdmaRx.Init.Priority = DMA_PRIORITY_LOW;
	hdmaRx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	hdmaRx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;

	if(HAL_DMA_Init(&hdmaRx) != HAL_OK)
	{
		my_log(0,TAG,"%s failed error=%d, state=%d\r\n", __FUNCTION__, hdmaRx.ErrorCode, hdmaRx.State);
    	Error_Handler();
	}

    my_log(0,TAG,"%s error=%d, state=%d\r\n", __FUNCTION__, hdmaRx.ErrorCode, hdmaRx.State);


    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);


    __HAL_DMA_ENABLE(&hdmaRx);

	return 0;
}

DMA_HandleTypeDef* DMA_GetTxHandle()
{
	return &hdmaTx;
}

DMA_HandleTypeDef* DMA_GetRxHandle()
{
	return &hdmaRx;
}