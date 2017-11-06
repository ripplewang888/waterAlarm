/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
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
#include "common.h"


#if MAIN_DEBUG
      #define MAIN_DBG(format,...)   printf("[MAIN DEBUG] %s:%d %s:: "format"\r\n",  __FILE__, __LINE__, __FUNCTION__,##__VA_ARGS__)
#else
     #define MAIN_DBG(format,...)   
#endif


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

void user_Init()
{
    uint8_t cmdRecv[BUF_LEN];

    /*BC95  module init, send AT command*/
    memset(cmdRecv, 0, sizeof(cmdRecv));
    if(RT_SUCCESS != send_AT_to_bc95(AT_CFUN_FULL, AT_TRY_TIMES, cmdRecv)){
        MAIN_DBG("BC95 module AT CFun enable failed. please check BC95 module.");
        return;
    }


    memset(cmdRecv, 0, sizeof(cmdRecv));
    if(RT_SUCCESS != send_AT_to_bc95(AT_SETBAND_5, AT_TRY_TIMES, cmdRecv)){
        MAIN_DBG("BC95 module AT set band failed. please check BC95 module");
        return;
    }

    memset(cmdRecv, 0, sizeof(cmdRecv));
    if(RT_SUCCESS != send_AT_to_bc95(AT_SET_FREQUENCY, AT_TRY_TIMES, cmdRecv)){
        MAIN_DBG("BC95 module AT set frequency failed. please check BC95 module");
        return;
    }

    memset(cmdRecv, 0, sizeof(cmdRecv));
    if(RT_SUCCESS != send_AT_to_bc95(AT_SET_PLMM, AT_TRY_TIMES, cmdRecv)){
        MAIN_DBG("BC95 module AT set PLMM failed. please check BC95 module");
        return;
    }

    //AT+NUESTATS check 
    memset(cmdRecv, 0, sizeof(cmdRecv));
    if(RT_SUCCESS != send_AT_to_bc95(AT_GET_NEU_STATUS, AT_TRY_TIMES, cmdRecv)){
        MAIN_DBG("BC95 module AT get NEU Status failed. please check BC95 module");
        return;
    }

    //attach
    memset(cmdRecv, 0, sizeof(cmdRecv));
    if(RT_SUCCESS != send_AT_to_bc95(AT_SET_ATTACH, AT_TRY_TIMES, cmdRecv)){
        MAIN_DBG("BC95 module AT set attach failed. please check BC95 module");
        return;
    }

    //get attach
    memset(cmdRecv, 0, sizeof(cmdRecv));
    if(RT_SUCCESS != send_AT_to_bc95(AT_GET_ATTACH, AT_TRY_TIMES, cmdRecv)){
        MAIN_DBG("BC95 module AT get attach failed. please check BC95 module");
        return;
    }

    //create socket
    memset(cmdRecv, 0, sizeof(cmdRecv));
    if(RT_SUCCESS != send_AT_to_bc95(AT_SOCKET_CREATE, AT_TRY_TIMES, cmdRecv)){
        MAIN_DBG("BC95 module AT create socket failed. please check BC95 module");
        return;
    }
    
}

 


int main(void)
{
  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();


  /* Configure the system clock */
  SystemClock_Config();



  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();

  /*uart2 start to receive*/
  uart2_mcu_BC95_StartRecv();

  /*wait for BC95 init success, then init BC95 module*/
  HAL_Delay(10000);
  user_Init();

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  { 
        printf("%d\n",waterAlarm_status());
        HAL_Delay(2000);
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
