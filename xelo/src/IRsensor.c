/*
 * IRsensor.c
 *
 *  Created on: Dec 6, 2017
 *      Author: ThangNguyen
 */
#include <IRsensor.h>
void TurnOffLed(void) {
	LED1_off;
	LED2_off;
	LED3_off;
	LED4_off;
}
int Check_Unuse_IRsesor(void) {
	int val = 0;
	val = val & 0x00;
	if (GPIO_ReadInputDataBit(UnUse1_port, UnUse1_pin)) {
		val += 1;
	}
	if (GPIO_ReadInputDataBit(UnUse2_port, UnUse2_pin)) {
		val += 2;
	}
	if (GPIO_ReadInputDataBit(UnUse3_port, UnUse3_pin)) {
		val += 4;
	}
	if (GPIO_ReadInputDataBit(UnUse4_port, UnUse4_pin)) {
		val += 8;
	}
}

