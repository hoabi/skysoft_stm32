/**
 ******************************************************************************
 * @file    IAP/src/main.c
 * @author  MCD Application Team
 * @version V3.3.0
 * @date    10/15/2010
 * @brief   Main program body
 ******************************************************************************
 * @copy
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
 */

/** @addtogroup IAP
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "main.h"
#include "xprintf.h"

//#define SKS_DEBUG
#define VECTOR_TABLE_OFFSET				0x0000

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//extern pFunction Jump_To_Application;
//extern uint32_t JumpAddress;
/* Private function prototypes -----------------------------------------------*/
static void IAP_Init(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */

/* Private function prototypes -----------------------------------------------*/
static void NVIC_Configuration(void);
static void RCC_Configuration(void);
volatile uint32_t ulSecCount = 0;
volatile uint32_t ulTickCount = 0;
volatile uint32_t ulMiliCount = 0;
extern char address[20];
#if 0
static void prvSetupHardware( void )
{

	RCC_Configuration();
	NVIC_Configuration();
	FLASH_Unlock();
	/* Configure HCLK clock as SysTick clock source. */
	//SysTick_CLKSourceConfig( SysTick_CLKSource_HCLK );
	SysTick_CLKSourceConfig( SysTick_CLKSource_HCLK );
	//SysTick_Config(SystemCoreClock / 1000);
	// Task hardware initialization.
	//LedHardwareInit();
	//FatHardwareInit();
}
#endif
//extern volatile unsigned long u1_count;
int main(void) {
	SystemInit();
	xdev_out(SerialPutChar);
	//prvSetupHardware();
	NVIC_Configuration();
	strcat(address, "hot.v");
	//SerialPutString("\r\nLOADING... \r\n\r\n");
	SysTick_Config(SystemCoreClock / 100);
	//LedHardwareInit();
	/* Flash unlock */
	FLASH_Unlock();
	/* Enable CRC clock */

	//LedHardwareInit();
	/* Initialize Key Button mounted on STM3210X-EVAL board */
	//STM_EVAL_PBInit(BUTTON_KEY, BUTTON_MODE_GPIO);
	/* Test if Key push-button on STM3210X-EVAL Board is pressed */
	//if (STM_EVAL_PBGetState(BUTTON_KEY)  == 0x00)
	/* If Key is pressed */
	/* Execute the IAP driver in order to re-program the Flash */

	IAP_Init();
#ifdef PUBLIC_VERSION
	xprintf("\r\nLoading PV ");
#else
	xprintf("\r\nLoading ");
#endif
	strcat(address, "iet");
	xprintf("... \r\n\r\n");
#if 0
	unsigned long lastTick = ulTickCount;
	while(1)
	{
		if ((ulTickCount - lastTick)>100)
		{
			SerialPutString("\r\nLOADING... \r\n\r\n");
			lastTick = ulTickCount;
		}
	}
#endif
	Main_Menu();
	while (1) {
	}
}

#ifdef USE_FULL_ASSERT
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

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/

/* Rcc functions ---------------------------------------------------------*/

/*******************************************************************************
 * Function Name  : RCC_Configuration
 * Description    : Configures the different system clocks.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void RCC_Configuration(void) {
	ErrorStatus HSEStartUpStatus;

	/* Reset the RCC clock configuration to default reset state */
	RCC_DeInit();

	/* Configure the High Speed External oscillator */
	RCC_HSEConfig(RCC_HSE_ON);

	/* Wait for HSE start-up */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if (HSEStartUpStatus == SUCCESS) {
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(ENABLE);

		/* Set the code latency value: FLASH Two Latency cycles */
		FLASH_SetLatency(FLASH_Latency_2);

		/* Configure the AHB clock(HCLK): HCLK = SYSCLK */
		RCC_HCLKConfig(RCC_SYSCLK_Div1);

		/* Configure the High Speed APB2 clcok(PCLK2): PCLK2 = HCLK */
		RCC_PCLK2Config(RCC_HCLK_Div1);

		/* Configure the Low Speed APB1 clock(PCLK1): PCLK1 = HCLK/2 */
		RCC_PCLK1Config(RCC_HCLK_Div2);

		/* Configure the PLL clock source and multiplication factor     */
		/* PLLCLK = HSE*PLLMul = 8*9 = 72MHz */
		RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);

		/* Enable PLL   */
		RCC_PLLCmd(ENABLE);

		/* Check whether the specified RCC flag is set or not */
		/* Wait till PLL is ready       */
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
			;

		/* Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		/* Get System Clock Source */
		/* Wait till PLL is used as system clock source */
		while (RCC_GetSYSCLKSource() != 0x08)
			;

	}

	/* Enable GPIOA, GPIOC and USART1 clock  */
	/*RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA   \
						  | RCC_APB2Periph_GPIOB    \
						  | RCC_APB2Periph_GPIOC    \
						  | RCC_APB2Periph_GPIOD    \
						  | RCC_APB2Periph_GPIOE    \
						  | RCC_APB2Periph_GPIOF    \
						  | RCC_APB2Periph_AFIO  \
						  | RCC_APB2Periph_TIM1     \
						  | RCC_APB2Periph_ADC1     \
						  | RCC_APB2Periph_SPI1     \
						  | RCC_APB2Periph_USART1, ENABLE);
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE);
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);*/
	RCC_AHBPeriphClockCmd(
			RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC
					| RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOE
					| RCC_AHBPeriph_GPIOF, ENABLE);
	RCC_APB2PeriphClockCmd(
			RCC_APB2Periph_SYSCFG | RCC_APB2Periph_SPI1 | RCC_APB2Periph_USART1
					| RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB1PeriphClockCmd(
			RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4
					| RCC_APB1Periph_SPI2 | RCC_APB1Periph_USART2
					| RCC_APB1Periph_USART3, ENABLE);
}

/*******************************************************************************
 * Name          : NVIC_Configuration
 * Deion         : Configures NVIC and Vector Table base location.
 * Input         : None
 * Output        : None
 * Return        : None
 *******************************************************************************/
void NVIC_Configuration(void) {
#if 1
	/* Set the Vector Table base address at 0x08000000 */
	/* Set the Vector Table base address at 0x08080000 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, VECTOR_TABLE_OFFSET);
#ifndef SKS_DEBUG
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	//NVIC_PriorityGroupConfig( NVIC_PriorityGroup_0 );
#else

	//NVIC_InitTypeDef NVIC_InitStructure;
	/* Configure the NVIC Preemption Priority Bits */
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;

#if 0
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the UART3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the UART4 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the UART4 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the TIM2 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
#endif
#endif
#else
	NVIC_InitTypeDef NVIC_InitStructure;

#ifdef  VECT_TAB_RAM
	/* Set the Vector Table base location at 0x20000000 */
	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH  */
	/* Set the Vector Table base location at 0x08000000 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif

	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQChannel;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the USART3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQChannel;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the UART4 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQChannel;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the UART5 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQChannel;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQChannel;
	NVIC_Init(&NVIC_InitStructure);
#endif
}
