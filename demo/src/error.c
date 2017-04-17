#include "main.h"
#include "console.h"

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  BSP_LED_On(LED3);
  BSP_LED_On(LED4);
  BSP_LED_On(LED5);
  BSP_LED_On(LED6);
  while(1)
  {
  }
}
