/**
 ******************************************************************************
 * @file    Project/STM32F0xx_StdPeriph_Templates/stm32f0xx_it.c
 * @author  MCD Application Team
 * @version V1.5.0
 * @date    05-December-2014
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and
 *          peripherals interrupt service routine.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "stm32f0xx_it.h"
#include "main.h"
#include "xprintf.h"
#include "string.h"
/** @addtogroup Template_Project
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile extern uint32_t ulSecCount;
volatile extern uint32_t ulTickCount;
volatile extern uint32_t ulMiliCount;
volatile extern unsigned long ulTick100;
extern void USARTxPutChar(USART_TypeDef * USARTx, uint8_t c);
extern void USARTxPutString(USART_TypeDef * USARTx, unsigned char *s);
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void) {
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void) {
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1) {
	}
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void) {
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void) {
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void) {
	ulTickCount++;
	ulMiliCount++;

	if ((ulMiliCount % 10) == 0) {
		ulTick100++;
	}

	if (ulMiliCount >= 100) {
		ulSecCount++;
	//	ulMiliCount = 0;
	}
}
char buff_cmd[256];
int buff_cmd_idx = 0;
char buff_data[1024];
int buff_data_idx = 0;
int Camera_idx = 0;
int On_handler_cmd_from_deveice = 0;
int last_time_rec_byte_time = 0;
void USART1_IRQHandler(void) {
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
		uint16_t cChar;
		//last_time_rec_byte_time = ulMiliCount;
		cChar = USART_ReceiveData(USART1);
		if (cChar == 0x56 || buff_data_idx == 0) {
			buff_cmd_idx = 0;
			memset(buff_cmd, 0, sizeof(buff_cmd));
		}
		if (buff_cmd_idx == 1) {
			if (cChar) {
				Camera_idx = cChar;
				switch (Camera_idx) {
				case 1:
					USARTxPutChar(USART2, 0x56);
					USARTxPutChar(USART2, Camera_idx);
					break;
				case 2:
					USARTxPutChar(USART3, 0x56);
					USARTxPutChar(USART3, Camera_idx);
					break;
				case 3:
					USARTxPutChar(USART4, 0x56);
					USARTxPutChar(USART4, Camera_idx);
					break;
				case 4:
					USARTxPutChar(USART5, 0x56);
					USARTxPutChar(USART5, Camera_idx);
					break;
				case 5:
					USARTxPutChar(USART6, 0x56);
					USARTxPutChar(USART6, Camera_idx);
					break;
				case 6:
					USARTxPutChar(USART7, 0x56);
					USARTxPutChar(USART7, Camera_idx);
					break;
				default:
					break;
				}
			}
		}
		if (buff_cmd_idx > 1) {
			switch (Camera_idx) {
			case 1:
				USARTxPutChar(USART2, cChar);
				break;
			case 2:
				USARTxPutChar(USART3, cChar);
				break;
			case 3:
				USARTxPutChar(USART4, cChar);
				break;
			case 4:
				USARTxPutChar(USART5, cChar);
				break;
			case 5:
				USARTxPutChar(USART6, cChar);
				break;
			case 6:
				USARTxPutChar(USART7, cChar);
				break;
			default:
				break;
			}
			buff_cmd[buff_cmd_idx] = cChar;
			buff_cmd_idx++;
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);

		}
	}
}
void USART2_IRQHandler(void) {
	uint16_t cChar;
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET) {
		cChar = USART_ReceiveData(USART2);
		if (cChar == 0x76) {
			buff_cmd_idx = 0;
			buff_data_idx = 0;
			memset(buff_data, 0, sizeof(buff_data));
		}
		if (buff_data_idx == 1) {
			USARTxPutChar(USART2, 0x76);
			USARTxPutChar(USART2, Camera_idx);
		}
		if (buff_data_idx > 1) {
			USARTxPutChar(USART2, cChar);
		}
		buff_data[buff_data_idx] = cChar;
		buff_data_idx++;
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
}
void USART3_8_IRQHandler(void) {
	uint16_t cChar;
	if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET) {
		cChar = USART_ReceiveData(USART3);

		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
	}
	if (USART_GetITStatus(USART4, USART_IT_RXNE) == SET) {
		cChar = USART_ReceiveData(USART4);

		USART_ClearITPendingBit(USART4, USART_IT_RXNE);
	}
	if (USART_GetITStatus(USART5, USART_IT_RXNE) == SET) {
		cChar = USART_ReceiveData(USART5);

		USART_ClearITPendingBit(USART5, USART_IT_RXNE);
	}
	if (USART_GetITStatus(USART6, USART_IT_RXNE) == SET) {
		cChar = USART_ReceiveData(USART6);

		USART_ClearITPendingBit(USART6, USART_IT_RXNE);
	}
	if (USART_GetITStatus(USART7, USART_IT_RXNE) == SET) {
		cChar = USART_ReceiveData(USART7);

		USART_ClearITPendingBit(USART7, USART_IT_RXNE);
	}
	if (USART_GetITStatus(USART8, USART_IT_RXNE) == SET) {
		cChar = USART_ReceiveData(USART8);

		USART_ClearITPendingBit(USART8, USART_IT_RXNE);
	}
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
 * @brief  This function handles PPP interrupt request.
 * @param  None
 * @retval None
 */
/*void PPP_IRQHandler(void)
 {
 }*/

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
