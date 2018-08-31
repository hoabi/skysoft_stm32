/*
 * mainboot.c
 *
 *  Created on: Aug 15, 2012
 *      Author: Admin
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_crc.h"
#include "alarm.h"
#include "command.h"
#include "xprintf.h"
#include "config.h"
#include "stm32f0xx.h"
#include "string.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t BlockNbr = 0, UserMemoryMask1 = 0;
__IO uint32_t FlashProtection = 0;

volatile extern uint32_t ulSecCount;
volatile extern uint32_t ulTickCount;
volatile extern uint32_t ulMiliCount;

unsigned long lastSentToTracker = 0;

extern char buff_cmd[256];
extern int buff_cmd_idx;
extern char buff_data[1024];
extern int buff_data_idx;
extern int Camera_idx;
extern int On_handler_cmd_from_deveice;
extern int last_time_rec_byte_time;

void SerialPutChar(uint8_t c) {
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {
	}
	USART_SendData(USART1, c);
}
void USARTxPutChar(USART_TypeDef * USARTx, uint8_t c) {
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET) {
	}
	USART_SendData(USARTx, c);
}
void USARTxPutString(USART_TypeDef * USARTx, unsigned char *s) {
	while (*s != '\0') {
		USARTxPutChar(USARTx, *s);
		s++;
	}
}
void Serial_PutString(unsigned char *s) {
	while (*s != '\0') {
		SerialPutChar(*s);
		s++;
	}
}
void SerialPutString(unsigned char *s) {
	while (*s != '\0') {
		SerialPutChar(*s);
		s++;
	}
}
void Process_Command_form_deveice(void) {
	if ((On_handler_cmd_from_deveice == 1)
			|| (last_time_rec_byte_time + 1 < ulMiliCount)) {
		Camera_idx = buff_cmd[1];
		switch (buff_cmd[1]) {
		case 1:
			buff_cmd[1] = 0;
			USARTxPutString(USART2, buff_cmd);
			On_handler_cmd_from_deveice = 0;
			break;
		case 2:
			buff_cmd[1] = 0;
			USARTxPutString(USART3, buff_cmd);
			On_handler_cmd_from_deveice = 0;
			break;
		case 3:
			buff_cmd[1] = 0;
			USARTxPutString(USART4, buff_cmd);
			On_handler_cmd_from_deveice = 0;
			break;
		case 4:
			buff_cmd[1] = 0;
			USARTxPutString(USART5, buff_cmd);
			On_handler_cmd_from_deveice = 0;
			break;
		case 5:
			buff_cmd[1] = 0;
			USARTxPutString(USART6, buff_cmd);
			On_handler_cmd_from_deveice = 0;
			break;
		case 6:
			buff_cmd[1] = 0;
			USARTxPutString(USART7, buff_cmd);
			On_handler_cmd_from_deveice = 0;
			break;
		default:
			break;
		}
	}
}
void Main_Menu(void) {
	while (1) {
		Process_Command_form_deveice();
	}
}
