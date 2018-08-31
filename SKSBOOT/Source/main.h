/*
 * main.h
 *
 *  Created on: Aug 15, 2012
 *      Author: Admin
 */

#ifndef MAIN_H_
#define MAIN_H_
#include "common.h"
#include "ymodem.h"
#include "stm32303c_eval.h"

#define SKS_ENABLE_READ_OUT_PROTECTION	1

/* Exported functions ------------------------------------------------------- */
void Int2Str(uint8_t* str,int32_t intnum);
uint32_t Str2Int(uint8_t *inputstr,int32_t *intnum);
uint32_t GetIntegerInput(int32_t * num);
uint32_t SerialKeyPressed(uint8_t *key);
uint8_t GetKey();
void SerialPutChar(uint8_t c);
//void Serial_PutString(uint8_t *s);
//void GetInputString(uint8_t * buffP);
uint32_t FLASH_PagesMask(__IO uint32_t Size);
void FLASH_DisableWriteProtectionPages(uint32_t UserMemMask);
void Main_Menu(void);
void SerialDownload(void);
//void SerialUpload(void);
//void PrintHex(void *data, int len);

//#define SerialPutString(x) Serial_PutString((uint8_t*)(x))
extern SKS_BOOT_INFO boot_inf;

void LedHardwareInit();
#ifdef GPIO_BUZZ_PORT
static inline void BuzzOn() {
	GPIO_SetBits(GPIO_BUZZ_PORT, GPIO_BUZZ_PIN);
}
static inline void BuzzOff() {
	GPIO_ResetBits(GPIO_BUZZ_PORT, GPIO_BUZZ_PIN);
}
#else
	#define BuzzOn()
	#define BuzzOff()
#endif
#ifdef GPIO_GSM_LED_PORT
static inline void LedGSMOn() {
#if USE_STM32_SKS5
	GPIO_ResetBits(GPIO_GSM_LED_PORT, GPIO_GSM_LED_PIN);
#else
	GPIO_SetBits(GPIO_GSM_LED_PORT, GPIO_GSM_LED_PIN);
#endif
}

static inline void LedGSMOff() {
#if USE_STM32_SKS5
	GPIO_SetBits(GPIO_GSM_LED_PORT, GPIO_GSM_LED_PIN);
#else
	GPIO_ResetBits(GPIO_GSM_LED_PORT, GPIO_GSM_LED_PIN);
#endif
}
#else
	#define LedGSMOn()
	#define LedGSMOff()
#endif

#ifdef GPIO_GPS_LED_PORT

static inline void LedGPSOn() {
#if USE_STM32_SKS5
	GPIO_ResetBits(GPIO_GPS_LED_PORT, GPIO_GPS_LED_PIN);
#else
	GPIO_SetBits(GPIO_GPS_LED_PORT, GPIO_GPS_LED_PIN);
#endif
}
static inline void LedGPSOff() {
#if USE_STM32_SKS5
	GPIO_SetBits(GPIO_GPS_LED_PORT, GPIO_GPS_LED_PIN);
#else
	GPIO_ResetBits(GPIO_GPS_LED_PORT, GPIO_GPS_LED_PIN);
#endif
}
#else
	#define LedGPSOn()
	#define LedGPSOff()
#endif
#endif /* MAIN_H_ */
