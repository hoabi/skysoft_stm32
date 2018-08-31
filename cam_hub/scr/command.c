/*
 * report.c
 *
 *  Created on: Aug 29, 2012
 *      Author: Admin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "command.h"
#include "main.h"
#include "alarm.h"
#include "config.h"
#include "xprintf.h"
#include "Util.h"
//extern unsigned char deviceCodeMajor;
//extern unsigned long deviceCodeMinor;

typedef int (*SKS_CMD_HANDLER)(int from, char* command, int argc, char** argv, int size, int total);

typedef struct _SKS_HANDLER {
	char* cmd;
	SKS_CMD_HANDLER handler;
	unsigned short dis_mask; //Disable handle from source mask
	unsigned short dis_pass; //This command can execute without pass
} SKS_HANDLER;

char *HexChar = "1234567890ABCDEF";
static int response = 0;

void turn_debug(char mark);

void append_int(char* str, uint8_t len, uint32_t val) {
	uint8_t i;
	char *ptr = str + strlen(str);
	for (i = 1; i <= len; i++) {
		ptr[len - i] = (uint8_t) ((val % 10UL) + '0');
		val /= 10;
	}
	ptr[i - 1] = '\0';
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
	//strcat(buff, (char*)g_config.deviceCode);
	return 1;
}

int append_time(char* buff, time_t ti) {
	time_t now = ti;
	struct tm *tm = gmtime(&now);
	char *ptr = buff + strlen(buff);
	append_int(ptr, 4, tm->tm_year + 1900);
	strcat(ptr, "-");
	append_int(ptr, 2, tm->tm_mon + 1);
	strcat(ptr, "-");
	append_int(ptr, 2, tm->tm_mday);
	strcat(ptr, " ");
	append_int(ptr, 2, tm->tm_hour);
	strcat(ptr, ":");
	append_int(ptr, 2, tm->tm_min);
	strcat(ptr, ":");
	append_int(ptr, 2, tm->tm_sec);
	return 1;
}

int append_v9_command(char *buff, char* command) {
	strcat(buff, ",V9,");
	strcat(buff, command);
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

int write_flash = 0;

extern int writeNow;
extern char tagData[68];
static int sks_cmd_write_tag(int from, char* command, int argc, char** argv, int size, int total) {
	//G9, debug setting
	//*XX,YYYYYYYYYY,G7,HHMMSS,S#
	char set = 0;
	if (argv[4] == NULL)
		return size;
	set = atoi(argv[4]);

	append_sign(Response);
	append_v9_command(Response, command);
	strcat(Response, ",");
	append_number(Response, set);
	strcat(Response, ",");
	if(set == 1) {
		memset(tagData, 0, sizeof(tagData));
		if (argv[5] != NULL) {
			int len = (argv[6] - argv[5]) - 1;
			char licenseNo[15] = {0};
			unsigned int crc = 0;
			memccpy(licenseNo, argv[5], 0, len<=15?len:15);
			strcat(Response, licenseNo);
			for(int i=0; i<sizeof(licenseNo); i++) {
				tagData[i] = licenseNo[i];
				crc += licenseNo[i];
			}
			tagData[15] = (crc & 0xFF);
		}

		if (argv[6] != NULL) {
			int len = (argv[7] - argv[6]) - 1;
			char name[43] = {0};
			memccpy(name, argv[6], 0, len<=43?len:43);
			strcat(Response, ",");
			strcat(Response, name);
			unsigned int crc = 0;
			for(int i=0; i<sizeof(name); i++) {
				tagData[i+16] = name[i];
				crc += name[i];
			}
			tagData[59] = (crc & 0xFF);
		}

		if (argv[7] != NULL) {
			int len = (argv[8] - argv[7]) - 1;
			char driverID[5] = {0};
			memccpy(driverID, argv[7], 0, len<=4?len:4);
			strcat(Response, ",");
			strcat(Response, driverID);
			for(int i=0; i<sizeof(driverID); i++) {
				tagData[i+63] = driverID[i];
			}

			xprintf("driverID: %s, %d\r\n", driverID, len);
		}

		tagData[60] = 'S';
		tagData[61] = 'S';
		tagData[62] = atoi(argv[8]);

		xprintf("tag data: %s", tagData);

		writeNow = 1;
	}

	strcat(Response, "#\r\n");

	response = 1;
	return size;
}

static int sks_cmd_v9(int from, char* command, int argc, char** argv, int size, int total) {
	//G9, debug setting
	//*XX,YYYYYYYYYY,G7,HHMMSS,S#
	char set = 0;
	if (argv[4] == NULL)
		return size;
	set = atoi(argv[4]);

	response = 0;
	return size;
}

#if 0
static int sks_cmd_G9(int from, char* command, int argc, char** argv, int size,
		int total) {
	//G9, debug setting
	//*XX,YYYYYYYYYY,G9,HHMMSS,S#
	char set = 0;
	if (argv[4] == NULL)
		return size;
	set = atoi(argv[4]);

	if(set == 0 || set == 1) {
		turn_debug(set);
	} else if(set == 9) { //restart device
		restart_device();
	}

	append_sign(Response);
	append_v9_command(Response, command);
	strcat(Response, ",");
	append_int(Response, 1, set);
	strcat(Response, "#");

	raise_command_coming();

	response = 1;
	return size;
}
#endif

SKS_HANDLER handlers[] = {
		{ "WT", sks_cmd_write_tag }, //get config
		{ "V9", sks_cmd_v9 }, //get config
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
	//sks_log(LOG_INFO, "Process COMMAND size=%d data=%s\r\n", size, data);
	int endPos = 0;
	int i = 0;
	char item_buff[20] = { 0 };
	char* arg[SKS_MAX_ARGV];
	for (i = 0; i < size; i++) {
		if ((data[i] == '#') || (data[i] == '\n') || (data[i] == '\0')) {
			endPos = i + 1;
			break;
		}
	}
	if (endPos == 0)
		return 0; //Waiting for end command sign
	//xprintf("endPos: %d \n\r",endPos);
	for (int i = 0; i < endPos; i++) {

		if ((data[i] == ',') || (data[i] == '\n') || (data[i] == '#')
				|| (data[i] == 0x00)) //complete one item
				{

			//xprintf("field xx :%d,%d,%d\n\r",field,i, endPos);
			if (j > 0) {
				//if (memcmp(ptr, "*SS", 3)==0)

				//xprintf("field 1:%d,%d,%d\n\r",field,i, ptr);

				//if (*(uint32_t*) (ptr) == 0x2C53532A) { //*SS,
				//	xprintf("field = 0");
				//	field = 0;
				//}

				//xprintf("field 2:%d,%d,%d\n\r",field,i, ptr);

				ftmp = field;
				//sks_log(LOG_INFO, "FIELD %d DATA %s", field, item_buff);
				arg[field % SKS_MAX_ARGV] = ptr;
				switch (ftmp) {
				case 0:
					if (*(uint32_t*) (ptr) != 0x2C53532A) {

						return -1; //*SS,
					}
					//if (memcmp(ptr, "*SS", 3)) return -1; //Invalid SIGN
					//field = 0;
					break;
				case 1:
					//sks_log(LOG_INFO, "INVALID DEVID", item_buff);
					//if (memcmp(ptr, g_config.DEVICE_ID, 10)) invalide_code |= 0x1; //Invalid DevID
					break;
				case 2:
					memcpy(command,ptr,j
							< SKS_MAX_CMD_LEN ? j : SKS_MAX_CMD_LEN);
					break;
				case 3:
					//if (memcmp(ptr, g_config.ADMINCODE, 6)) invalide_code |= 0x2; //Invalid AdminCode
					break;
				default:
					//return endPos;
					break;
				}
			}
			//else
			//	arg[field%SKS_MAX_ARGV] = NULL;
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
#if 0
			if (invalide_code)
			{
				//sks_log(LOG_INFO, "COMMAND  invalide_code %s handlers[%d].cmd=%s", command, i, handlers[i].cmd);
				//Allow All command from SKS_CMD_SOURCE_SERIAL
				if (from == SKS_CMD_SOURCE_SERIAL)
				{

				}
				else if(!(handlers[i].dis_pass & from)) return endPos; //Invalid Code
			}
#endif
			//sks_log(LOG_INFO, "COMMAND A %s handlers[%d].cmd=%s", command, i, handlers[i].cmd);
			if (!(handlers[i].dis_mask & from)) //Chi cho phep gui lenh tu nguon
			{
				write_flash = 0;
				//result = handlers[i].handler(from, command, field, arg, endPos-(arg[4]-data), size-(arg[4]-data));
				memset(Response, 0, 200);
				result = handlers[i].handler(from, command, field, arg, endPos,
						size);
				//sks_log(LOG_INFO, "***********===************COMMAND B%s handlers[%d].cmd=%s, total %d result:%d\r\n", command, i, handlers[i].cmd, size, result);
				//if (write_flash)
				//	flash_write_config_info(&g_config);
			}
			break;
		}
		i++;
	}

	if (result > 0) {
		//if (!((result==0)&&(arg[4][0]=='#'))) return 0; //WAITING FOR MORE DATA
		//Make V9 OK Report
		if (response) {
			//msg.ulUpdate = ulSecCount;

			if (from == SKS_CMD_SOURCE_COM1) {
				xprintf(Response);
			} else if (from == SKS_CMD_SOURCE_COM2) {
				//ExtSerial_PutString(Response);
			} else {
			}
			//msg.
			//sks_log(LOG_INFO, "RESPONSE:%s", Response);
		}
		//REQUEST:*SS,YYYYYYYYYY,U2,112233,packid,size#DATA#
		//SIZE=packid,size#
		//TOTALSIZE=packid,size#DATA# =>TOTAL_SIZE>=size+rcv_size+1
		//result += (arg[4]-data);
		//sks_log(LOG_INFO, "SOCKET USE, REMOVE: %d BYTES", result);
	} else if (result < 0) {
		result = endPos;
		//sks_log(LOG_INFO, "REMOVE1: %d BYTES", result);
	}
	return result;
}
