#include "spi.h"
#include "console.h"
#include "error.h"
#include "stm32f4xx.h"
#include "main.h"
#include "i2c.h"

#define I2C_MODULE "i2c"

I2C_HandleTypeDef  hi2c;


I2C_HandleTypeDef* I2C_GetHandle()
{
	return &hi2c;
}



I2S_HandleTypeDef hi2s3;

I2S_HandleTypeDef* I2S_GetI2SHandle() {
	return &hi2s3;
}


void I2S3_Init(void) {

	__SPI3_CLK_ENABLE();

	hi2s3.Instance = SPI3;
	hi2s3.Init.Mode = I2S_MODE_MASTER_TX;
	hi2s3.Init.Standard = I2S_STANDARD_PHILIPS;
	hi2s3.Init.DataFormat = I2S_DATAFORMAT_16B;
	hi2s3.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE; // Enables MCLK output
	hi2s3.Init.AudioFreq = I2S_AUDIOFREQ_44K;
	hi2s3.Init.CPOL = I2S_CPOL_LOW;
	hi2s3.Init.ClockSource = I2S_CLOCK_PLL;
	hi2s3.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;

	if (HAL_I2S_Init(&hi2s3) != HAL_OK) {
	    Error_Handler();
	}

	//my_log(0,I2C_MODULE,"%s done !\n", __FUNCTION__);
}


void HAL_I2S_MspInit(I2S_HandleTypeDef *h) {

	if(h==NULL) {
		my_log(0,I2C_MODULE,"i2c handle is null");
		return;
	}

	my_log(0,I2C_MODULE,"%s\r\n",__FUNCTION__);

	I2C1_GPIOA_CLK_ENABLE();
	I2C1_GPIOC_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;


    /* I2S pins */
    GPIO_InitStruct.Pin = I2C1_MCK_PIN | I2C1_SCK_PIN | I2C1_SD_PIN;
    GPIO_InitStruct.Alternate = GPIO_AF6_SPI3; //Selects alternate function (I2C1)
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; //Selects alternate function open drain mode
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST; //Selects fast speed
    GPIO_InitStruct.Pull = GPIO_NOPULL; //Selects no pull-up or pull-down activation
    HAL_GPIO_Init(I2C1_PORTC_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = I2C1_WS_PIN;
    GPIO_InitStruct.Alternate = GPIO_AF6_SPI3; //Selects alternate function (I2C1)
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(I2C1_PORTA_GPIO_PORT, &GPIO_InitStruct);

	my_log(0,I2C_MODULE,"%s done\r\n",__FUNCTION__);

    return;
}


void I2C_Init(void){

	__I2C1_CLK_ENABLE();

    if(HAL_I2C_GetState(&hi2c) == HAL_I2C_STATE_RESET) {
    	hi2c.Instance = I2C1;
		hi2c.Init.ClockSpeed = 100000;
		hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
		hi2c.Init.OwnAddress1 = 0x33;
		hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;

		/* Init the I2C */
		HAL_I2C_Init(&hi2c);
	}
}


void HAL_I2C_MspInit(I2C_HandleTypeDef *h) {

	if(h==NULL) {
		my_log(0,I2C_MODULE,"i2c handle is null");
		return;
	}

	my_log(0,I2C_MODULE,"%s\r\n",__FUNCTION__);

	I2C1_GPIOA_CLK_ENABLE();
	I2C1_GPIOB_CLK_ENABLE();
	I2C1_GPIOC_CLK_ENABLE();
	I2C1_GPIOD_CLK_ENABLE();

	HAL_GPIO_WritePin (GPIOD, GPIO_PIN_4, GPIO_PIN_RESET);

	GPIO_InitTypeDef GPIO_InitStruct;


    GPIO_InitStruct.Pin = I2C1_SDA_PIN | I2C1_SCL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(I2C1_PORTB_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = I2C1_RESET_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(I2C1_PORTD_GPIO_PORT, &GPIO_InitStruct);


    /* I2S pins */
    GPIO_InitStruct.Pin = I2C1_MCK_PIN | I2C1_SCK_PIN | I2C1_SD_PIN;
    GPIO_InitStruct.Alternate = GPIO_AF6_SPI3; //Selects alternate function (I2C1)
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; //Selects alternate function open drain mode
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST; //Selects fast speed
    GPIO_InitStruct.Pull = GPIO_NOPULL; //Selects no pull-up or pull-down activation
    HAL_GPIO_Init(I2C1_PORTC_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = I2C1_WS_PIN;
    GPIO_InitStruct.Alternate = GPIO_AF6_SPI3; //Selects alternate function (I2C1)
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(I2C1_PORTA_GPIO_PORT, &GPIO_InitStruct);


    return;
}


int8_t I2C_Write(uint16_t DevAddress, uint8_t *pData, uint16_t Size) {

	HAL_StatusTypeDef ret;

	I2C_HandleTypeDef *h = I2C_GetHandle();

	if(h == NULL) {
		my_log(0,I2C_MODULE,"h null\n");
		return (-1);
	}
/*
	if(!HAL_I2C_IsDeviceReady(I2C_GetHandle(),DevAddress,3,500)) {
		my_log(0,I2C_MODULE,"not ready\n");
		return (-1);
	}
*/
	ret = HAL_I2C_Master_Transmit(h, DevAddress, pData, Size, 500);
	if(ret) {
		my_log(0,I2C_MODULE,"HAL_I2C_Master_Transmit returned %d (size=%d)\n", ret, Size);
		return (-1);
	}
	my_log(0,I2C_MODULE,"OKOK\n");

	return 0;
}


int8_t I2C_Read(uint16_t DevAddress, uint8_t reg, uint8_t *pData, uint16_t Size) {

	HAL_StatusTypeDef ret;

	I2C_HandleTypeDef *h = I2C_GetHandle();

	if(h == NULL)
		return (-1);
/*
	if(!HAL_I2C_IsDeviceReady(I2C_GetHandle(),DevAddress>>1,3,500))
		return (-1);
*/

	ret = I2C_Write(DevAddress, &reg, 1); 
	if(ret) {
		my_log(0,I2C_MODULE,"I2C_Write returned %d\n", ret);
		return (-1);
	}

	ret = HAL_I2C_Master_Receive(h, DevAddress, pData, Size, 500);
	if(ret) {
		my_log(0,I2C_MODULE,"HAL_I2C_Master_Receive returned %d\n", ret);
		return (-1);
	}

	my_log(0,I2C_MODULE,"HAL_I2C_Master_Receive returned %d\n", pData[0]);
	my_log(0,I2C_MODULE,"HAL_I2C_Master_Receive returned %d\n", pData[1]);
		my_log(0,I2C_MODULE,"HAL_I2C_Master_Receive returned %d\n", pData[2]);
			my_log(0,I2C_MODULE,"HAL_I2C_Master_Receive returned %d\n", pData[3]);

	return 0;
}

