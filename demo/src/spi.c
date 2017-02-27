#include "spi.h"
#include "console.h"
#include "error.h"
#include "stm32f4xx.h"
#include "main.h"

#define SPI_MODULE "spi"

SPI_HandleTypeDef  hspi;

	 DMA_HandleTypeDef hdmaTx = {};
  	 DMA_HandleTypeDef hdmaRx;

DMA_HandleTypeDef* DMA_Tx_GetHandle()
{
	return &hdmaTx;
}

DMA_HandleTypeDef* DMA_Rx_GetHandle()
{
	return &hdmaRx;
}


SPI_HandleTypeDef* SPI_GetHandle()
{
	return &hspi;
}

int16_t SPI_Init(void)
{

	HAL_SPI_DeInit(&hspi);

	SPI1_CLK_ENABLE();

	hspi.Instance = SPI1;
	hspi.Init.Mode = SPI_MODE_MASTER;
	hspi.Init.Direction = SPI_DIRECTION_2LINES;
	hspi.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi.Init.CLKPhase = SPI_PHASE_2EDGE;
	hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;      
	hspi.Init.CRCPolynomial = 7;
	hspi.Init.NSS = SPI_NSS_SOFT;      
	hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;                   
	hspi.Init.TIMode = SPI_TIMODE_DISABLE;

	if(HAL_SPI_Init(&hspi) != HAL_OK) {
    	Error_Handler();
	}

    my_log(0,SPI_MODULE,"%s error=%d, state=%d\r\n", __FUNCTION__, hspi.ErrorCode,hspi.State);
  __HAL_SPI_ENABLE(&hspi);
	return 0;
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *h)
{


	if(h==NULL) {
		my_log(0,SPI_MODULE,"hspi is null");
		return;
	}

	my_log(0,SPI_MODULE,"%s\r\n",__FUNCTION__);

	__HAL_RCC_DMA2_CLK_ENABLE();

	SPI1_GPIOA_CLK_ENABLE();
	SPI1_GPIOE_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = SPI1_MOSI_PIN | SPI1_SCK_PIN | SPI1_MISO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(SPI1_PORTA_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitTypeDef GPIO_InitStructE;
    GPIO_InitStructE.Pin = SPI1_CS_PIN;
    GPIO_InitStructE.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructE.Pull  = GPIO_NOPULL;
  	GPIO_InitStructE.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(SPI1_PORTE_GPIO_PORT, &GPIO_InitStructE);

	hdmaTx.Instance 				= DMA2_Stream3;
	hdmaTx.Init.Channel 			= DMA_CHANNEL_3;
	hdmaTx.Init.Direction 			= DMA_MEMORY_TO_PERIPH;
	hdmaTx.Init.PeriphInc 			= DMA_PINC_DISABLE;
	hdmaTx.Init.MemInc 				= DMA_MINC_ENABLE;
	hdmaTx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdmaTx.Init.MemDataAlignment 	= DMA_MDATAALIGN_BYTE;
	hdmaTx.Init.Mode 				= DMA_NORMAL;
	hdmaTx.Init.Priority 			= DMA_PRIORITY_LOW;
	hdmaTx.Init.FIFOMode 			= DMA_FIFOMODE_DISABLE;
	hdmaTx.Init.FIFOThreshold 		= DMA_FIFO_THRESHOLD_FULL;
	hdmaTx.Init.MemBurst            = DMA_MBURST_INC4;
    hdmaTx.Init.PeriphBurst         = DMA_PBURST_INC4;

	hdmaTx.XferCpltCallback			= HAL_DMA_TxCpltCallback;
	hdmaTx.XferHalfCpltCallback		= HAL_DMA_TxHalfCpltCallback;
	hdmaTx.XferErrorCallback		= HAL_DMA_ErrorCallback;
	hdmaTx.XferAbortCallback		= HAL_DMA_ErrorCallback;

	HAL_DMA_Init(&hdmaTx);
    __HAL_LINKDMA(h, hdmatx, hdmaTx);

	hdmaRx.Instance 				= DMA2_Stream0;
	hdmaRx.Init.Channel 			= DMA_CHANNEL_3;
	hdmaRx.Init.Direction 			= DMA_PERIPH_TO_MEMORY;
	hdmaRx.Init.PeriphInc 			= DMA_PINC_DISABLE;
	hdmaRx.Init.MemInc 				= DMA_MINC_ENABLE;
	hdmaRx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdmaRx.Init.MemDataAlignment 	= DMA_MDATAALIGN_BYTE;
	hdmaRx.Init.Mode 				= DMA_NORMAL;
	hdmaRx.Init.Priority 			= DMA_PRIORITY_HIGH;
	hdmaRx.Init.FIFOMode 			= DMA_FIFOMODE_DISABLE;
	hdmaRx.Init.FIFOThreshold 		= DMA_FIFO_THRESHOLD_FULL;
	hdmaRx.Init.MemBurst            = DMA_MBURST_INC4;
    hdmaRx.Init.PeriphBurst         = DMA_PBURST_INC4;


	HAL_DMA_Init(&hdmaRx);
    __HAL_LINKDMA(h, hdmarx, hdmaRx);



  	/*##-4- Configure the NVIC for DMA #########################################*/ 
	/* NVIC configuration for DMA transfer complete interrupt (SPI3_TX) */
	HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
// TODO SCO enableirq fout la grouille

	/* NVIC configuration for DMA transfer complete interrupt (SPI3_RX) */
	HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 1);   
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

	/*##-5- Configure the NVIC for SPI #########################################*/
	HAL_NVIC_SetPriority(SPI1_IRQn, 0, 2);
	HAL_NVIC_EnableIRQ(SPI1_IRQn);
}


uint8_t SPI_Write(uint8_t *txData, uint8_t *rxData, uint8_t len)
{
  HAL_GPIO_WritePin (SPI1_PORTE_GPIO_PORT, SPI1_CS_PIN, GPIO_PIN_RESET);
  HAL_SPI_TransmitReceive(&hspi, txData, rxData, len, 200);
  HAL_GPIO_WritePin (SPI1_PORTE_GPIO_PORT, SPI1_CS_PIN, GPIO_PIN_SET);

  return 0;
}

uint8_t SPI_Read(uint8_t *txData, uint8_t *rxData)
{
	uint32_t	cnt = 1;

  	*txData |= 0x80;

  	HAL_GPIO_WritePin (SPI1_PORTE_GPIO_PORT, SPI1_CS_PIN, GPIO_PIN_RESET);

	HAL_StatusTypeDef ret;

    ret = HAL_SPI_Transmit_DMA(&hspi, txData, cnt);

    while (HAL_SPI_GetState(&hspi) != HAL_SPI_STATE_READY) {}

    ret = HAL_SPI_Receive_DMA(&hspi, rxData, cnt);
    while (HAL_SPI_GetState(&hspi) != HAL_SPI_STATE_READY) {}

  	HAL_GPIO_WritePin (SPI1_PORTE_GPIO_PORT, SPI1_CS_PIN, GPIO_PIN_SET);

  return 0;
}


void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi) {
	BSP_LED_On(LED3);
    my_log(0,SPI_MODULE,"SPI error callback\r\n");
}

void HAL_DMA_TxCpltCallback(DMA_HandleTypeDef *hdma)
{
	  my_log(0,SPI_MODULE,"SPI HAL_DMA_TxCpltCallback callback\r\n");
}


void HAL_DMA_TxHalfCpltCallback(DMA_HandleTypeDef *hdma)
{
	  my_log(0,SPI_MODULE,"SPI HAL_DMA_TxHalfCpltCallback callback\r\n");
}


void HAL_DMA_ErrorCallback(DMA_HandleTypeDef *hdma)
{
	BSP_LED_On(LED3);
	  my_log(0,SPI_MODULE,"SPI HAL_DMA_ErrorCallback callback\r\n");
}

void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi) {
	my_log(0,SPI_MODULE,"SPI HAL_SPI_TxRxHalfCpltCallback callback\r\n");
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
	my_log(0,SPI_MODULE,"SPI HAL_SPI_TxRxCpltCallback callback\r\n");
}
