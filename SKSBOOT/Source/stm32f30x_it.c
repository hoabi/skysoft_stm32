/**
 ******************************************************************************
 * @file    stm32f30x_it.c
 * @author  MCD Application Team
 * @version V1.2.2
 * @date    14-August-2015
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and
 *          peripherals interrupt service routine.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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
#include "stm32f30x_it.h"
#include "main.h"
volatile extern uint32_t ulSecCount;
volatile extern uint32_t ulTickCount;
volatile extern uint32_t ulMiliCount;
/** @addtogroup IAP
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
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
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void) {
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1) {
	}
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void) {
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1) {
	}
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void) {
	/* Go to infinite loop when Usage Fault exception occurs */
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
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void) {
}

/**
 * @brief  This function handles PendSV_Handler exception.
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
extern int blink;
unsigned long count = 0;
void SysTick_Handler(void) {
	ulTickCount++;
	ulMiliCount++;
	int blk = 0;
	if (ulTickCount == 20) {
		//GPIO_ResetBits(GPIOBuzz, GPIO_BUZZ_PIN);
		BuzzOff();
	}
	if ((ulTickCount % 10) == 0) {
#ifdef GPIO_WATCHDOG_PORT
		GPIO_WriteBit(GPIO_WATCHDOG_PORT, GPIO_WATCHDOG_PIN,
				(BitAction) (Bit_SET));
		GPIO_WriteBit(GPIO_WATCHDOG_PORT, GPIO_WATCHDOG_PIN,
				(BitAction) (Bit_RESET));
#endif
	}
	if (ulMiliCount >= 100) {
		ulSecCount++;
		ulMiliCount = 0;
	}

	if (blink == 1) {
		if (((ulTickCount % 100) == 0)) {
			blk = 1;
		}
	} else if (blink == 2) {
		if (((ulTickCount % 10) == 0)) {
			blk = 1;
		}
	}

	if (blk) {
		if (count % 2) {
#ifdef GPIO_GSM_LED_PORT
			GPIO_SetBits(GPIO_GSM_LED_PORT, GPIO_GSM_LED_PIN);
#endif
#ifdef GPIO_GPS_LED_PORT
			GPIO_ResetBits(GPIO_GPS_LED_PORT, GPIO_GPS_LED_PIN);
#endif
		} else {
#ifdef GPIO_GSM_LED_PORT
			GPIO_ResetBits(GPIO_GSM_LED_PORT, GPIO_GSM_LED_PIN);
#endif
#ifdef GPIO_GPS_LED_PORT
			GPIO_SetBits(GPIO_GPS_LED_PORT, GPIO_GPS_LED_PIN);
#endif
		}
		count++;
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

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
