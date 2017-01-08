
#include "console.h"
#include "error.h"
#include "stm32f4xx.h"


#include "lis3dsh.h"
#include "spi.h"

#define LIS3DSH_MODULE "spi"

uint8_t LIS3DSH_Whoami()
{
	uint8_t txData[2]={LIS3DSH_WHOAMI_REG};
	uint8_t rxData[2]={0x00};
	SPI_Write(txData, rxData, 1);

	my_log(0,LIS3DSH_MODULE,"%s WHO_AM_I = <%x>\n", __FUNCTION__, rxData[0]);

	return 0;
}


uint8_t LIS3DSH_On()
{
	uint8_t txData4[2]={LIS3DSH_REG4_REG,0x67};
	uint8_t rxData4[2]={0x00,0x00};
	SPI_Write(txData4, rxData4, 2);

	uint8_t txData3[2]={LIS3DSH_REG3_REG,0xC9};
	uint8_t rxData3[2]={0x00,0x00};
	SPI_Write(txData3, rxData3, 2);

	uint8_t txData5[2]={LIS3DSH_REG5_REG,0x20};
	uint8_t rxData5[2]={0x00,0x00};
	SPI_Write(txData5, rxData5, 2);


	my_log(0,LIS3DSH_MODULE,"%s success <%x %x> !\n", __FUNCTION__, rxData3[0], rxData3[1]);

	return 0;
}

uint8_t LIS3DSH_IntteruptOn()
{
	uint8_t txData[2]={LIS3DSH_REG3_REG,0xC8};
	uint8_t rxData[2]={0x00,0x00};
	SPI_Write(txData, rxData, 2);

	my_log(0,LIS3DSH_MODULE,"%s success !\n", __FUNCTION__);

	return 0;
}

uint8_t LIS3DSH_Temp()
{
	uint8_t txData[1]={LIS3DSH_OUT_T_REG};
	uint8_t rxData[1]={0x00};
	SPI_Write(txData, rxData, 1);

	my_log(0,LIS3DSH_MODULE,"%s T= <%x>\n", __FUNCTION__, rxData[0]);

	return 0;
}

uint8_t LIS3DSH_Out_x_l()
{
	uint8_t txData[1]={LIS3DSH_OUT_X_L_REG};
	uint8_t rxData[1]={0x00};
	SPI_Write(txData, rxData, 1);

	my_log(0,LIS3DSH_MODULE,"%s X_L= <%x>\n", __FUNCTION__, rxData[0]);

	return 0;
}

uint8_t LIS3DSH_Out_x_h()
{
	uint8_t txData[1]={LIS3DSH_OUT_X_H_REG};
	uint8_t rxData[1]={0x00};
	SPI_Write(txData, rxData, 1);

	my_log(0,LIS3DSH_MODULE,"%s X_H= <%x>\n", __FUNCTION__, rxData[0]);

	return 0;
}

uint8_t LIS3DSH_Out_y_l()
{
	uint8_t txData[1]={LIS3DSH_OUT_Y_L_REG};
	uint8_t rxData[1]={0x00};
	SPI_Write(txData, rxData, 1);

	my_log(0,LIS3DSH_MODULE,"%s Y_L= <%x>\n", __FUNCTION__, rxData[0]);

	return 0;
}

uint8_t LIS3DSH_Out_y_h()
{
	uint8_t txData[1]={LIS3DSH_OUT_Y_H_REG};
	uint8_t rxData[1]={0x00};
	SPI_Write(txData, rxData, 1);

	my_log(0,LIS3DSH_MODULE,"%s Y_H= <%x>\n", __FUNCTION__, rxData[0]);

	return 0;
}


uint8_t LIS3DSH_Out_z_l()
{
	uint8_t txData[1]={LIS3DSH_OUT_Z_L_REG};
	uint8_t rxData[1]={0x00};
	SPI_Write(txData, rxData, 1);

	my_log(0,LIS3DSH_MODULE,"%s Z_L= <%x>\n", __FUNCTION__, rxData[0]);

	return 0;
}

uint8_t LIS3DSH_Out_z_h()
{
	uint8_t txData[1]={LIS3DSH_OUT_Z_H_REG};
	uint8_t rxData[1]={0x00};
	SPI_Write(txData, rxData, 1);

	my_log(0,LIS3DSH_MODULE,"%s Z_H= <%x>\n", __FUNCTION__, rxData[0]);

	return 0;
}


uint8_t LIS3DSH_Status()
{
	uint8_t txData[2]={LIS3DSH_STATUS_REG};
	uint8_t rxData[2]={0x00};
	SPI_Write(txData, rxData, 1);

	my_log(0,LIS3DSH_MODULE,"%s Status = <%x>\n", __FUNCTION__, rxData[0]);

	return 0;
}
