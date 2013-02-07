#include "main.h"


void systick_init(void)
{
    if(SysTick_Config(SystemCoreClock / 1000))
    {
        while(1);
    }
}


int main(void)
{
    systick_init();
    eep_init();         //读取EEPROM内的数据
    lcd_init();
    key_init();
    io_init();
    pwm_init();
    ntc_init();
    
    while (1)
    {
        if (time_1ms_flag == 1)
        {
            //1ms进入一次
            time_1ms_flag = 0;

        }

        if(time_10ms_flag == 1)
        {
            //10ms进入一次
            time_10ms_flag = 0;

            key_scan();
        }

        if(time_100ms_flag == 1)
        {
            //100ms进入一次
            time_100ms_flag = 0;

            key_done();
        }

        if(time_1s_flag == 1)
        {
            //1s执行一次
            time_1s_flag = 0;

        }
    }
}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
