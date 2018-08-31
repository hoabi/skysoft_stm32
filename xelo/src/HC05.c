/*
 * HC05.c
 *
 *  Created on: Oct 31, 2017
 *      Author: ThangNguyen
 */
#include "HC05.h"
#include "xprintf.h"
#include <string.h>
#include <stdint.h>
#include <stm32f10x_usart.h>
#include <main.h>
#include "delay.h"
#define HC05_PIO9_port GPIOB
#define HC05_PIO9_pin GPIO_Pin_15
#define HC05_DIS	GPIO_ResetBits(GPIOB, GPIO_Pin_14)
#define HC05_EN		GPIO_SetBits(GPIOB, GPIO_Pin_14)
extern uint32_t MiliCount;
uint32_t last_check_time = 0;
extern char BLE_buff_temp[256];
extern int BLE_buff_idx;
void UART4_PutC(uint8_t C) {
	while (USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET) {
	}
	USART_SendData(UART4, C);
}
void UART4_PutS(char *S) {
	while (*S != '\0') {
		UART4_PutC(*S);
		S++;
	}
}
char UART4_getC(void) {
	char C = 0;
	int time_out = 0;
	time_out = MiliCount + 1;
	while (USART_GetFlagStatus(UART4, USART_FLAG_RXNE) != SET) {
		if (time_out < MiliCount)
			return 0x0;
	}
	C = USART_ReceiveData(UART4);
	return C;
}
void UART4_getS(char *S) {
	int time_out = MiliCount + 1;
	char Cchar;
	while (1) {
		while (USART_GetFlagStatus(UART4, USART_FLAG_RXNE) != SET) {
			if (time_out < MiliCount) {
				return;
			}
		}
		Cchar = USART_ReceiveData(UART4);
		*S = Cchar;
		S++;
		time_out = MiliCount + 1;
	}

}
int HC05_Get_Connected(void) {
	if (GPIO_ReadInputDataBit(HC05_PIO9_port, HC05_PIO9_pin)) {
		return 1;
	} else {
		return 0;
	}

}
int HC05_TestOk(void) {
	char str[5] = { 0 };
	UART4_getS(str);
	if (strcmp(str, "OK\n\r")) {
		return 1;
	} else {
		return 0;
	}
}
int HC05_check(void) {
	HC05_EN;
	HC05_Reset();
	memset(BLE_buff_temp, 0, sizeof(BLE_buff_temp)); //clear buff
	BLE_buff_idx = 0; //reset index
	UART4_PutS("AT\n\r"); //send AT
	last_check_time = MiliCount + 5; //set timeout point
	//waiting for response
	while (BLE_buff_temp[0] == 0) {
		if (last_check_time < MiliCount)
			break; //time out
	}
	HC05_DIS;
	if (BLE_buff_temp[0] != 0) {
		if (strcmp(BLE_buff_temp, "OK\n\r")) {
			return 1; //ok
		} else {
			return 0; //fail
		}
	} else
		return -1; //no response

}
int HC05_Reset(void) {
	memset(BLE_buff_temp, 0, sizeof(BLE_buff_temp)); //clear buff
	BLE_buff_idx = 0; //reset index
	UART4_PutS("AT+RESET\n\r"); //send AT
	last_check_time = MiliCount + 100; //set timeout point
	//waiting for response
	while (1) {
		if (last_check_time < MiliCount || BLE_buff_temp[BLE_buff_idx] == 0x0a)
			break;
	}
	if (strcmp(BLE_buff_temp, "OK\n\r")) {
		return 1; //ok
	} else {
		return 0; //fail
	}
}
int HC05_SetPassword(char *str) {
	char data[64] = { 0 };
	HC05_EN;
	delay_ms(100);
	//UART4_PutS("AT+RESET\r\n");
	//delay_ms(100);
	memset(BLE_buff_temp, 0, sizeof(BLE_buff_temp)); //clear buff
	BLE_buff_idx = 0; //reset index
	usnprintf(data, strlen(str) + strlen("AT+PSWD=\r\n"), "AT+PSWD=%s\r\n",
			str);
	UART4_PutS(data);
	//delay_ms(100); //set name
	last_check_time = MiliCount + 100; //set timeout point
	//waiting for response
	while (1) {
		if ((last_check_time < MiliCount)
				|| (BLE_buff_temp[BLE_buff_idx] == 0x0a))
			break;
	}
	//xprintf("Response:%s", BLE_buff_temp);
	if (strcmp(BLE_buff_temp, "OK\r\n") == 0) {
		HC05_DIS;
		delay_ms(100);
		UART4_PutS("AT+RESET\r\n");
		return 1; //ok
	} else {
		HC05_DIS;
		delay_ms(100);
		UART4_PutS("AT+RESET\r\n");
		return 0; //fail
	}
}
int HC05_SetName(char *str) {
	char data[64] = { 0 };
	HC05_EN;
	delay_ms(100);
	//UART4_PutS("AT+RESET\r\n");
	//delay_ms(100);
	memset(BLE_buff_temp, 0, sizeof(BLE_buff_temp)); //clear buff
	BLE_buff_idx = 0; //reset index
	usnprintf(data, strlen(str) + strlen("AT+NAME=\r\n"), "AT+NAME=%s\r\n",
			str);
	UART4_PutS(data);
	//delay_ms(100); //set name
	last_check_time = MiliCount + 100; //set timeout point
	//waiting for response
	while (1) {
		if ((last_check_time < MiliCount)
				|| (BLE_buff_temp[BLE_buff_idx] == 0x0a))
			break;
	}
	xprintf("Response:%s", BLE_buff_temp);
	if (strcmp(BLE_buff_temp, "OK\r\n") == 0) {
		HC05_DIS;
		delay_ms(100);
		UART4_PutS("AT+RESET\r\n");
		return 1; //ok
	} else {
		HC05_DIS;
		delay_ms(100);
		UART4_PutS("AT+RESET\r\n");
		return 0; //fail
	}
}
int HC05_SetUsart(void) {
	HC05_EN;
	memset(BLE_buff_temp, 0, sizeof(BLE_buff_temp)); //clear buff
	BLE_buff_idx = 0; //reset index
	UART4_PutS("AT+UART=38400,0,0\n\r"); //set name
	last_check_time = MiliCount + 5; //set timeout point
	//waiting for response
	while (BLE_buff_temp[0] == 0) {
		if (last_check_time < MiliCount)
			break; //time out
	}
	if (BLE_buff_temp[0] != 0) {
		if (strcmp(BLE_buff_temp, "OK\r\n")) {
			return 1; //ok
		} else {
			return 0; //fail
		}
	} else
		return -1; //no response

}
int HC05_seting(void) {
	HC05_EN;
	for (int i = 0; i < 5; i++) {
		if (HC05_Reset())
			continue;
	}

}
int HC05_SetingMode(void) {
	return HC05_Reset();

}
int HC05_NormalMode(void) {
	HC05_DIS;
	return HC05_Reset();
}
void HC05_init(void) {

}

int HC05_WorkingMode(void) {
	return 0;
}
int HC05_change_baudrate(int baudrate) {
	/*
	 char str[5] = { 0 };
	 UART4_PutS("AT+UART=%d,0,0\n\r", baudrate);
	 return HC05_TestOk();
	 */

}
void HC05_SendData(char *S) {
	if (HC05_Get_Connected()) {
		UART4_PutS(S);
	} else {
		xprintf("not connect\r\n");
	}
}
