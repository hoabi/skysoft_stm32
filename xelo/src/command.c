/*
 * report.c
 *
 *  Created on: Aug 29, 2012
 *      Author: Admin
 */
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "command.h"
#include <string.h>
#include "xprintf.h"
#include "HC05.h"
/* Private typedef -----------------------------------------------------------*/
typedef int (*SKS_CMD_HANDLER)(int from, char* command, int argc, char** argv,
		int size, int total);
typedef struct _SKS_HANDLER {
	char* cmd;
	SKS_CMD_HANDLER handler;
	unsigned short dis_mask; //Disable handle from source mask
	unsigned short dis_pass; //This command can execute without pass
} SKS_HANDLER;
/* Private variables ---------------------------------------------------------*/
static int response = 0;
const char HexChar[16] = "0123456789ABCDEF";
/* Private function prototypes -----------------------------------------------*/
void CharToHex(const char *str1, char *str2, int len) {
	char temp_buff[256] = { 0 };
	for (int i = 0; i < len / 2; i++) {
		if (str1[i * 2] > 57) {
			temp_buff[i] = (str1[i * 2] - 55) << 4;
		} else {
			temp_buff[i] = (str1[i * 2] - 48) << 4;
		}
		if (str1[i * 2 + 1] > 57) {
			temp_buff[i] += (str1[i * 2 + 1] - 55);
		} else {
			temp_buff[i] += (str1[i * 2 + 1] - 48);
		}

	}
	memccpy(str2, temp_buff, 0, strlen(temp_buff));
}
void HexToChar(const char *str1, char *str2, int len) {
	char temp_buff[64] = { 0 };
	for (int i = 0; i < len; i++) {
		temp_buff[i * 2] = (HexChar[str1[i] >> 4]);
		temp_buff[i * 2 + 1] = (HexChar[str1[i] & 0x0F]);
	}
	memccpy(str2, temp_buff, 0, strlen(temp_buff));
}
void append_int(char* str, uint8_t len, uint32_t val) {
	uint8_t i;
	char *ptr = str + strlen(str);
	for (i = 1; i <= len; i++) {
		ptr[len - i] = (uint8_t) ((val % 10UL) + '0');
		val /= 10;
	}
	ptr[i - 1] = '\0';
}
void append_char(char *str, char val) {
	char *ptr = str + strlen(str);
	*ptr = val;
}
void append_hex(char* str, uint8_t val) {
	char *ptr = str + strlen(str);
	ptr[0] = HexChar[val >> 4];
	ptr[1] = HexChar[val & 0xF];
	ptr[2] = 0;
}

void append_hex_long(char* str, long val) {
	char *ptr = str + strlen(str);
	ptr[0] = HexChar[val >> 28];
	ptr[1] = HexChar[(val >> 24) & 0xF];
	ptr[2] = HexChar[(val >> 20) & 0xF];
	ptr[3] = HexChar[(val >> 16) & 0xF];
	ptr[4] = HexChar[(val >> 12) & 0xF];
	ptr[5] = HexChar[(val >> 8) & 0xF];
	ptr[6] = HexChar[(val >> 4) & 0xF];
	ptr[7] = HexChar[val & 0xF];
	ptr[8] = 0x0;
}
int append_sign(char* buff) {
	strcpy(buff, "*SS,");
	return 1;
}
int next_char(char* data, char sep, int max) {
	char *ptr = strchr(data, sep);
	if (ptr) {
		return (ptr - data) >= max ? max : (ptr - data);
	} else {
		return 0;
	}
}

static char Response[256];
void create_v3(int blockno) {
	append_sign(Response);
	strcat(Response, ",V3,");
	if (blockno >= 10000) {
		append_int(Response, 5, blockno);
	} else if (blockno >= 1000) {
		append_int(Response, 4, blockno);
	} else if (blockno >= 100) {
		append_int(Response, 3, blockno);
	} else if (blockno >= 10) {
		append_int(Response, 2, blockno);
	} else {
		append_int(Response, 1, blockno);
	}
}
//BLE01
static int sks_cmd_Set_PassWord(int from, char* command, int argc, char** argv,
		int size, int total) {
	char temp_buff[64] = { 0 };
	xprintf("sks_cmd_Set_PassWord\n\r");
	char set = 0;
	if (argv[4] == NULL)
		return size;
	set = atoi(argv[4]);
	if (set == 1) {
		if (argv[5] != NULL) {
			int len = (argv[6] - argv[5]) - 1;
			memccpy(temp_buff, argv[5], 0, len);
		}
	}
	return 0;
}
//BLE02
static int sks_cmd_Renane(int from, char* command, int argc, char** argv,
		int size, int total) {
	char temp_buff[64] = { 0 };
	//xprintf("sks_cmd_Rename\n\r");
	char set = 0;
	if (argv[4] == NULL)
		return size;
	set = atoi(argv[4]);
	if (set == 1) {
		if (argv[5] != NULL) {
			int len = (argv[6] - argv[5]) - 1;
			memccpy(temp_buff, argv[5], 0, len);
			//xprintf("%s\n\r", temp_buff);
			if (HC05_SetName(temp_buff) == 1)
				xprintf("successful\r\n");
			else
				xprintf("fail\r\n");
		}
	}
	return 0;
}
//BLE03
static int sks_cmd_Reset_Defautl(int from, char* command, int argc, char** argv,
		int size, int total) {
	xprintf("sks_cmd_Reset_Default\n\r");
	//memset(buff_cmd, 0, sizeof(buff_cmd));
	return 0;
}
SKS_HANDLER handlers[] = { { "BLE01", sks_cmd_Set_PassWord }, //set password
		{ "BLE02", sks_cmd_Renane }, //set name
		{ "BLE03", sks_cmd_Reset_Defautl }, //set default
		{ NULL, NULL } };

int server_on_command(int from, char * data, int size) {
#define SKS_MAX_CMD_LEN 10
#define SKS_MAX_ARGV 	25
	int result = 0;
	int field = 0;
	int ftmp;
	int j = 0;
	char *ptr = data;
	//char invalide_code = 0;
	char command[SKS_MAX_CMD_LEN + 1] = { 0 };
	//*XX,YYYYYYYYYY,CMD,VVVVVV,PARA1,PARA2,…#
	int endPos = 0;
	int i = 0;
	char item_buff[20] = { 0 };
	char* arg[SKS_MAX_ARGV];
	for (i = 0; i < size; i++) {
		if ((data[i] == '#') || (data[i] == '\n') || (data[i] == '\0')) {
			//xprintf("jump here");
			endPos = i + 1;
			break;
		}
	}
	if (endPos == 0)
		return 0; //Waiting for end command sign

	for (int i = 0; i < endPos; i++) {
		if ((data[i] == ',') || (data[i] == '\n') || (data[i] == '#')
				|| (data[i] == 0x00)) //complete one item
				{
			if (j > 0) {
				if (*(uint32_t*) (ptr) == 0x2C53532A) //*SS,
						{
					field = 0;
				}
				ftmp = field;
				arg[field % SKS_MAX_ARGV] = ptr;
				switch (ftmp) {
				case 0:

					if (*(uint32_t*) (ptr) != 0x2C53532A)
						return -1; //*SS,
					break;
				case 1:
					break;
				case 2:
					memcpy(command, ptr,
							j < SKS_MAX_CMD_LEN ? j : SKS_MAX_CMD_LEN);
					break;
				case 3:
					break;
				default:
					break;
				}

			}
			field++;
			if (field >= SKS_MAX_ARGV)
				break;
			j = 0; //reset index
			ptr = data + i + 1;
			arg[field % SKS_MAX_ARGV] = ptr;
		} else {
			item_buff[j % sizeof(item_buff)] = data[i];
			j++;
			item_buff[j] = 0x00;
		}
	}
	if (field > SKS_MAX_ARGV)
		return endPos; //Too many param
	if (field <= 3)
		return endPos; //Too few param

	i = 0;
	result = -1;
	response = 0;
	while (handlers[i].cmd) {
		if (strcmp(command, handlers[i].cmd) == 0) {
			if (!(handlers[i].dis_mask & from)) //Chi cho phep gui lenh tu nguon
			{
				memset(Response, 0, 200);
				result = handlers[i].handler(from, command, field, arg, endPos,
						size);
			}
			break;
		}
		i++;
	}

	if (result > 0) {
		if (response) {
			if (from == SKS_CMD_SOURCE_COM1) {
				xprintf(Response);
			} else if (from == SKS_CMD_SOURCE_COM2) {
			} else {
			}
		}
	} else if (result < 0) {
		result = endPos;
	}
	return result;
}
