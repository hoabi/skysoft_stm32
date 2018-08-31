/*
 * EEprom.c
 *
 *  Created on: Feb 16, 2017
 *      Author: ThangNguyen
 */
#include "EEprom.h"
#include <string.h>
#include "xprintf.h"
volatile FLASH_Status FLASHStatus = FLASH_TIMEOUT;
void FlashInit(void) {
	FLASH_UnlockBank1();
	/*	PageCount = (BANK1_WRITE_END_ADDR - BANK1_WRITE_START_ADDR)
	 / FLASH_PAGE_SIZE;*/
}
void flash_wrire_char(char c) {
	FLASH_UnlockBank1();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	FLASH_ErasePage(BANK1_WRITE_START_ADDR);
	{
		FLASH_ProgramHalfWord(BANK1_WRITE_START_ADDR, c);
	}
}
char flash_read_char(uint32_t add) {
	return (*(char*) add);
}
void flash_write_config(uint32_t add, char *data, int len) {
	FLASH_UnlockBank1();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	FLASH_ErasePage(BANK1_WRITE_START_ADDR);
	for (int i = 0; i < len; i++) {
		FLASH_ProgramWord(add + i * 4, *data);
		data++;
	}
}
char flash_read_config(uint32_t add, char *buff, int len) {
	char tempbuff[128] = { 0 };
	memset(tempbuff, 0, sizeof(tempbuff));
	for (int i = 0; i < len; i++) {
		tempbuff[i] = flash_read_char(add + i * 4);
	}
	strcpy(buff, tempbuff);
	return 0;
}
