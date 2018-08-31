/**
 ******************************************************************************
 * @file    Project/STM32F0xx_StdPeriph_Templates/main.c
 * @author  MCD Application Team
 * @version V1.5.0
 * @date    05-December-2014
 * @brief   Main program body
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
#include "main.h"
#include "alarm.h"
#include "xprintf.h"
/** @addtogroup STM32F0xx_StdPeriph_Templates
 * @{
 */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/*
 #define APPLICATION_ADDRESS     (uint32_t)0x08002800
 Private macro -------------------------------------------------------------
 Private variables ---------------------------------------------------------
 #if   (defined ( __CC_ARM ))
 __IO uint32_t VectorTable[48] __attribute__((at(0x20000000)));
 #elif (defined (__ICCARM__))
 #pragma location = 0x20000000
 __no_init __IO uint32_t VectorTable[48];
 #elif defined   (  __GNUC__  )
 __IO uint32_t VectorTable[48] __attribute__((section(".RAMVectorTable")));
 #elif defined ( __TASKING__ )
 __IO uint32_t VectorTable[48] __at(0x20000000);
 #endif
 */

/* Private function prototypes -----------------------------------------------*/
static void RCC_Configuration(void);
static void GPIO_Configuration(void);
static void NVIC_Configuration(void);
volatile uint32_t ulSecCount = 0;
volatile uint32_t ulTickCount = 0;
volatile uint32_t ulMiliCount = 0;
volatile unsigned long ulTick100 = 0; //Tick Count from start to now, 100ms
/* Private functions ---------------------------------------------------------*/
static void prvSetupHardware(void) {
	RCC_Configuration();
	NVIC_Configuration();
	GPIO_Configuration();
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
}
/*******************************************************************************
 * Function Name  : USART1_Init
 * Description    : Initialize the IAP: Configure RCC, USART and GPIOs.
 * Input          : None
 * Output         : None
 * Return         : None
 * Note                   : You have to run RCC_Configuration() before calling this function
 *******************************************************************************/
void PC_USART_Init(int baudrate) {
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* Configure the USART1 */
	USART_Init(USART1, &USART_InitStructure);
	/* Enable USART1 interrupt */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	/* Enable the USART1 */
	USART_Cmd(USART1, ENABLE);
}
void USART2_Init(int baudrate) {
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* Configure the USART2 */
	USART_Init(USART2, &USART_InitStructure);
	/* Enable USART2 interrupt */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	/* Enable the USART2 */
	USART_Cmd(USART2, ENABLE);
}
void USART3_Init(int baudrate) {
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* Configure the USART3 */
	USART_Init(USART3, &USART_InitStructure);
	/* Enable USART3 interrupt */
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	/* Enable the USART3 */
	USART_Cmd(USART3, ENABLE);
}
void USART4_Init(int baudrate) {
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* Configure the USART4 */
	USART_Init(USART4, &USART_InitStructure);
	/* Enable USART4 interrupt */
	USART_ITConfig(USART4, USART_IT_RXNE, ENABLE);
	/* Enable the USART4 */
	USART_Cmd(USART4, ENABLE);
}
void USART5_Init(int baudrate) {
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* Configure the USART5 */
	USART_Init(USART5, &USART_InitStructure);
	/* Enable USART5 interrupt */
	USART_ITConfig(USART5, USART_IT_RXNE, ENABLE);
	/* Enable the USART5 */
	USART_Cmd(USART5, ENABLE);
}
void USART6_Init(int baudrate) {
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* Configure the USART6 */
	USART_Init(USART6, &USART_InitStructure);
	/* Enable USART6 interrupt */
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
	/* Enable the USART6 */
	USART_Cmd(USART6, ENABLE);
}
void USART7_Init(int baudrate) {
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* Configure the USART7 */
	USART_Init(USART7, &USART_InitStructure);
	/* Enable USART7 interrupt */
	USART_ITConfig(USART7, USART_IT_RXNE, ENABLE);
	/* Enable the USART7 */
	USART_Cmd(USART7, ENABLE);
}
void USART8_Init(int baudrate) {
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* Configure the USART8 */
	USART_Init(USART8, &USART_InitStructure);
	/* Enable USART8 interrupt */
	USART_ITConfig(USART8, USART_IT_RXNE, ENABLE);
	/* Enable the USART8 */
	USART_Cmd(USART8, ENABLE);
}
long check_time = 0;
int main(void) {
	/*
	 uint32_t i = 0;
	 for (i = 0; i < 48; i++) {
	 VectorTable[i] = *(__IO uint32_t*) (APPLICATION_ADDRESS + (i << 2));
	 }

	 Enable the SYSCFG peripheral clock
	 RCC_APB2PeriphResetCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	 Remap SRAM at 0x00000000
	 SYSCFG_MemoryRemapConfig(SYSCFG_MemoryRemap_SRAM);
	 */
	//SystemInit();
	prvSetupHardware();
	PC_USART_Init(115200);
	SysTick_Config(SystemCoreClock / 1000);
	xdev_out(SerialPutChar);
	xprintf("cam hub demo\r\n");
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);
	while (1) {
		if (check_time < ulMiliCount) {
			GPIO_WriteBit(GPIOB, GPIO_Pin_8,
					!GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_8));
			check_time = ulMiliCount + 100;
		}
	}
	//Main_Menu();
}
void RCC_Configuration(void) {
	/* Function used to set the RCC clock configuration to the default reset state */
	RCC_DeInit();
	/* Peripheral clocks configuration functions **********************************/
	RCC_AHBPeriphClockCmd(
			RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC
					| RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOE
					| RCC_AHBPeriph_GPIOF, ENABLE);
	RCC_APB2PeriphClockCmd(
			RCC_APB2Periph_USART1 | RCC_APB2Periph_USART6
					| RCC_APB2Periph_USART7 | RCC_APB2Periph_USART8, ENABLE);
	RCC_APB1PeriphClockCmd(
			RCC_APB1Periph_USART2 | RCC_APB1Periph_USART3
					| RCC_APB1Periph_USART4 | RCC_APB1Periph_USART5, ENABLE);
}
void NVIC_Configuration(void) {
	NVIC_InitTypeDef NVIC_InitStructure;
	/*uart2
	 */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	/*uart1
	 */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}
void GPIO_Configuration(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	/*portA initialization
	 * GPIO_Pin_0	:UART4 TX
	 * GPIO_Pin_1	:UART4 RX
	 * GPIO_Pin_2	:UART2 TX
	 * GPIO_Pin_3	:UART2 RX
	 * GPIO_Pin_4	:UART6 TX
	 * GPIO_Pin_5	:UART6 TX
	 */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_4);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_4);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_5);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2
			| GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*portB initialization
	 * GPIO_Pin_3	:UART5 TX
	 * GPIO_Pin_4	:UART5 RX
	 * GPIO_Pin_6	:UART1 TX
	 * GPIO_Pin_7	:UART1 RX
	 * GPIO_Pin_10	:UART3 TX
	 * GPIO_Pin_11	:UART3 TX
	 */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_4);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_4);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_4);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_4);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6
			| GPIO_Pin_7 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*portC initialization
	 * GPIO_Pin_0	:UART7 TX
	 * GPIO_Pin_1	:UART7 RX
	 * GPIO_Pin_2	:UART8 TX
	 * GPIO_Pin_3	:UART8 TX
	 */
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource0, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource1, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource2, GPIO_AF_2);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource3, GPIO_AF_2);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2
			| GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/*led
	 * PB8: LED GREEN
	 * PB9: LED RED
	 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
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
