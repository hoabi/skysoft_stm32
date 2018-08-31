/*
 * delay.c
 *
 *  Created on: Feb 14, 2017
 *      Author: ThangNguyen
 */
void delay_us(unsigned int time_us) {
	unsigned int i;
	unsigned char j;
	for (i = 0; i < time_us; i++) {
		for (j = 0; j < 7; j++)
			;
	}
}
void delay_ms(unsigned int time_ms) {
	unsigned int i;
	for (i = 0; i < time_ms; i++) {
		delay_us(900);
	}
}

