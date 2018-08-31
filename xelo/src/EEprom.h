/*
 * EEprom.h
 *
 *  Created on: Feb 16, 2017
 *      Author: ThangNguyen
 */

#ifndef EEPROM_H_
#define EEPROM_H_
#include <stm32f10x_flash.h>
/*

 */
#define FLASH_PAGE_SIZE    ((uint16_t)0x400)
#define BANK1_WRITE_START_ADDR  ((uint32_t)0x0800f800)
#define BANK1_WRITE_END_ADDR    ((uint32_t)0x0800ffff)
//uint32_t PageCount = 0x00;

void FlashInit(void);
void flash_wrire_char(char c);
char flash_read_char(uint32_t add);
void flash_write_config(uint32_t add, char *data, int len);
char flash_read_config(uint32_t add, char *buff, int len);
#endif /* EEPROM_H_ */
