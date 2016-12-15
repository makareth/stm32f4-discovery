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

	hspi.Init.Mode = SPI_MODE_MASTER;
	hspi.Init.Direction = SPI_DIRECTION_2LINES;
	hspi.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
	//hspi.Init.CRCCalculation = SPI_CRCCALCULATION_ENABLE;      
	//hspi.Init.CRCPolynomial = 7;
	hspi.Init.NSS = SPI_NSS_SOFT;      
	hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;                   

	if(HAL_SPI_Init(&hspi) != HAL_OK) {
    	Error_Handler();
	}
  
	__HAL_SPI_ENABLE(&hspi);


	return 0;
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *h)
{
	if(h==NULL) {
		my_log(0,SPI_MODULE,"hspi is null");
		return;
	}

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

uint8_t write()
{


  my_log(0,SPI_MODULE,"SPI tx/rx\r\n");
  HAL_StatusTypeDef ret;
  uint8_t txData[2]={0x0f,0x00};
  uint8_t rxData[2]={0x00,0x00};

  my_log(0,SPI_MODULE,"HAL_SPI_TransmitReceive tx/rx\r\n");

  HAL_GPIO_WritePin (SPI1_PORTE_GPIO_PORT, SPI1_CS_PIN, GPIO_PIN_RESET);

  ret = HAL_SPI_TransmitReceive(&hspi, txData, rxData, 1, 500);
  HAL_GPIO_WritePin (SPI1_PORTE_GPIO_PORT, SPI1_CS_PIN, GPIO_PIN_SET);

  //ret = HAL_SPI_Transmit(&hspi, txData, 1, 1000);
  my_log(0,SPI_MODULE,"HAL_SPI_TransmitReceive returned <ret=%d>, res = <%x>\n",ret,rxData[0]);

  return 0;
}
