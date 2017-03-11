/**
  ******************************************************************************
  * @file    GPIO/GPIO_EXTI/Src/main.c 
  * @author  MCD Application Team
  * @version V1.2.6
  * @date    06-May-2016
  * @brief   This example describes how to configure and use GPIOs through 
  *          the STM32F4xx HAL API.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "console.h"
#include "usart.h"
#include "spi.h"
#include "dma.h"
#include "lis3dsh.h"
#include "error.h"
#include "button.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup GPIO_EXTI
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MODULE_MAIN "main"

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void Error_Handler(void);


uint32_t    my_tick = 0;

/* Private functions ---------------------------------------------------------*/
void HAL_IncTick(void)
{
  my_tick++;
}

uint32_t HAL_GetTick(void)
{
  return my_tick;
}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  HAL_Init();

  /* Configure LED3, LED4, LED5 and LED6 */
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  BSP_LED_Init(LED5);
  BSP_LED_Init(LED6);

  /* Configure the system clock to 84 MHz */
  //SystemClock_Config();

  SysTick_Config(SystemCoreClock/ 1000);

  USART2_UART_Init();
  my_log(0,MODULE_MAIN,"UART initialized successfully\r\n");

  my_log(0,MODULE_MAIN,"SPI init\r\n");


  SPI_Init();
  HAL_Delay(300);

  Button_Init();

  LIS3DSH_Whoami();
  LIS3DSH_Init();
  LIS3DSH_Read_REG4();

  while(1)
  {

      HAL_Delay(50);
      
      /*int16_t accel = 0;
      LIS3DSH_GetAccel( LIS3DSH_OUT_X_H_REG , LIS3DSH_OUT_X_L_REG , &accel);
      if(accel>1000) {
        BSP_LED_On(LED5);
        BSP_LED_Off(LED4);
      }
      else if(accel<-1000){
        BSP_LED_On(LED4);
        BSP_LED_Off(LED5);
      }
      else {
        BSP_LED_Off(LED4);
        BSP_LED_Off(LED5);
      }

      my_log(0,MODULE_MAIN,"X= <%x> %d\r\n", accel, accel);
      LIS3DSH_GetAccel( LIS3DSH_OUT_Y_H_REG , LIS3DSH_OUT_Y_L_REG , &accel);
      my_log(0,MODULE_MAIN,"Y= <%x> %d\r\n", accel, accel);
      if(accel>1000) {
        BSP_LED_On(LED3);
        BSP_LED_Off(LED6);
      }
      else if(accel<-1000){
        BSP_LED_On(LED6);
        BSP_LED_Off(LED3);
      }
      else {
        BSP_LED_Off(LED3);
        BSP_LED_Off(LED6);
      }

      LIS3DSH_GetAccel( LIS3DSH_OUT_Z_H_REG, LIS3DSH_OUT_Z_L_REG , &accel);
      my_log(0,MODULE_MAIN,"Z= <%x> %d\r\n", accel, accel);
      */
  }


}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
