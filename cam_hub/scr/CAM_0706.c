/*
 * CAM_0706.c
 *
 *  Created on: May 14, 2018
 *      Author: ThangNguyen
 */
#include <stm32f0xx_usart.h>
#include "CAM_0706.h"
extern void USARTxPutChar(USART_TypeDef * USARTx, uint8_t c);
int CAM_0706_Reset(USART_TypeDef * USARTx) {
	USARTxPutChar(USARTx, 0x56);
	USARTxPutChar(USARTx, 0x00);
	USARTxPutChar(USARTx, 0x26);
	USARTxPutChar(USARTx, 0x00);
	return 0;
}
int CAM_0706_TakePicture(USART_TypeDef * USARTx) {
	USARTxPutChar(USARTx, 0x56);
	USARTxPutChar(USARTx, 0x00);
	USARTxPutChar(USARTx, 0x36);
	USARTxPutChar(USARTx, 0x01);
	USARTxPutChar(USARTx, 0x00);
	return 0;
}
int CAM_0706_ReadFlieSize(USART_TypeDef * USARTx) {
	USARTxPutChar(USARTx, 0x56);
	USARTxPutChar(USARTx, 0x00);
	USARTxPutChar(USARTx, 0x34);
	USARTxPutChar(USARTx, 0x01);
	USARTxPutChar(USARTx, 0x00);
	return 0;
}
int CAM_0706_StopTakePicture(USART_TypeDef * USARTx) {
	USARTxPutChar(USARTx, 0x56);
	USARTxPutChar(USARTx, 0x00);
	USARTxPutChar(USARTx, 0x36);
	USARTxPutChar(USARTx, 0x01);
	USARTxPutChar(USARTx, 0x03);
	return 0;
}
int CAM_0706_CompressionRatio(USART_TypeDef * USARTx, int xx) {
	USARTxPutChar(USARTx, 0x56);
	USARTxPutChar(USARTx, 0x00);
	USARTxPutChar(USARTx, 0x31);
	USARTxPutChar(USARTx, 0x05);
	USARTxPutChar(USARTx, 0x01);
	USARTxPutChar(USARTx, 0x01);
	USARTxPutChar(USARTx, 0x12);
	USARTxPutChar(USARTx, 0x04);
	USARTxPutChar(USARTx, xx);
	return 0;
}
int CAM_0706_ReadPictureContent(USART_TypeDef * USARTx) {
	USARTxPutChar(USARTx, 0x56);
	USARTxPutChar(USARTx, 0x00);
	USARTxPutChar(USARTx, 0x31);
	USARTxPutChar(USARTx, 0x05);
	USARTxPutChar(USARTx, 0x01);
	USARTxPutChar(USARTx, 0x01);
	USARTxPutChar(USARTx, 0x12);
	USARTxPutChar(USARTx, 0x04);
	return 0;
}
