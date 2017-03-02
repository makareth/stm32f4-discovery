
#include "console.h"
#include "error.h"
#include "stm32f4xx.h"


#include "lis3dsh.h"
#include "spi.h"

#define LIS3DSH_MODULE "lis3dsh"

uint8_t LIS3DSH_Read_REG4()
{
	uint8_t txData = {LIS3DSH_REG4_REG};
	uint8_t rxData = 0x00;
	SPI_Read(&txData, &rxData);

	my_log(0,LIS3DSH_MODULE,"%s LIS3DSH_REG4_REG = <%x>\n", __FUNCTION__, rxData);

	return 0;
}

uint8_t LIS3DSH_Whoami()
{
	uint8_t txData=LIS3DSH_WHOAMI_REG;
	uint8_t rxData=0x00;
	SPI_Read(&txData, &rxData);

	my_log(0,LIS3DSH_MODULE,"%s WHO_AM_I = <%x>\n", __FUNCTION__, rxData);

	return 0;
}

uint8_t LIS3DSH_Init()
{
	uint8_t txData5[2]={LIS3DSH_REG5_REG,0x00};
	uint8_t rxData5[2]={0x55};
	SPI_Write(txData5, rxData5, 2);

	uint8_t txData4[]={LIS3DSH_REG4_REG,0x67};
	uint8_t rxData4[2]={0x55};
	SPI_Write(txData4, rxData4, 2);

	my_log(0,LIS3DSH_MODULE,"%s done !\n", __FUNCTION__);

	return 0;
}

uint8_t LIS3DSH_GetAccel(uint8_t high_reg, uint8_t low_reg, int16_t *accel)
{
	uint8_t txData=0x55;
	uint8_t rxData=0x55;

	if(!accel)
		return 1;

	*accel=0;

	txData=low_reg;
	SPI_Read(&txData, &rxData);

	*accel |= rxData;
	txData=high_reg;
	SPI_Read(&txData, &rxData);
	*accel |= (rxData<<8);

	return 0;
}

uint8_t LIS3DSH_Status()
{
	uint8_t txData[]={LIS3DSH_STATUS_REG};
	uint8_t rxData[]={0x00};
	SPI_Write(txData, rxData, 1);

	my_log(0,LIS3DSH_MODULE,"%s Status = <%x>\n", __FUNCTION__, rxData[0]);

	return 0;
}
