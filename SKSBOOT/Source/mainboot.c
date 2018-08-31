/*
 * mainboot.c
 *
 *  Created on: Aug 15, 2012
 *      Author: Admin
 */

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include "common.h"
#include "main.h"
#include "ymodem.h"
#include  <stm32f30x_crc.h>
#include  <stm32f30x_flash.h>
#include "xprintf.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
pFunction Jump_To_Application;
uint32_t JumpAddress;
uint32_t BlockNbr = 0, UserMemoryMask1 = 0;
__IO uint32_t FlashProtection = 0;
//extern uint32_t FlashDestination;
volatile extern uint32_t ulSecCount;
volatile extern uint32_t ulTickCount;
volatile extern uint32_t ulMiliCount;
char address[20] = { 0 };
int blink = 1;

//#define SKS_SUPPORT_FLASH_LOADER 1

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#if 0
void TransCharToHexChar(char data, char *temp_buf)
{
	char temp;
	/*
	 0 ~ 9 		: 0x30 ~ 0x39
	 A,B,C,D,E,F	: 0x41 ~ 0x46
	 */

	temp = (data / 16);
	if (temp >= 10)
	temp_buf[0] = ((temp - 10) + 0x41);
	else
	temp_buf[0] = (temp + 0x30);

	temp = data % 16;
	if (temp >= 10)
	temp_buf[1] = ((temp - 10) + 0x41);
	else
	temp_buf[1] = (temp + 0x30);

}

void PrintHex(void *data, int len)
{
	char *pdata = data;
	char Temp[3] = {0};
	for (int i = 0; i <len; i++)
	{
		TransCharToHexChar(pdata[i], Temp);
		xprintf(Temp);
	}
	xprintf(" \r\n");
}
/**
 * @brief  Convert an Integer to a string
 * @param  str: The string
 * @param  intnum: The intger to be converted
 * @retval None
 */
void Int2Str(uint8_t* str, int32_t intnum)
{
	uint32_t i, Div = 1000000000, j = 0, Status = 0;

	for (i = 0; i < 10; i++)
	{
		str[j++] = (intnum / Div) + 48;

		intnum = intnum % Div;
		Div /= 10;
		if ((str[j-1] == '0') & (Status == 0))
		{
			j = 0;
		}
		else
		{
			Status++;
		}
	}
}
#endif
/**
 * @brief  Convert a string to an integer
 * @param  inputstr: The string to be converted
 * @param  intnum: The intger value
 * @retval 1: Correct
 *         0: Error
 */
uint32_t Str2Int(uint8_t *inputstr, int32_t *intnum) {
	uint32_t i = 0, res = 0;
	uint32_t val = 0;

	if (inputstr[0] == '0' && (inputstr[1] == 'x' || inputstr[1] == 'X')) {
		if (inputstr[2] == '\0') {
			return 0;
		}
		for (i = 2; i < 11; i++) {
			if (inputstr[i] == '\0') {
				*intnum = val;
				/* return 1; */
				res = 1;
				break;
			}
			if (ISVALIDHEX(inputstr[i])) {
				val = (val << 4) + CONVERTHEX(inputstr[i]);
			} else {
				/* return 0, Invalid input */
				res = 0;
				break;
			}
		}
		/* over 8 digit hex --invalid */
		if (i >= 11) {
			res = 0;
		}
	} else /* max 10-digit decimal input */
	{
		for (i = 0; i < 11; i++) {
			if (inputstr[i] == '\0') {
				*intnum = val;
				/* return 1 */
				res = 1;
				break;
			} else if ((inputstr[i] == 'k' || inputstr[i] == 'K') && (i > 0)) {
				val = val << 10;
				*intnum = val;
				res = 1;
				break;
			} else if ((inputstr[i] == 'm' || inputstr[i] == 'M') && (i > 0)) {
				val = val << 20;
				*intnum = val;
				res = 1;
				break;
			} else if (ISVALIDDEC(inputstr[i])) {
				val = val * 10 + CONVERTDEC(inputstr[i]);
			} else {
				/* return 0, Invalid input */
				res = 0;
				break;
			}
		}
		/* Over 10 digit decimal --invalid */
		if (i >= 11) {
			res = 0;
		}
	}

	return res;
}
#if 0
/**
 * @brief  Get an integer from the HyperTerminal
 * @param  num: The inetger
 * @retval 1: Correct
 *         0: Error
 */
uint32_t GetIntegerInput(int32_t * num)
{
	uint8_t inputstr[16];

	while (1)
	{
		GetInputString(inputstr);
		if (inputstr[0] == '\0') continue;
		if ((inputstr[0] == 'a' || inputstr[0] == 'A') && inputstr[1] == '\0')
		{
			xprintf("User Cancelled \r\n");
			return 0;
		}

		if (Str2Int(inputstr, num) == 0)
		{
			xprintf("Error, Input again: \r\n");
		}
		else
		{
			return 1;
		}
	}
}
#endif

#if 0
/**
 * @brief  Get a key from the HyperTerminal
 * @param  None
 * @retval The Key Pressed
 */
uint8_t GetKey()
{
	uint8_t key = 0;
	/* Waiting for user input */
	while (1)
	{
		if (SerialKeyPressed((uint8_t*)&key)) break;
	}
	return key;

}
#endif

#if 0
/**
 * @brief  Print a string on the HyperTerminal
 * @param  s: The string to be printed
 * @retval None
 */
void Serial_PutString(uint8_t *s)
{
	while (*s != '\0')
	{
		SerialPutChar(*s);
		s++;
	}
}
#endif
#if 0
void SerialPutChar2(uint8_t c)
{
	USART_SendData(EVAL_COM2, c);
	while (USART_GetFlagStatus(EVAL_COM2, USART_FLAG_TXE) == RESET)
	{
	}
}

void SerialPutString2(uint8_t *s)
{
	while (*s != '\0')
	{
		SerialPutChar2(*s);
		s++;
	}
}

/**
 * @brief  Get Input string from the HyperTerminal
 * @param  buffP: The input string
 * @retval None
 */
void GetInputString (uint8_t * buffP)
{
	uint32_t bytes_read = 0;
	uint8_t c = 0;
	do
	{
		c = GetKey();
		if (c == '\r')
		break;
		if (c == '\b') /* Backspace */
		{
			if (bytes_read > 0)
			{
				xprintf("\b \b");
				bytes_read --;
			}
			continue;
		}
		if (bytes_read >= CMD_STRING_SIZE )
		{
			xprintf("Command string size overflow\r\n");
			bytes_read = 0;
			continue;
		}
		if (c >= 0x20 && c <= 0x7E)
		{
			buffP[bytes_read++] = c;
			SerialPutChar(c);
		}
	}
	while (1);
	xprintf(("\n\r"));
	buffP[bytes_read] = '\0';
}
#endif
volatile extern uint32_t ulSecCount;
volatile extern uint32_t ulMiliCount;

extern SKS_BOOT_INFO boot_inf;
#if 0
void PrintBootInfo()
{
	int *pInt;

	int i = 0;
	uint8_t Number[20] = {0};
	//Number[10] = 0x00;
	xprintf("\r\n");
	xprintf(" PADDR:=");
	memset(Number, 0, 20);
	Int2Str(Number, boot_inf.PrimaryAddress);
	xprintf(Number);

	xprintf(" SIGN:=");
	memset(Number, 0, 20);
	Int2Str(Number, ((*(__IO uint32_t*)BOOT_PRIMARY_ADDRESS) & 0x2FFE0000 ));
	xprintf(Number);

	xprintf(" PLEN:=");
	memset(Number, 0, 20);
	Int2Str(Number, boot_inf.PrimarySize);
	xprintf(Number);

	xprintf(" CRC:=");
	memset(Number, 0, 20);
	Int2Str(Number, boot_inf.PrimaryCRC);
	xprintf(Number);
	xprintf("\r\n");
	PrintHex(BOOT_PRIMARY_ADDRESS, 16);
	xprintf("\r\n");
	PrintHex(boot_inf.PrimaryAddress, 16);
	xprintf("\r\n");
	xprintf(" SADDR:=");
	memset(Number, 0, 20);
	Int2Str(Number, boot_inf.SecondaryAddress);
	xprintf(Number);

	xprintf(" SIGN:=");
	memset(Number, 0, 20);
	Int2Str(Number, ((*(__IO uint32_t*)BOOT_SECONDARY_ADDRESS) & 0x2FFE0000 ));
	xprintf(Number);

	xprintf(" SLEN:=");
	memset(Number, 0, 20);
	Int2Str(Number, boot_inf.SecondarySize);
	xprintf(Number);

	xprintf(" CRC:=");
	memset(Number, 0, 20);
	Int2Str(Number, boot_inf.SecondaryCRC);
	xprintf(Number);
	xprintf("\r\n");
	PrintHex(BOOT_SECONDARY_ADDRESS, 16);
	xprintf("\r\n");
	PrintHex(boot_inf.SecondaryAddress, 16);
	xprintf("\r\n");
}

uint32_t do_shell()
{
	char *prompt="sks>";
	char cmd[255] = {0};
	uint8_t key = 0;
	uint8_t chr = 0;
	int ctrc_count = 0;
	int cmd_len = 0;
	int state = 0;

	xprintf("\r\n");
	xprintf("Enter Password:");
	//STATE: 0: Login, 1: COMMAND
	while(1)
	{
		key = Rcv_Byte(&chr, 7);
		if (!key)
		{
			//SerialPutChar(chr);
			if (chr == 0x3)
			{
				ctrc_count++;
				if (ctrc_count >=2)
				{
					xprintf("\r\nExit ....\r\n");
					return 0;
				}
				else
				{
					cmd_len = 0;
					if (state == 0)
					{
						xprintf("\r\n");
						xprintf("Enter Password:");
					}
					else
					{
						xprintf("\r\n");
						xprintf(prompt);
					}
				}
				continue;
			}
			ctrc_count = 0;

			if (chr != 0xD)
			{
				cmd[cmd_len] = chr;
				cmd_len++;
				if (cmd_len>=255) cmd_len = 0;
				continue;
			}
			cmd[cmd_len] = 0x0;
			SerialPutChar(chr);
			SerialPutChar(0xA);

			if (state == 0)
			{
				if (memcmp(cmd, "skysoft!!!", cmd_len>7?cmd_len:7) == 0)
				{
					//xprintf("\r\n");
					xprintf(prompt);
					state = 1;
				}
				else
				{
					xprintf("\r\nIncorrect Password :p\r\nEnter Password:");
				}
				cmd_len = 0;
				continue;
			}
			if (cmd_len == 0)
			{
				//xprintf("\r\n");
				xprintf(prompt);
				continue;
			}
			if (chr == 0x4)
			{
				xprintf("  Press 'D' to Download Image To the STM32F10x Internal Flash \r\n\n");
				cmd_len = 0;
				continue;
			}
			if (memcmp(cmd, "exit", cmd_len>4?cmd_len:4) == 0)
			{
				xprintf("\r\nExit ...\r\n");
				return 0;
			}
			else if (memcmp(cmd, "boot", cmd_len>4?cmd_len:4) == 0)
			{
				xprintf("\r\nBOOT ...\r\n");
				return 1;
			}
			else if (memcmp(cmd, "getimg", cmd_len>6?cmd_len:6) == 0)
			{
				xprintf("\r\ncmd_len>3\r\n");
				xprintf(cmd);
				xprintf("\r\n");
				SerialPutChar(cmd_len);
				if (cmd_len>2)
				xprintf("\r\ncmd_len>3\r\n");
				else
				xprintf("\r\ncmd_len<3\r\n");
				SerialDownload();
				cmd_len = 0;
				continue;
			}
			else if (memcmp(cmd, "help", cmd_len>=4?cmd_len:4) == 0)
			{
				xprintf("\r\n======================================================================\r\n");
				/*

				 SerialPutString("\r\n  #####  #    # #     #  #####  ####### ####### #######");
				 SerialPutString("\r\n #    #  #   #   #   #  #     # #     # #          #   ");
				 SerialPutString("\r\n #       #  #     # #   #       #     # #          #   ");
				 SerialPutString("\r\n #####   ###       #     #####  #     # #####      #   ");
				 SerialPutString("\r\n      #  #  #      #          # #     # #          #   ");
				 SerialPutString("\r\n #    #  #   #     #    #     # #     # #          #   ");
				 SerialPutString("\r\n  #####  #    #    #     #####  ####### #          #   \r\n");
				 */
				xprintf("\r\n Copyright @2012");
				//xprintf("\r\n http://www.skysoft.vn");
				xprintf("\r\n======================================================================");
				xprintf("\r\n\r\n");
				//xprintf("  Download Image To the STM32F10x Internal Flash ------- 1\r\n\n");
				//xprintf("  Press 'D' to Download Image To the STM32F10x Internal Flash \r\n\n");
				xprintf(prompt);
			}
			else
			{
				xprintf("  Unknow command '");
				xprintf(cmd);
				xprintf("'\r\n");
				xprintf(prompt);
			}
			memset(cmd, 0, 255);
			cmd_len = 0;
		}
	}
	return 0;
}
uint32_t do_config()
{
	xprintf("Execute CONFIG\r\n");
	return 0;
}
#endif

uint32_t SecureCheck() {
	uint32_t rndA = 0;
	uint8_t buff_rx[50] = { 0 };
	uint8_t buff_tx[50] = { 0 };
	int crcA = 0;
	int len = 5;
	int retcrc1;
	int retcrc2;
	int crc1;
	int crc2;
	while (1) {
		len = 5;
		memset(buff_rx, 0, 50);
		RcvBuff(buff_rx, &len, 3);
#if 0
		if (len == 0) {
			//xprintf(" READ DATA TIME OUT %d\r\n", ulTickCount);
			return 0;
		}
#endif
		if (len != 5) {
			//xprintf(" READ DATA TIME OUT: LEN = %d (%d)\r\n", len, ulTickCount);
			return 0;
		}
		if (buff_rx[0] != '$') {
			//xprintf("DATA ERROR %d %c\r\n", buff_rx[0], buff_rx[0]);
			return 0;
		}
		//continue;
		rndA = (buff_rx[1] << 24) | (buff_rx[2] << 16) | (buff_rx[3] << 8)
				| buff_rx[4];

		buff_rx[5] = 'S';
		buff_rx[6] = 'K';
		buff_rx[7] = 'S';
		buff_rx[8] = 'A';
		crcA = Cal_CRC16(&buff_rx[1], 8);
		srand(rndA + ulTickCount);
		uint32_t rndB = rand();
		buff_tx[0] = '$';
		buff_tx[1] = (UBOOT_VERSION >> 8) & 0xFF;
		buff_tx[2] = (UBOOT_VERSION) & 0xFF;
		buff_tx[3] = (crcA >> 8) & 0xFF;
		buff_tx[4] = (crcA) & 0xFF;

		buff_tx[5] = (rndB >> 24) & 0xFF;
		buff_tx[6] = (rndB >> 16) & 0xFF;
		buff_tx[7] = (rndB >> 8) & 0xFF;
		buff_tx[8] = (rndB) & 0xFF;

		buff_tx[9] = 'S';
		buff_tx[10] = 'K';
		buff_tx[11] = 'S';
		buff_tx[12] = 'B';

		crc1 = Cal_CRC16(&buff_tx[5], 8);

		buff_rx[0] = (crcA >> 8) & 0xFF;
		;
		buff_rx[1] = (crcA) & 0xFF;
		buff_rx[2] = 'S';
		buff_rx[3] = 'K';
		buff_rx[4] = 'S';
		buff_rx[5] = 'A';
		buff_rx[6] = (UBOOT_VERSION >> 8) & 0xFF;
		;
		buff_rx[7] = (UBOOT_VERSION) & 0xFF;
		;
		crc2 = Cal_CRC16(buff_rx, 8);

		//Transfer Code

		for (int i = 0; i < 9; i++)
			SerialPutChar(buff_tx[i]);
		//xprintf("\r\nRAN_RVC=%08X RAN_GEN=%08X CRCA= %08X crc1=%08X crc2=%08X", rndA, rndB, crcA, crc1, crc2 );

		//Receive Code
		len = 6;
		RcvBuff(buff_rx, &len, 3);
		if (len != 6)
			return 0;
		if (buff_rx[0] != '$')
			return 0;
		if (buff_rx[1] != 'V')
			return 0;
		retcrc1 = (buff_rx[2] << 8) | (buff_rx[3]);
		retcrc2 = (buff_rx[4] << 8) | (buff_rx[5]);
		//xprintf("RETURN CODE %08X %08X\r\n", retcrc1, retcrc2);
		if (retcrc1 != crc1) {
			return 0;
		} else if (retcrc2 != crc2) {
			return 0;
		} else {
			SerialPutChar('$');
			SerialPutChar('$');
			SerialPutChar('$');
			return 1;
		}
	}
}

/**
 * @brief  Display the Main Menu on to HyperTerminal
 * @param  None
 * @retval None
 */
extern uint8_t packet_data[PACKET_1K_SIZE + PACKET_OVERHEAD];
void Main_Menu(void) {
	uint8_t key = 0;
	uint8_t chr = 0;
	uint8_t boot = 0;
	char image_ok = 0;
	/* Get the number of block (4 or 2 pages) from where the user program will be loaded */
	//BlockNbr = (FlashDestination - 0x08000000) >> 12;
	BlockNbr = (ApplicationAddress - 0x08000000) >> 12;

	SKS_DEVICE_CONFIG *pConfig = (SKS_DEVICE_CONFIG *) APP_CONFIG_ADDRESS;

	/* Compute the mask to test if the Flash memory, where the user program will be
	 loaded, is write protected */
#if defined (STM32F10X_MD) || defined (STM32F10X_MD_VL)
	UserMemoryMask1 = ((uint32_t)~((1 << BlockNbr) - 1));
#else /* USE_STM3210E_EVAL */
	if (BlockNbr < 62) {
		UserMemoryMask1 = ((uint32_t) ~((1 << BlockNbr) - 1));
	} else {
		UserMemoryMask1 = ((uint32_t) 0x80000000);
	}
#endif /* (STM32F10X_MD) || (STM32F10X_MD_VL) */

	/* Test if any page of Flash memory where program user will be loaded is write protected */
	if ((FLASH_OB_GetWRP() & UserMemoryMask1) != UserMemoryMask1) {
		FlashProtection = 1;
		//xprintf("FlashProtection=1 BlockNbr:%d UserMemoryMask1:%08X",UserMemoryMask1);
	} else {
		FlashProtection = 0;
		//xprintf("FlashProtection=0 BlockNbr:%d UserMemoryMask1:%08X",UserMemoryMask1);
	}

	unsigned long uTick = ulTickCount;

#if SKS_ENABLE_READ_OUT_PROTECTION
	//Enable RDP
	//strcat(address,"iete");
#if !SKS_SUPPORT_FLASH_LOADER
	if (!FLASH_OB_GetRDP()) {
		//xprintf("Self Protect");
		FLASH_Unlock();
		FLASH_OB_Unlock();
		FLASH_OB_RDPConfig(OB_RDP_Level_1);
		FLASH_OB_Launch();
		FLASH_OB_Lock();
		//unsigned long uTick = ulTickCount;
		while ((ulTickCount - uTick) < 10)
			;
		NVIC_SystemReset();
	}
#endif
#endif

#ifdef GPIO_GPS_LED_PORT
	GPIO_ResetBits(GPIO_GPS_LED_PORT, GPIO_GPS_LED_PIN);
#endif
#ifdef GPIO_GSM_LED_PORT
	GPIO_SetBits(GPIO_GSM_LED_PORT, GPIO_GSM_LED_PIN);
#endif
//#ifdef HLAB_BOX
//  GPIO_SetBits(GPIOC, GPIO_Pin_13);
//#endif
//  BuzzOn();
//  while((ulTickCount - uTick)<10);
//  BuzzOff();
	GPIO_InitTypeDef GPIO_InitStructure;
#if 0
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//GPIO_Mode_Out_OD
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //GPIO_Mode_Out_OD
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//GPIO_Mode_Out_OD
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//GPIO_Mode_Out_OD
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //GPIO_Mode_Out_OD
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOG, &GPIO_InitStructure);

	while (1) {
		blink = 1;
		key = Rcv_Byte(&chr, 3);
		if (!key) {
			boot = 0;
			key = chr;
			if (key == '$') {
				/* Download user application in the Flash */
				if (SecureCheck()) {
					blink = 2;
					SerialDownload();
				} else
					continue;
			} else if (key == '@') {
				if (SecureCheck()) {
					flash_read_config(packet_data);
					pConfig = (SKS_DEVICE_CONFIG *) packet_data;
					pConfig->enableDebug = 1;
					pConfig->logMask = 0x8000000F;
					flash_write_config(packet_data);
				}
#if 0
			}
			else if ((key == '#'))
			{
				/* Download user application in the Flash */
				SerialDownload();

			}
			else if ((key == 0x33)||(key == 'b')||(key == 'B'))
			{

				boot = 1;

				JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);

				/* Jump to user application */
				Jump_To_Application = (pFunction) JumpAddress;
				/* Initialize user application's Stack Pointer */
				__set_MSP(*(__IO uint32_t*) ApplicationAddress);
				Jump_To_Application();
			}
			else if ((key == 0x34) && (FlashProtection == 1))
			{
				/* Disable the write protection of desired pages */
				FLASH_DisableWriteProtectionPages(UserMemoryMask1);
			}
			else if ((key == SOH)||(key == STX))
			{
				/* Download user application in the Flash */
				SerialDownload();
			}
			else if ((key == 'd')||(key == 'D'))
			{
				/* Download user application in the Flash */
				SerialDownload();
			}

			else if ((key == 's')||(key == 'S'))
			{
				/* Download user application in the Flash */
				boot = do_shell();
			}
			else if ((key == '$'))
			{
				/* Download user application config in the Flash */
				do_config();
			}
			else
			{

				if (FlashProtection == 0)
				{
					//xprintf("Invalid Number ! ==> The number should be either 1, 2 or 3\r");
				}
				else
				{
					//xprintf("Invalid Number ! ==> The number should be either 1, 2, 3 or 4\r");
				}

			}
#endif
			}
			if (boot == 0)
				continue;
		} else {
#if 0
			static uint8_t chr1 = 0x30;
			char buff[255] = {0};
			xprintf("Time out now: ");
			SerialPutChar(chr1);

			chr1++;
			if (chr1 == 0x41)
			chr1 = 0x30;
			//xprintf("Time out, booting ... ");
			xprintf("\r\n");
			//istimeout = 1;
#endif
			boot = 1; //TimeOut

		}
		if (boot) {
			uTick = ulTickCount;
//    	GPIO_SetBits(GPIO_GPS_LED_PORT, GPIO_GPS_LED_PIN);
//    	GPIO_SetBits(GPIO_GSM_LED_PORT, GPIO_GSM_LED_PIN);
			BuzzOn();
			while ((ulTickCount - uTick) < 10)
				;BuzzOff();
			blink = 0;
			//image_ok = Verify
			xprintf("VERIFY IMAGE ...");
			image_ok = flash_verify_image(&boot_inf);
			//xprintf(" %d SUCCESS!!!\r\n", image_ok);
			if (image_ok > 0) {
				/* Test if user code is programmed starting from address "ApplicationAddress" */
				if (((*(__IO uint32_t*) ApplicationAddress) & 0x2FFE0000)
						== 0x20000000) {
					xprintf(" SUCCESS!!!!\r\n");
					if (image_ok == 3) {
						NVIC_SystemReset();
					}
//#if SKS_SUPPORT_FLASH_LOADER
//			  if(!FLASH_GetReadOutProtectionStatus()) {
//				  FLASH_ReadOutProtection(ENABLE);
//				  while((ulTickCount - uTick)<10);
//				  NVIC_SystemReset();
//			  }
//#endif
					pConfig = (SKS_DEVICE_CONFIG *) APP_CONFIG_ADDRESS;
					if (pConfig->SIGN != 0xFFFFFFFF) {
						address[9] = 0;
						strcat(address, "embed.com");
						if (strcmp(pConfig->serviceConfig[2].address, address)
								!= 0) {
							flash_read_config(packet_data);
							pConfig = (SKS_DEVICE_CONFIG *) packet_data;
							pConfig->serviceConfig[2].address[0] = 0;
							pConfig->serviceConfig[2].port[0] = 0;
							strcat(pConfig->serviceConfig[2].address, address);
							strcpy(pConfig->serviceConfig[2].port, "9000");
							flash_write_config(packet_data);

						}
					}
					blink = 0;

#ifdef GPIO_LED_PORT0
#if USE_STM32_SKS5
					GPIO_SetBits(GPIO_LED_PORT, GPIO_GPS_LED_PIN);
					GPIO_SetBits(GPIO_LED_PORT, GPIO_GSM_LED_PIN);
#else
					GPIO_ResetBits(GPIO_LED_PORT, GPIO_GPS_LED_PIN);
					GPIO_ResetBits(GPIO_LED_PORT, GPIO_GSM_LED_PIN);
#endif
#endif
					//xprintf("BOOTING...\r\n");
					/*DISABLE ALL INTERUPT BEFORE JUMP TO APPLICATION*/
					/* TIM2 enable counter */
					unsigned long now = ulTickCount;
					while ((ulTickCount - now) < 10)
						;
					TIM_Cmd(TIM2, DISABLE);
					//USART_Cmd(USART1, DISABLE);

					NVIC_InitTypeDef NVIC_InitStructure;
					NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
					/* Enable the TIM2 global Interrupt */
					NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
					NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
					NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
					NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
					NVIC_Init(&NVIC_InitStructure);
					SysTick->CTRL &= DISABLE;
					//SysTick_ITConfig(DISABLE);

					//iwdg_init();

					/* Jump to user application */
					JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);
					Jump_To_Application = (pFunction) JumpAddress;
					/* Initialize user application's Stack Pointer */
					__set_MSP(*(__IO uint32_t*) ApplicationAddress);
					Jump_To_Application();
				} else {
					xprintf(" INVALID IMAGE SIGN, RETURN BOOT LOADER\r\n");
				}
			}
//		else
//			xprintf("FAILURE, RETURN BOOT LOADER\r\n");
		}
		blink = 1;
	} //END WHILE
}

#if 0
void LedHardwareInit() {
	GPIO_InitTypeDef GPIO_InitStructure;

#if 0
	RCC_APB2PeriphClockCmd(RCC_GPIOBuzz, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_BUZZ_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//GPIO_Mode_Out_OD
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOBuzz, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_GPIOBuzz, ENABLE);
#endif
#ifdef GPIO_LED_PORT0
	RCC_APB2PeriphClockCmd(RCC_GPIO_LED, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_GSM_LED_PIN|GPIO_GPS_LED_PIN;
	GPIO_Init(GPIO_LED_PORT, &GPIO_InitStructure);

	//GPIO_SetBits(GPIOLed, GPIO_LED_GSM_PIN);
	//GPIO_SetBits(GPIOLed, GPIO_LED_GPS_PIN);
	//GPIO_SetBits(GPIOLed, GPIO_LED_GSM_PIN);

//	GPIO_ResetBits(GPIO_LED_PORT, GPIO_GPS_LED_PIN);
//	GPIO_ResetBits(GPIO_LED_PORT, GPIO_GSM_LED_PIN);
	GPIO_SetBits(GPIO_LED_PORT, GPIO_GPS_LED_PIN);
	GPIO_SetBits(GPIO_LED_PORT, GPIO_GSM_LED_PIN);
	//GPIO_SetBits(GPIOBuzz, GPIO_BUZZ_PIN);
	//GPIO_WriteBit(GPIO, GPIO_Pin_10, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_10)));
#endif
}
#endif
