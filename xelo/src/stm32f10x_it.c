/**
 ******************************************************************************
 * @file    GPIO/IOToggle/stm32f10x_it.c
 * @author  MCD Application Team
 * @version V3.6.0
 * @date    24-April-2012
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and peripherals
 *          interrupt service routine.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
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
#include "stm32f10x_it.h"
#include <string.h>
#include "xprintf.h"
#include "IRsensor.h"
/** @addtogroup STM32F10x_StdPeriph_Examples
 * @{
 */

/** @addtogroup GPIO_IOToggle
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint32_t MiliCount;
volatile uint32_t timer_count;
volatile uint32_t check1, check2, check3, check4;
uint32_t CLK_count = 0;
uint32_t old_CLK_count = 0;
int PPS = 0;
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

void SysTick_Handler(void) {
	MiliCount++;
	if (MiliCount % 1000 == 0) {
		PPS = CLK_count - old_CLK_count;
		old_CLK_count = CLK_count;
	}

	if (GPIO_ReadInputDataBit(IR_Rx1_port, IR_Rx1_pin) == 0) {
		LED1_on;
		check1 = 0;
	}
	if (GPIO_ReadInputDataBit(IR_Rx1_port, IR_Rx1_pin) == 1) {
		check1++;
		if (check1 >= 250) {
			LED1_off;
		}
	}
	if (GPIO_ReadInputDataBit(IR_Rx2_port, IR_Rx2_pin) == 0) {
		LED2_on;
		check2 = 0;
	}
	if (GPIO_ReadInputDataBit(IR_Rx2_port, IR_Rx2_pin) == 1) {
		check2++;
		if (check2 >= 250) {
			LED2_off;
		}
	}
	if (GPIO_ReadInputDataBit(IR_Rx3_port, IR_Rx3_pin) == 0) {
		LED3_on;
		check3 = 0;
	}
	if (GPIO_ReadInputDataBit(IR_Rx3_port, IR_Rx3_pin) == 1) {
		check3++;
		if (check3 >= 250) {
			LED3_off;
		}
	}
	if (GPIO_ReadInputDataBit(IR_Rx4_port, IR_Rx4_pin) == 0) {
		LED4_on;
		check4 = 0;
	}
	if (GPIO_ReadInputDataBit(IR_Rx4_port, IR_Rx4_pin) == 1) {
		check4++;
		if (check4 >= 250) {
			LED4_off;
		}
	}
	if ((check1 >= 2000) | (check2 >= 2000) | (check3 >= 2000)
			| (check4 >= 2000)) {
	} else {

	}
}
void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		timer_count++;
		if (timer_count <= 64) {
			GPIO_WriteBit(IR_Tx1_port, IR_Tx1_pin,
					!GPIO_ReadOutputDataBit(IR_Tx1_port, IR_Tx1_pin));
			GPIO_WriteBit(IR_Tx2_port, IR_Tx2_pin,
					!GPIO_ReadOutputDataBit(IR_Tx2_port, IR_Tx2_pin));
			GPIO_WriteBit(IR_Tx3_port, IR_Tx3_pin,
					!GPIO_ReadOutputDataBit(IR_Tx3_port, IR_Tx3_pin));
			GPIO_WriteBit(IR_Tx4_port, IR_Tx4_pin,
					!GPIO_ReadOutputDataBit(IR_Tx4_port, IR_Tx4_pin));
		} else {
			(GPIO_SetBits(IR_Tx1_port, IR_Tx1_pin));
			(GPIO_SetBits(IR_Tx2_port, IR_Tx2_pin));
			(GPIO_SetBits(IR_Tx3_port, IR_Tx3_pin));
			(GPIO_SetBits(IR_Tx4_port, IR_Tx4_pin));

		}
		if (timer_count >= 6464) {
			timer_count = 0;
		}
	}
}
extern char buff_cmd[256];
char buff_cmd_tmp[256];
int buff_idx = 0;
void USART1_IRQHandler(void) {
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
		char cChar;
		cChar = USART_ReceiveData(USART1);
		//xprintf("%c", cChar);
		if (buff_idx > 255 || cChar == '*') {
			buff_idx = 0;
		}
		if (cChar == '#') {
			buff_cmd_tmp[buff_idx] = cChar;
			buff_idx++;
			//copy
			memcpy(buff_cmd, buff_cmd_tmp, buff_idx);
			buff_idx = 0;
		} else {
			buff_cmd_tmp[buff_idx] = cChar;
			buff_idx++;
		}

		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
extern char BLE_buff[256];
char BLE_buff_temp[256] = { 0 };
int BLE_buff_idx = 0;
void UART4_IRQHandler(void) {
	if (USART_GetITStatus(UART4, USART_IT_RXNE) == SET) {
		char cChar;
		cChar = USART_ReceiveData(UART4);
		xprintf("%c\r\n", cChar);
		if (BLE_buff_idx > 255 || cChar == '*') {
			BLE_buff_idx = 0;
		}
		if (cChar == '#') {
			BLE_buff_temp[BLE_buff_idx] = cChar;
			BLE_buff_idx++;
			//copy
			memcpy(BLE_buff, BLE_buff_temp, BLE_buff_idx);
			memset(BLE_buff_temp, 0, sizeof(BLE_buff_temp));
			BLE_buff_idx = 0;
		} else {
			BLE_buff_temp[BLE_buff_idx] = cChar;
			//xprintf("%c,%d", BLE_buff_temp[BLE_buff_idx], BLE_buff_idx);
			BLE_buff_idx++;

		}
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
	}
}
void EXTI9_5_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line7) != RESET) {
		CLK_count++;
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
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

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
