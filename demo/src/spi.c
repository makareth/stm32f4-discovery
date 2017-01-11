#include "spi.h"
#include "console.h"
#include "error.h"
#include "stm32f4xx.h"

#define SPI_MODULE "spi"

SPI_HandleTypeDef  hspi;

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
	//hspi.Init.CRCPolynomial = 7;
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
}

uint8_t SPI_Write(uint8_t *txData, uint8_t *rxData, uint8_t len)
{
  //txData[0] = txData[0] | 0x00;

  /*if(len>1)
  	txData[0] = txData[0] | 0x40;
*/
  HAL_GPIO_WritePin (SPI1_PORTE_GPIO_PORT, SPI1_CS_PIN, GPIO_PIN_RESET);

  HAL_SPI_TransmitReceive(&hspi, txData, rxData, len, 200);
  //HAL_SPI_Receive(&hspi, rxData, len, 200);

  HAL_GPIO_WritePin (SPI1_PORTE_GPIO_PORT, SPI1_CS_PIN, GPIO_PIN_SET);

  return 0;
}

uint8_t SPI_Read(uint8_t *txData, uint8_t *rxData, uint8_t len)
{
  HAL_StatusTypeDef ret;

  txData[0] |= 0x80;
/*
  if(len>1)
  	txData[0] = txData[0] | 0x40;
*/
  HAL_GPIO_WritePin (SPI1_PORTE_GPIO_PORT, SPI1_CS_PIN, GPIO_PIN_RESET);

  ret = HAL_SPI_Transmit(&hspi, &txData[0], 1, 200);
  ret = HAL_SPI_Receive(&hspi, &rxData[0], 2, 200);

/*
  ret = HAL_SPI_Transmit(&hspi, &txData[1], 1, 200);
  ret = HAL_SPI_Receive(&hspi, &rxData[1], 1, 200);
*/
  HAL_GPIO_WritePin (SPI1_PORTE_GPIO_PORT, SPI1_CS_PIN, GPIO_PIN_SET);

  return 0;
}
