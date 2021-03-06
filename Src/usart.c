/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
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
#include "usart.h"

#include "gpio.h"
#include "ringBuffer.h"

/* USER CODE BEGIN 0 */
__IO ITStatus UartRxComplete = RESET;
__IO ITStatus UartTxReady = RESET;

__IO ITStatus LPUartRxComplete = RESET;
__IO ITStatus LPUTxReady = RESET;

static uint8_t  g_uart2_recvChar;
ringBufTypeDef   g_ringBufStruct;
static unsigned char  g_rxbuf[BUF_LEN];        

/* USER CODE END 0 */

UART_HandleTypeDef hlpuart1;
UART_HandleTypeDef huart2;

/* LPUART1 init function */

void MX_LPUART1_UART_Init(void)
{

  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 9600;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(uartHandle->Instance==LPUART1)
  {
  /* USER CODE BEGIN LPUART1_MspInit 0 */

  /* USER CODE END LPUART1_MspInit 0 */
    /* LPUART1 clock enable */
    __HAL_RCC_LPUART1_CLK_ENABLE();
  
    /**LPUART1 GPIO Configuration    
    PA13     ------> LPUART1_RX
    PA14     ------> LPUART1_TX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF6_LPUART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* LPUART1 interrupt Init */
    HAL_NVIC_SetPriority(AES_RNG_LPUART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(AES_RNG_LPUART1_IRQn);
  /* USER CODE BEGIN LPUART1_MspInit 1 */

  /* USER CODE END LPUART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = UART2_MCUTX_BC95RX_Pin|UART2_MCURX_BC95TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==LPUART1)
  {
  /* USER CODE BEGIN LPUART1_MspDeInit 0 */

  /* USER CODE END LPUART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LPUART1_CLK_DISABLE();
  
    /**LPUART1 GPIO Configuration    
    PA13     ------> LPUART1_RX
    PA14     ------> LPUART1_TX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_13|GPIO_PIN_14);

    /* LPUART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(AES_RNG_LPUART1_IRQn);
  /* USER CODE BEGIN LPUART1_MspDeInit 1 */

  /* USER CODE END LPUART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOA, UART2_MCUTX_BC95RX_Pin|UART2_MCURX_BC95TX_Pin);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */


void uart2_mcu_BC95_StartRecv(void){

    /*create ring buffer for  uart2*/
    ring_buf_create(&g_ringBufStruct, g_rxbuf, BUF_LEN);

    HAL_UART_Receive_IT(&huart2, (unsigned char *)&g_uart2_recvChar, 1);
}

/*
@breif:  uart read data from ringBuffer
@param:   
             readBuff:   read data output.
   return value:
              the length of read data.
*/
uint32_t uart2_mcu_BC95_Receive(uint8_t *readBuff)
{
    return ring_buf_get(&g_ringBufStruct, readBuff, BUF_LEN);
}




void uart2_mcu_BC95_SendMsg(uint8_t* sendBuff, size_t size)
{
  /*This while is optional*/
  while (UartTxReady == SET){} 
  
  if(HAL_UART_Transmit_IT(&huart2, sendBuff, size)!= HAL_OK)
  {
    ERR_HANDLER_ASSERT("failed!!!\r\n");
  }
  while (UartTxReady != SET){}
  
  UartTxReady = RESET;  
}


void HAL_USART2_TxCpltCallback()
{
    UartTxReady = SET;
}

void HAL_LPUUART1_TxCpltCallback()
{
    LPUTxReady = SET;
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  //  HAL_UART4_TxCpltCallback(UartHandle);
  /* Set transmission flag: transfer complete */
  switch((unsigned int)UartHandle->Instance)
  {
    case (unsigned int)USART2:
      HAL_USART2_TxCpltCallback(UartHandle);
      break;
     
    case (unsigned int)LPUART1:
      HAL_LPUUART1_TxCpltCallback(UartHandle);
      break;    
    default:
      break;
  }
    
}

void HAL_USART2_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    ring_buf_put(&g_ringBufStruct, (unsigned char *)&g_uart2_recvChar, 1);
    g_uart2_recvChar=0;
    UartRxComplete = SET;

    /*ripple, call back receive, so , do not need to receive in Loop*/
    HAL_UART_Receive_IT(UartHandle, (unsigned char  *)&g_uart2_recvChar, 1);
    UartRxComplete = RESET;

}

void HAL_LPUART1_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    LPUartRxComplete = SET;

}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
   // HAL_UART4_RxCpltCallback(UartHandle);
  /* Set transmission flag: transfer complete */
  switch((unsigned int)UartHandle->Instance)
  {
    case (unsigned int)USART2:
      HAL_USART2_RxCpltCallback(UartHandle);
      break;
    
    case (unsigned int)LPUART1:
      HAL_LPUART1_RxCpltCallback(UartHandle);
      break;
    default:
      break;
  }
    
}





int fputc(int ch, FILE *f)
{
    while (LPUTxReady == SET){}
    HAL_UART_Transmit_IT(&hlpuart1, (uint8_t*)&ch, 1);
    // UartTxReady is wait for transmit done
    while (LPUTxReady != SET){}
    LPUTxReady = RESET;
    return (ch);
}


/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
