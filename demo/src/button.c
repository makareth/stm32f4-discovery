
#include "console.h"
#include "error.h"
#include "stm32f4xx.h"


#include "button.h"
#include "spi.h"

#define BUTTON_MODULE "button"


uint8_t Button_Init()
{

	SPI1_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = BUTTON_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING; // SCO TODO regarder ds la doc
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	my_log(0,BUTTON_MODULE,"%s done !\n", __FUNCTION__);

	/*##-5- Configure the NVIC for SPI #########################################*/
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 2);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	return 0;
}
