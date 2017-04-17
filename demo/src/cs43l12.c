
#include "console.h"
#include "error.h"
#include "stm32f4xx.h"


#include "cs43l12.h"
#include "i2c.h"

#define CS43L12_MODULE "CS43L12"

uint8_t CS43L12_Init(void) {

	int8_t ret;
	uint8_t cmd[3];


	HAL_GPIO_WritePin (GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
	// REMOVED for freertos : 
	// HAL_Delay(100);

	cmd[0] = 0x02;
	cmd[1] = 0x01;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s 1 failed %d !\n", __FUNCTION__, ret);
		return 1;
	}

	cmd[0] = 0x00;
	cmd[1] = 0x99;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s 1 failed %d !\n", __FUNCTION__, ret);
		return 1;
	}

	cmd[0] = 0x47;
	cmd[1] = 0x80;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s 2 failed !\n", __FUNCTION__);
		return 1;
	}

	cmd[0] = 0x32;
	cmd[1] = 0x80;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s failed !\n", __FUNCTION__);
		return 1;
	}

	cmd[0] = 0x32;
	cmd[1] = 0x00;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s failed !\n", __FUNCTION__);
		return 1;
	}

	cmd[0] = 0x00;
	cmd[1] = 0x00;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s failed !\n", __FUNCTION__);
		return 1;
	}

	// headphone power control
	cmd[0] = 0x04;
	cmd[1] = 0xAA;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s failed !\n", __FUNCTION__);
		return 1;
	}

	// headphone power control
	cmd[0] = 0x0D;
	cmd[1] = 0x70;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s failed !\n", __FUNCTION__);
		return 1;
	}

	// clocking control
	cmd[0] = 0x05;
	cmd[1] = 0x81;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s failed !\n", __FUNCTION__);
		return 1;
	}

	// _IF_CTRL1
	cmd[0] = 0x06;
	cmd[1] = 0x07;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s failed !\n", __FUNCTION__);
		return 1;
	}






	/* BEEP configuration */
	cmd[0] = 0x1C;
	cmd[1] = 0xFF;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s 1 failed %d !\n", __FUNCTION__, ret);
		return 1;
	}

	/* BBEP OFFTIME and VOLUME */
	cmd[0] = 0x1D;
	cmd[1] = 0xE6;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s 1 failed %d !\n", __FUNCTION__, ret);
		return 1;
	}

	/* BEEP tone configuration */
	cmd[0] = 0x1E;
	cmd[1] = 0xC0;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s 1 failed %d !\n", __FUNCTION__, ret);
		return 1;
	}

	/* Master volume */
	cmd[0] = 0x20;
	cmd[1] = 0x18;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s 1 failed %d !\n", __FUNCTION__, ret);
		return 1;
	}

	cmd[0] = 0x21;
	cmd[1] = 0x18;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s 1 failed %d !\n", __FUNCTION__, ret);
		return 1;
	}

	/* headphone volume */
	cmd[0] = 0x22;
	cmd[1] = 0xff;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s 1 failed %d !\n", __FUNCTION__, ret);
		return 1;
	}

	cmd[0] = 0x23;
	cmd[1] = 0xff;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s 1 failed %d !\n", __FUNCTION__, ret);
		return 1;
	}

	// ramp
	cmd[0] = 0x0A;
	cmd[1] = 0x00;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s 1 failed %d !\n", __FUNCTION__, ret);
		return 1;
	}

	// Limiter
	cmd[0] = 0x27;
	cmd[1] = 0x00;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s 1 failed %d !\n", __FUNCTION__, ret);
		return 1;
	}


/* tone configuration */
	cmd[0] = 0x1A | 0x80;
	cmd[1] = 0x0A;
	cmd[2] = 0x0A;

	ret = I2C_Write(CS43L12_ADDRESS, cmd, 3);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s 1 failed %d !\n", __FUNCTION__, ret);
		return 1;
	}


	/* tone configuration */
	cmd[0] = 0x1F;
	cmd[1] = 0x0F;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s 1 failed %d !\n", __FUNCTION__, ret);
		return 1;
	}

	cmd[0] = 0x02;
	cmd[1] = 0x9E;
	ret = I2C_Write(CS43L12_ADDRESS, cmd, 2);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s failed !\n", __FUNCTION__);
		return 1;
	}

	my_log(0,CS43L12_MODULE,"%s done !\n", __FUNCTION__);

	return 0;
}

uint8_t CS43L12_ReadId() {

	int8_t ret;
	uint8_t buf;

	uint8_t reg = 0x01;

	ret = I2C_Read(CS43L12_ADDRESS, reg, &buf, 1);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s failed (%d)!\n", __FUNCTION__, ret);
		return 1;
	}

	my_log(0,CS43L12_MODULE,"%s id = %x\n", __FUNCTION__,  buf);
	return 0;
}


uint8_t CS43L12_ReadError() {

	int8_t ret;
	uint8_t buf;

	uint8_t reg = 0x2e;

	ret = I2C_Read(CS43L12_ADDRESS, reg, &buf, 1);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s failed (%d)!\n", __FUNCTION__, ret);
		return 1;
	}

	my_log(0,CS43L12_MODULE,"%s id = %x\n", __FUNCTION__,  buf);
	return 0;
}


uint8_t CS43L12_ReadMasterVolume() {

	int8_t ret;
	uint8_t buf;

	uint8_t reg = 0x20;

	ret = I2C_Read(CS43L12_ADDRESS, reg, &buf, 1);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s failed (%d)!\n", __FUNCTION__, ret);
		return 1;
	}

	my_log(0,CS43L12_MODULE,"%s master volume = %x\n", __FUNCTION__,  buf);
	return 0;
}



uint8_t CS43L12_ReadPower() {

	int8_t ret;
	uint8_t buf;

	uint8_t reg = 0x02;

	ret = I2C_Read(CS43L12_ADDRESS, reg, &buf, 1);
	if(ret) {
		my_log(0,CS43L12_MODULE,"%s failed (%d)!\n", __FUNCTION__, ret);
		return 1;
	}

	my_log(0,CS43L12_MODULE,"%s power = %x\n", __FUNCTION__,  buf);
	return 0;
}


uint8_t CS43L12_BeepContinuous() {

	uint16_t Istr[1];

	Istr[0] = 0x00;

	my_log(0,CS43L12_MODULE,"%s Beeping\n", __FUNCTION__);
 	while (1) {
		if( HAL_I2S_Transmit (I2S_GetI2SHandle(), Istr , 1, 10 ) != HAL_OK) {    //!!this made it work!!
		}
  	}
}