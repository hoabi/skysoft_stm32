/**
 ******************************************************************************
 * @file    IAP/src/common.c
 * @author  MCD Application Team
 * @version V3.3.0
 * @date    10/15/2010
 * @brief   This file provides all the common functions.
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
#include "stm32f30x_crc.h"
#include "stm32f30x_flash.h"
#include "main.h"
#include "xprintf.h"

/**
 * @brief Definition for COM port1, connected to USART1
 */

/**
 * @brief Definition for COM port2, connected to USART2
 */

#if (USE_USART==1)
#define USARTx 						  USART1
#define USARTx_CLK                    RCC_APB2Periph_USART1
#define USARTx_TX_PIN                 GPIO_Pin_9
#define USARTx_TX_GPIO_PORT           GPIOA
#define USARTx_TX_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define USARTx_TX_SOURCE              GPIO_PinSource9
#define USARTx_TX_AF                  GPIO_AF_7

#define USARTx_RX_PIN                 GPIO_Pin_10
#define USARTx_RX_GPIO_PORT           GPIOA
#define USARTx_RX_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define USARTx_RX_AF                  GPIO_AF_7
#define USARTx_RX_SOURCE              GPIO_PinSource10
#define USARTx_IRQn                   USART1_IRQn
#elif (USE_USART==2)
#define USARTx                        USART2
#define USARTx_CLK                    RCC_APB1Periph_USART2
#define USARTx_TX_PIN                 GPIO_Pin_2				//Pin A2
#define USARTx_TX_GPIO_PORT           GPIOA
#define USARTx_TX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define USARTx_RX_PIN                 GPIO_Pin_3				////Pin A3
#define USARTx_RX_GPIO_PORT           GPIOA
#define USARTx_RX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define USARTx_IRQn                   USART2_IRQn
#define USARTx_IRQHandler		    USART2_IRQHandler
#elif (USE_USART==3)
#define USARTx                        USART3
#define USARTx_CLK                    RCC_APB1Periph_USART3
#define USARTx_TX_PIN                 GPIO_Pin_10
#define USARTx_TX_GPIO_PORT           GPIOB					//Pin B10: Not use
#define USARTx_TX_GPIO_CLK            RCC_APB2Periph_GPIOB
#define USARTx_RX_PIN                 GPIO_Pin_10
#define USARTx_RX_GPIO_PORT           GPIOB					//Pin B10
#define USARTx_RX_GPIO_CLK            RCC_APB2Periph_GPIOB
#define USARTx_IRQn                   USART3_IRQn
#define USARTx_IRQHandler			USART3_IRQHandler
#elif (USE_USART==4)
#define USARTx                        UART4
#define USARTx_CLK                    RCC_APB1Periph_UART4
#define USARTx_TX_PIN                 GPIO_Pin_10
#define USARTx_TX_GPIO_PORT           GPIOC					//Pin C10
#define USARTx_TX_GPIO_CLK            RCC_APB2Periph_GPIOC
#define USARTx_RX_PIN                 GPIO_Pin_11
#define USARTx_RX_GPIO_PORT           GPIOC					//Pin C11
#define USARTx_RX_GPIO_CLK            RCC_APB2Periph_GPIOC
#define USARTx_IRQn                   UART4_IRQn
#define USARTx_IRQHandler		     UART4_IRQHandler
#elif (USE_USART==5)
#define USARTx                       UART5
#define USARTx_CLK                    RCC_APB1Periph_UART5
#define USARTx_TX_PIN                 GPIO_Pin_12
#define USARTx_TX_GPIO_PORT           GPIOC					//Pin C12
#define USARTx_TX_GPIO_CLK            RCC_APB2Periph_GPIOC
#define USARTx_RX_PIN                 GPIO_Pin_2
#define USARTx_RX_GPIO_PORT           GPIOD					//Pin D2
#define USARTx_RX_GPIO_CLK            RCC_APB2Periph_GPIOD
#define USARTx_IRQn                   UART5_IRQn
#define USARTx_IRQHandler		      UART5_IRQHandler
#else
#error "USART NOT DEFINED"
#endif
/**
 * @brief  Calculate the number of pages
 * @param  Size: The image size
 * @retval The number of pages
 */
uint32_t FLASH_PagesMask(__IO uint32_t Size) {
	uint32_t pagenumber = 0x0;
	uint32_t size = Size;

	if ((size % PAGE_SIZE) != 0) {
		pagenumber = (size / PAGE_SIZE) + 1;
	} else {
		pagenumber = size / PAGE_SIZE;
	}
	return pagenumber;

}

/**
 * @brief  Disable the write protection of desired pages
 * @param  None
 * @retval None
 */
void FLASH_DisableWriteProtectionPages(uint32_t UserMemoryMask) {
	uint32_t useroptionbyte = 0, WRPR = 0;
	uint16_t var1 = OB_IWDG_SW, var2 = OB_STOP_NoRST, var3 = OB_STDBY_NoRST;
	FLASH_Status status = FLASH_BUSY;

	WRPR = FLASH_GetWriteProtectionOptionByte();

	/* Test if user memory is write protected */
	if ((WRPR & UserMemoryMask) != UserMemoryMask) {
		useroptionbyte = FLASH_GetUserOptionByte();

		UserMemoryMask |= WRPR;

		status = FLASH_EraseOptionBytes();

		if (UserMemoryMask != 0xFFFFFFFF) {
			status = FLASH_EnableWriteProtection((uint32_t) ~UserMemoryMask);
		}

		/* Test if user Option Bytes are programmed */
		if ((useroptionbyte & 0x07) != 0x07) {
			/* Restore user Option Bytes */
			if ((useroptionbyte & 0x01) == 0x0) {
				var1 = OB_IWDG_HW;
			}
			if ((useroptionbyte & 0x02) == 0x0) {
				var2 = OB_STOP_RST;
			}
			if ((useroptionbyte & 0x04) == 0x0) {
				var3 = OB_STDBY_RST;
			}

			FLASH_UserOptionByteConfig(var1, var2, var3);
		}

		if (status == FLASH_COMPLETE) {
			//xprintf("Write Protection disabled...\r\n");

			//xprintf("...and a System Reset will be generated to re-load the new option bytes\r\n");

			/* Generate System Reset to load the new option byte values */
			NVIC_SystemReset();
		} else {
			//xprintf("Error: Flash write unprotection failed...\r\n");
		}
	} else {
		//xprintf("Flash memory not write protected\r\n");
	}
}

/**
 * @}
 */

/*
 * flash_verify_image
 * return value:
 * 	-1: No execute image
 * 	-2: No secondary image, primary image checksum failed
 */
int flash_verify_image(SKS_BOOT_INFO *boot_info) {
	int check_crc = 0;
	int copy = 0;
	//char str [255] = {0};
	uint32_t crc_primary = 0;
	uint32_t crc_secondary = 0;
	flash_read_uboot_info(boot_info);
	//Calculate check sum
	if ((boot_info->SecondarySize == 0xFFFFFFFF)
			|| (boot_info->SecondarySize == 0x0)
			|| (boot_info->SecondarySize >= 100 * PAGE_SIZE)) //Invalid Secondary image
			{
		if ((boot_info->PrimarySize == 0x0)
				|| (boot_info->PrimarySize == 0xFFFFFFFF)
				|| (boot_info->PrimarySize >= 100 * PAGE_SIZE)) //Invalid Primary Image's Size
			return -1;
		else {
			CRC_ResetDR();
			crc_primary = CRC_CalcBlockCRC(BOOT_PRIMARY_ADDRESS,
					(boot_info->PrimarySize / 4) + 1);
			if (crc_primary != boot_info->PrimaryCRC) {
				return -2; //Invalid PRIMARY's  CRC
			}
			return 1; //Secondary error, First OK
		}
	} else {
		if ((boot_info->PrimarySize == 0x0)
				|| (boot_info->PrimarySize == 0xFFFFFFFF)
				|| (boot_info->PrimarySize >= 100 * PAGE_SIZE)) //Invalid Primary Image's Size
				{
			copy = 1;
		} else {
			check_crc = 1;
		}
		if ((boot_info->PrimaryCRC != boot_info->SecondaryCRC)
				|| (boot_info->PrimarySize != boot_info->SecondarySize)) //Primary not same Secondary
				{
			if (copy == 0)
				copy = 2;
		}
		if (copy) {
			//Verify Secondary CRC image
			CRC_ResetDR();
			crc_secondary = CRC_CalcBlockCRC(BOOT_SECONDARY_ADDRESS,
					(boot_info->SecondarySize / 4) + 1);
			if (crc_secondary == boot_info->SecondaryCRC) {
				if (((*(__IO uint32_t*) (BOOT_SECONDARY_ADDRESS)) & 0x2FFE0000)
						== 0x20000000) {
					flash_copy_image(boot_info);
					//flash_write_uboot_info(boot_info);
					check_crc = 2;
				} else {
					//check_crc = 3;
				}
			} else {
				//check_crc = 1;
			}
			boot_info->SecondarySize = boot_info->PrimarySize;
			boot_info->SecondaryCRC = boot_info->PrimaryCRC;
			flash_write_uboot_info(boot_info);
		}
		if (check_crc) {
			if ((boot_info->PrimarySize == 0)
					|| (boot_info->PrimarySize == 0xFFFFFFFF))
				return -3;
			CRC_ResetDR();
			crc_primary = CRC_CalcBlockCRC((uint32_t) BOOT_PRIMARY_ADDRESS,
					(uint32_t) (boot_info->PrimarySize / 4) + 1);
			if (crc_primary != boot_info->PrimaryCRC) {
				return -4; //Invalid PRIMARY's  CRC
			}
			if (copy == 1) {
				return 3;
			} else if (check_crc == 2) {
				return 4;
			}
		} else
			return 0;
	}
	return 2;
}

void flash_read_uboot_info(SKS_BOOT_INFO *boot_info) {
	int i = 0;
	uint32_t *pInt = (uint32_t *) UBOOT_CONFIG_ADDRESS;
	uint32_t *pDest = (uint32_t *) boot_info;
	for (i = 0; i < sizeof(SKS_BOOT_INFO) / 4; i++) {
		FLASH_ClearFlag(
				FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR
						| FLASH_FLAG_WRPERR);
		pDest[i] = pInt[i];
	}
}

void flash_write_uboot_info(SKS_BOOT_INFO *boot_info) {
	volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
	//int *pInt = (int *)UBOOT_CONFIG_ADDRESS;
	FLASH_ClearFlag(
			FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR
					| FLASH_FLAG_WRPERR);
	FLASH_ErasePage(UBOOT_CONFIG_ADDRESS); //CONFIG_MAX_2K
	uint32_t *pSource = (uint32_t *) boot_info;
	boot_info->BootVersion = UBOOT_VERSION;
	for (int i = 0; i < sizeof(SKS_BOOT_INFO) / 4; i++)
		FLASHStatus = FLASH_ProgramWord(UBOOT_CONFIG_ADDRESS + i * 4,
				pSource[i]);
	/*
	 FLASHStatus = FLASH_ProgramWord(UBOOT_CONFIG_ADDRESS, boot_info->PrimaryCRC);
	 FLASHStatus = FLASH_ProgramWord(UBOOT_CONFIG_ADDRESS+4, boot_info->PrimarySize);
	 FLASHStatus = FLASH_ProgramWord(UBOOT_CONFIG_ADDRESS+8, boot_info->SecondaryCRC);
	 FLASHStatus = FLASH_ProgramWord(UBOOT_CONFIG_ADDRESS+12, boot_info->SecondarySize);
	 FLASHStatus = FLASH_ProgramWord(UBOOT_CONFIG_ADDRESS+16, boot_info->FirmwareUpdate);
	 FLASHStatus = FLASH_ProgramWord(UBOOT_CONFIG_ADDRESS+16, boot_info->FirmwareUpdate);
	 */
}

int flash_copy_image(SKS_BOOT_INFO *boot_info) {
	//FLASH_Lock();
	uint32_t *data; // = (uint32_t*)BOOT_SECONDARY_ADDRESS;
	uint32_t count = 0;
	uint32_t tmp = (boot_info->SecondarySize / 4) + 1;
	volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;

	data = BOOT_SECONDARY_ADDRESS;
	FLASH_ClearFlag(
			FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR
					| FLASH_FLAG_WRPERR);

	//FLASH_ErasePage(FLASH_CONFIG_ADDRESS+FLASH_PAGE_SIZE);
	int maxPages = ((boot_info->SecondarySize & 0xFFFFF800) + 0x800) / 0x800;
	if (maxPages > 100)
		maxPages = 100;
	for (count = 0; count < maxPages; count++) {
		FLASH_ErasePage(BOOT_PRIMARY_ADDRESS + count * PAGE_SIZE); //CONFIG_MAX_2K
	}
	//&& (FLASHStatus == FLASH_COMPLETE)
	for (count = 0; count < tmp; count++) {
		if ((count % (tmp / 10)) == 0)
			SerialPutChar('.');
		FLASHStatus = FLASH_ProgramWord(
				BOOT_PRIMARY_ADDRESS + count * sizeof(uint32_t), data[count]);
	}
	//SerialPutString("DONE\r\n BOOT_INFO\r\n");
	boot_info->PrimaryCRC = boot_info->SecondaryCRC;
	boot_info->PrimarySize = boot_info->SecondarySize;
	boot_info->PrimaryAddress = BOOT_PRIMARY_ADDRESS;
	boot_info->SecondaryAddress = BOOT_SECONDARY_ADDRESS;

	return 1;
}

void flash_read_config(unsigned char* out) {
	int i = 0;
	uint32_t *pInt = APP_CONFIG_ADDRESS;
	uint32_t *pDest = out;
	for (i = 0; i < 1024; i++) {
		FLASH_ClearFlag(
				FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR
						| FLASH_FLAG_WRPERR);
		pDest[i] = pInt[i];
	}
}

void flash_write_config(unsigned char *in) {
	volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
	//int *pInt = (int *)UBOOT_CONFIG_ADDRESS;
	FLASH_ClearFlag(
			FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR
					| FLASH_FLAG_WRPERR);
	FLASH_ErasePage(APP_CONFIG_ADDRESS); //CONFIG_MAX_2K
	uint32_t *pSource = (uint32_t *) in;
	for (int i = 0; i < 1024 / 4; i++)
		FLASHStatus = FLASH_ProgramWord(APP_CONFIG_ADDRESS + i * 4, pSource[i]);
	/*
	 FLASHStatus = FLASH_ProgramWord(UBOOT_CONFIG_ADDRESS, boot_info->PrimaryCRC);
	 FLASHStatus = FLASH_ProgramWord(UBOOT_CONFIG_ADDRESS+4, boot_info->PrimarySize);
	 FLASHStatus = FLASH_ProgramWord(UBOOT_CONFIG_ADDRESS+8, boot_info->SecondaryCRC);
	 FLASHStatus = FLASH_ProgramWord(UBOOT_CONFIG_ADDRESS+12, boot_info->SecondarySize);
	 FLASHStatus = FLASH_ProgramWord(UBOOT_CONFIG_ADDRESS+16, boot_info->FirmwareUpdate);
	 FLASHStatus = FLASH_ProgramWord(UBOOT_CONFIG_ADDRESS+16, boot_info->FirmwareUpdate);
	 */
}
/**
 * @brief  Print a character on the HyperTerminal
 * @param  c: The character to be printed
 * @retval None
 */
void SerialPutChar(uint8_t c) {
	USART_SendData(USARTx, c);
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET) {
	}
}
/**
 * @brief  Test to see if a key has been pressed on the HyperTerminal
 * @param  key: The key pressed
 * @retval 1: Correct
 *         0: Error
 */
uint32_t SerialKeyPressed(uint8_t *key) {

	if (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) != RESET) {
		*key = (uint8_t) USARTx->RDR;
		return 1;
	} else {
		return 0;
	}
}
int32_t Rcv_Byte(uint8_t *c, uint32_t timeout) {
	uint32_t sec = ulSecCount;
	while (1) {
		if (SerialKeyPressed(c) == 1) {
			return 0;
		}

		if ((ulSecCount - sec) >= timeout)
			return -1;
	}
	return -1;
}

int32_t RcvBuff(uint8_t *buff, int *length, uint32_t timeout) {
	int i = 0;
	int len = *length;
	*length = 0;
	for (i = 0; i < len; i++) {
		if (Rcv_Byte(buff + i, timeout) != 0) {
			//if (Receive_Byte(buff + i, timeout) != 0) {
			//return *length;
			break;
		}
		(*length)++;
	}
	return *length;
}
void gpio_pin_init() {
	GPIO_InitTypeDef GPIO_InitStructure;
#ifdef GPIO_BUZZ_PIN
	GPIO_InitStructure.GPIO_Pin = GPIO_BUZZ_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_BUZZ_PORT, &GPIO_InitStructure);
#endif
#ifdef GPIO_GSM_LED_PORT
	GPIO_InitStructure.GPIO_Pin = GPIO_GSM_LED_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_GSM_LED_PORT, &GPIO_InitStructure);
#endif
#ifdef GPIO_GPS_LED_PORT
	GPIO_InitStructure.GPIO_Pin = GPIO_GPS_LED_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_GPS_LED_PORT, &GPIO_InitStructure);
#endif
#ifdef GPIO_WATCHDOG_PORT
	//init watch dog pin
	GPIO_InitStructure.GPIO_Pin = GPIO_WATCHDOG_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_WATCHDOG_PORT, &GPIO_InitStructure);
#endif

	//GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIO clock */
	/* Connect PXx to USARTx_Tx */
	GPIO_PinAFConfig(USARTx_TX_GPIO_PORT, USARTx_TX_SOURCE, USARTx_TX_AF);

	/* Connect PXx to USARTx_Rx */
	GPIO_PinAFConfig(USARTx_RX_GPIO_PORT, USARTx_RX_SOURCE, USARTx_RX_AF);
	/* Configure USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = USARTx_TX_PIN;
	GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStructure);

	/* Configure USART Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = USARTx_RX_PIN;
	GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStructure);

#if (USE_USART!=1)
	/* Configure USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART Rx as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif

}
void iwdg_init(void) {
	/* IWDG timeout equal to ~2s */
	/* Enable write access to IWDG_PR and IWDG_RLR registers */
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

	/* IWDG counter clock: LSI/256, ~6.4ms  ~ 156.25Khz => 1000ms/156.24 = 6.4ms */
	IWDG_SetPrescaler(IWDG_Prescaler_256);

	/* Set counter reload value to obtain 4s IWDG TimeOut.
	 Counter Reload Value = 4s/IWDG counter clock period
	 = 4s / (256/LSI)
	 = LsiFreq*4/256
	 312.25*6.4 = 2000ms

	 ~ 2s
	 Counter Reload Value = 2000ms/IWDG counter clock period ~ 312.25 -1

	 */
	//IWDG_SetReload(LsiFreq*3/256);
	//IWDG_SetReload(311);  //312 - 1
	IWDG_SetReload(780); //(5s )312 - 1

	/* Reload IWDG counter */
	IWDG_ReloadCounter();

	/* Enable IWDG (the LSI oscillator will be enabled by hardware) */
	IWDG_Enable();

}

/**
 * @brief  Initialize the IAP: Configure RCC, USART and GPIOs.
 * @param  None
 * @retval None
 */
void IAP_Init(void) {

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

#ifdef RCC_GPIO_BUZZ
	RCC_AHBPeriphClockCmd(RCC_GPIO_BUZZ, ENABLE);
#endif

#ifdef RCC_GPIO_GSM_LED
	RCC_AHBPeriphClockCmd(RCC_GPIO_GSM_LED, ENABLE);
#endif

#ifdef RCC_GPIO_GPS_LED
	RCC_AHBPeriphClockCmd(RCC_GPIO_GPS_LED, ENABLE);
#endif

#ifdef USARTx_TX_GPIO_CLK
	RCC_AHBPeriphClockCmd(USARTx_TX_GPIO_CLK, ENABLE);
#endif

#ifdef USARTx_RX_GPIO_CLK
	RCC_AHBPeriphClockCmd(USARTx_RX_GPIO_CLK, ENABLE);
#endif

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

#if 0
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

	//RCC_APB2PeriphClockCmd(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM] | RCC_APB2Periph_AFIO, ENABLE);
#endif
	/* Enable UART clock */
#if (USE_USART==1)
	RCC_APB2PeriphClockCmd(USARTx_CLK, ENABLE);
#elif (USE_USART==2)||(USE_USART==3)||(USE_USART==4)||(USE_USART==5)
	RCC_APB1PeriphClockCmd(USARTx_CLK, ENABLE);
#else
#error "USART not defined!!!"
#endif

	gpio_pin_init();

	/* USART resources configuration (Clock, GPIO pins and USART registers) ----*/
	/* USART configured as follow:
	 - BaudRate = 115200 baud
	 - Word Length = 8 Bits
	 - One Stop Bit
	 - No parity
	 - Hardware flow control disabled (RTS and CTS signals)
	 - Receive and transmit enabled
	 */
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	//STM_EVAL_COMInit(COM1, &USART_InitStructure);

	/* USART configuration */
	USART_Init(USARTx, &USART_InitStructure);

	/* Enable USART */
	USART_Cmd(USARTx, ENABLE);
#if (USE_USART!=1)
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
#endif
	/*
	 USART_InitStructure.USART_BaudRate = 115200;
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	 USART_InitStructure.USART_StopBits = USART_StopBits_1;
	 USART_InitStructure.USART_Parity = USART_Parity_No;
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	 STM_EVAL_COMInit(COM2, &USART_InitStructure);
	 */
}

/*******************(C)COPYRIGHT 2010 STMicroelectronics *****END OF FILE******/
