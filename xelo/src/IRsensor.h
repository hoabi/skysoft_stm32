/*
 * IRsensor.h
 *
 *  Created on: Dec 4, 2017
 *      Author: ThangNguyen
 */

#ifndef IRSENSOR_H_
#define IRSENSOR_H_
#include <stm32f10x_gpio.h>
#define IR_Rx1_pin		GPIO_Pin_0
#define IR_Rx1_port		GPIOA
#define IR_Rx2_pin		GPIO_Pin_4
#define IR_Rx2_port		GPIOA
#define IR_Rx3_pin		GPIO_Pin_4
#define IR_Rx3_port		GPIOC
#define IR_Rx4_pin		GPIO_Pin_2
#define IR_Rx4_port		GPIOB
#define UnUse1_pin		GPIO_Pin_1
#define UnUse1_port		GPIOA
#define UnUse2_pin		GPIO_Pin_5
#define UnUse2_port		GPIOA
#define UnUse3_pin		GPIO_Pin_5
#define UnUse3_port		GPIOC
#define UnUse4_pin		GPIO_Pin_10
#define UnUse4_port		GPIOB
#define IR_Tx1_pin		GPIO_Pin_2
#define IR_Tx1_port		GPIOA
#define IR_Tx2_pin		GPIO_Pin_6
#define IR_Tx2_port		GPIOA
#define IR_Tx3_pin		GPIO_Pin_0
#define IR_Tx3_port		GPIOB
#define IR_Tx4_pin		GPIO_Pin_11
#define IR_Tx4_port		GPIOB
#define LED1_pin		GPIO_Pin_3
#define LED1_port		GPIOA
#define LED2_pin		GPIO_Pin_7
#define LED2_port		GPIOA
#define LED3_pin		GPIO_Pin_1
#define LED3_port		GPIOB
#define LED4_pin		GPIO_Pin_12
#define LED4_port		GPIOB
#define LED1_on			GPIO_SetBits(LED1_port, LED1_pin)
#define LED1_off		GPIO_ResetBits(LED1_port, LED1_pin)
#define LED2_on			GPIO_SetBits(LED2_port, LED2_pin)
#define LED2_off		GPIO_ResetBits(LED2_port, LED2_pin)
#define LED3_on			GPIO_SetBits(LED3_port, LED3_pin)
#define LED3_off		GPIO_ResetBits(LED3_port, LED3_pin)
#define LED4_on			GPIO_SetBits(LED4_port, LED4_pin)
#define LED4_off		GPIO_ResetBits(LED4_port, LED4_pin)
void TurnOffLed(void);
int Check_Unuse_IRsesor(void);

#endif /* IRSENSOR_H_ */
