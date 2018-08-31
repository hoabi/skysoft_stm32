/*
 * main.h
 *
 *  Created on: Aug 15, 2012
 *      Author: Admin
 */

#ifndef MAIN_H_
#define MAIN_H_
#include <stdint.h>
#include <core_cm0.h>
/* Exported functions ------------------------------------------------------- */
void Int2Str(uint8_t* str,int32_t intnum);
uint32_t Str2Int(uint8_t *inputstr,int32_t *intnum);
uint32_t GetIntegerInput(int32_t * num);
uint32_t SerialKeyPressed(uint8_t *key);
uint8_t GetKey();
void SerialPutChar(uint8_t c);
//void Serial_PutString(uint8_t *s);
void SerialPutChar2(uint8_t c);
void SerialPutString2(uint8_t *s);
void GetInputString(uint8_t * buffP);
void FLASH_DisableWriteProtectionPages(uint32_t UserMemMask);
void Main_Menu(void);
void SerialDownload(void);
void SerialUpload(void);
void PrintHex(void *data, int len);
void PC_USART_Init(int baud);
void restart_device();
void disable_usart2(void);
void enalbe_usart2(void);
#define X3SerialPutString(x) X3Serial_PutString((uint8_t*)(x))
//extern SKS_BOOT_INFO boot_inf;

#endif /* MAIN_H_ */
