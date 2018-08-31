/*
 * report.h
 *
 *  Created on: Aug 29, 2012
 *      Author: Admin
 */

#ifndef __COMMAND_H_
#define __COMMAND_H_

#define SKS_CMD_SOURCE_COM1 1//form pc usart1
#define SKS_CMD_SOURCE_COM2 2// from bluetooth usart2
#include <stdint.h>
void append_int(char* str, uint8_t len, uint32_t val);
int server_on_command(int from, char * data, int size);

#endif /* __COMMAND_H_ */
