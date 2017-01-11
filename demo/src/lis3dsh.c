
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

uint8_t LIS3DSH_GetAccelZ(uint16_t *accelZ)
{
	uint8_t txData=0x55;
	uint8_t rxData=0x55;

	if(!accelZ)
		return 1;

	*accelZ=0;

	txData=LIS3DSH_OUT_Z_L_REG;
	SPI_Read(&txData, &rxData);

	*accelZ |= rxData;
	txData=LIS3DSH_OUT_Z_H_REG;
	SPI_Read(&txData, &rxData);
	*accelZ |= (rxData<<8);

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
