/*
 * HC05.h
 *
 *  Created on: Oct 31, 2017
 *      Author: ThangNguyen
 */

#ifndef HC05_H_
#define HC05_H_
//char USART2_getC(void);
//void USART2_getS(char *S);
int HC05_Get_Connected(void);
void HC05_SendData(char *S);
int HC05_Reset(void);
int HC05_SetName(char *str);
#endif /* HC05_H_ */
