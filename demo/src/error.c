#include "main.h"
#include "console.h"

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  printf("============== Error_Handler ==========\r\n" );
  /* Turn LED5 on */
  BSP_LED_On(LED3);
  BSP_LED_Off(LED4);
  BSP_LED_Off(LED5);
  BSP_LED_Off(LED6);
  while(1)
  {
  }
}
