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
#include "i2c.h"
#include "cs43l12.h"
#include "my_event.h"
#include "my_queue.h"
#include "sm.h"
  
#include "FreeRTOS.h"
#include "task.h"
#include "string.h"

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




void vAccelTask( void *pvParameters )
{
  portTickType xLastWakeTime;
  const portTickType xFrequency = 50;
  xLastWakeTime = xTaskGetTickCount();

  e_imu_direction prev_dir = EVT_DIRECTION_CENTER;

#define THR 2000
  
  while(1)
  {

    e_imu_direction cur_dir = EVT_DIRECTION_CENTER;

      int16_t accel = 0;
      LIS3DSH_GetAccel( LIS3DSH_OUT_X_H_REG , LIS3DSH_OUT_X_L_REG , &accel);
      if(accel>THR) {
        cur_dir = EVT_DIRECTION_LEFT;
        BSP_LED_On(LED5);
        BSP_LED_Off(LED4);
      }
      else if(accel<-THR){
        cur_dir = EVT_DIRECTION_RIGHT;
        BSP_LED_On(LED4);
        BSP_LED_Off(LED5);
      }
      else {
        BSP_LED_Off(LED4);
        BSP_LED_Off(LED5);
      }

      //my_log(0,MODULE_MAIN,"X= <%x> %d\r\n", accel, accel);
      LIS3DSH_GetAccel( LIS3DSH_OUT_Y_H_REG , LIS3DSH_OUT_Y_L_REG , &accel);
      //my_log(0,MODULE_MAIN,"Y= <%x> %d\r\n", accel, accel);
      if(accel>THR) {
        cur_dir = EVT_DIRECTION_FRONT;
        BSP_LED_On(LED3);
        BSP_LED_Off(LED6);
      }
      else if(accel<-THR){
        cur_dir = EVT_DIRECTION_BACK;
        BSP_LED_On(LED6);
        BSP_LED_Off(LED3);
      }
      else {
        BSP_LED_Off(LED3);
        BSP_LED_Off(LED6);
      }

      LIS3DSH_GetAccel( LIS3DSH_OUT_Z_H_REG, LIS3DSH_OUT_Z_L_REG , &accel);
      //my_log(0,MODULE_MAIN,"Z= <%x> %d\r\n", accel, accel);
      
      if ( cur_dir != prev_dir) {
        t_event *evt = NULL;
        evt = pvPortMalloc(sizeof(t_event));

        e_imu_direction *ctx = NULL; 
        ctx = pvPortMalloc(sizeof(e_imu_direction));
        *ctx = cur_dir;

        evt->type = EVT_TYPE_ACCEL_DATA;
        evt->ctx = ctx;

        //my_log(0,MODULE_MAIN,"Queuing @%x\r\n", evt);
        my_queue_add(evt);
      }

      prev_dir = cur_dir;
      vTaskDelay(xFrequency/portTICK_PERIOD_MS);
  }
}

void vInitTask( void *pvParameters )
{

  USART2_UART_Init();
  my_log(0,MODULE_MAIN,"UART initialized successfully\r\n");


  my_log(0,MODULE_MAIN,"I2C init\r\n");

  I2C_Init();


  my_log(0,MODULE_MAIN,"SPI init\r\n");
  SPI_Init();

  Button_Init();

  LIS3DSH_Whoami();
  LIS3DSH_Init();
  LIS3DSH_Read_REG4();

  I2S3_Init();
  CS43L12_Init();


  CS43L12_ReadId();

  CS43L12_ReadError();
  CS43L12_ReadMasterVolume();

  CS43L12_ReadPower();

  my_log(0,MODULE_MAIN,"Starting tasks\r\n");

  CS43L12_BeepContinuous();
}


void vLEDFlashTask( void *pvParameters )
{
  portTickType xLastWakeTime;
  const portTickType xFrequency = 200;
  xLastWakeTime=xTaskGetTickCount();
    for( ;; )
    {
      BSP_LED_Toggle(LED5);
      vTaskDelay(xFrequency/portTICK_PERIOD_MS);
    }
}



void vSmTask( void *pvParameters )
{
  sm_run();
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

  SystemInit();

  #define mainLED_TASK_PRIORITY           ( tskIDLE_PRIORITY )

  my_queue_init();
  sm_init();

  xTaskCreate( vInitTask, ( signed char * ) "INIT", configMINIMAL_STACK_SIZE, NULL, mainLED_TASK_PRIORITY, NULL );
  xTaskCreate( vLEDFlashTask, ( signed char * ) "LED", configMINIMAL_STACK_SIZE, NULL, mainLED_TASK_PRIORITY, NULL );
  xTaskCreate( vAccelTask, ( signed char * ) "ACCEL", configMINIMAL_STACK_SIZE, NULL, mainLED_TASK_PRIORITY, NULL );
  xTaskCreate( vSmTask, ( signed char * ) "SM", configMINIMAL_STACK_SIZE, NULL, mainLED_TASK_PRIORITY, NULL );
  vTaskStartScheduler ( ) ;

  while(1);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
