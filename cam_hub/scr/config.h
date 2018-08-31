//config.h
#ifndef __MATRIX_CNF__
#define __MATRIX_CNF__

#define APP_VERSION "RFID1.0.1.5SS-20150615"

/*
 * Version RFID1.0.1.4SS-20150615:
 * 		- Ban khoi dau, doc the, ghi the, keep alive
 *
 * */

//#define DEBUG_MODE //TODO: remove when release
//#define DEBUG_MATRIX
//#define CUT_REPORT_TIME //TODO: remove when release
//#define REPORT_MAX_SPEED //The hien toc do toi da trong bao cao
//#define PRINT_TOTAL_RECORD

#define ALARM_TIMEOUT 5 //thoi gian canh bao lai xe lien tuc, va trong ngay, tinh theo phut, sau thoi gian se tat canh bao
#define ALARM_RAISE_INTERVAL 10 //thoi gian gian cach giua 2 lan canh bao beep, tinh bang giay
#define NOT_ALLOW_REPORT_WHILE_RUNNING
#define CHECK_SPEED_BY_RANGE

#endif //__MATRIX_CNF__
