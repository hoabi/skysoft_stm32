/*
 * mainboot.c
 *
 *  Created on: Aug 15, 2012
 *      Author: Admin
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "command.h"
#include "xprintf.h"
#include <string.h>
#include "HC05.h"
#include <stm32f10x_rtc.h>
#include <time.h>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile extern uint32_t MiliCount;
volatile extern unsigned long ulTick100;
unsigned long lastSentToTracker = 0;
unsigned long CraskCheck = 0;
unsigned long nextStepSchedule = 0;
char buff_cmd[256] = { 0 };
char BLE_buff[256] = { 0 };
char data[64] = { 0 };
extern uint32_t CLK_count;
extern int PPS;
static void process_command_from_pc(void) {
	if (buff_cmd[0] == '*') {
		server_on_command(SKS_CMD_SOURCE_COM1, buff_cmd, sizeof(buff_cmd));
		buff_cmd[0] = 0;
	}
}
/*static void process_command_from_Blueooth(void) {
 if (buff_cmd[0] == '*') {
 server_on_command(SKS_CMD_SOURCE_COM2, buff_cmd, sizeof(buff_cmd));
 buff_cmd[0] = 0;
 }
 }*/
int taxi_cal(void) {
	int distane = 0;
	distane = (int) CLK_count * 100 / 2560;
	return distane;
}
void process_data(void) {
	int v = 0;
	v = PPS * 36000 / 2560;
	memset(data, 0, sizeof(data));
	usnprintf(data, 43, "*SS,0000000001,BLE,123123,1,%d,%d,%d#\r\n", taxi_cal(),
			PPS * 36000 / 2560, CLK_count);
}

/**
 * @brief  Returns the time entered by user, using Hyperterminal.
 * @param  None
 * @retval Current time RTC counter value
 */
uint32_t Time_Regulate(void) {
	uint32_t Tmp_HH = 11, Tmp_MM = 11, Tmp_SS = 11;
	return ((Tmp_HH * 3600 + Tmp_MM * 60 + Tmp_SS));
}

/**
 * @brief  Adjusts time.
 * @param  None
 * @retval None
 */
void Time_Adjust(void) {
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
	/* Change the current time */
	RTC_SetCounter(Time_Regulate());
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
}

/**
 * @brief  Displays the current time.
 * @param  TimeVar: RTC counter value.
 * @retval None
 */
void Time_Display(uint32_t TimeVar) {
	//uint32_t THH = 0, TMM = 0, TSS = 0;
	time_t epoch = 0;
	epoch = RTC_GetCounter();
	xprintf("%s\n\r", asctime(localtime(&epoch)));
}

/**
 * @brief  Shows the current time (HH:MM:SS) on the Hyperterminal.
 * @param  None
 * @retval None
 */
void Time_Show(void) {
	/*	printf("\n\r");

	 Infinite loop
	 while (1) {
	 If 1s has been elapsed
	 if (TimeDisplay == 1) {
	 Display current time
	 Time_Display(RTC_GetCounter());
	 TimeDisplay = 0;
	 }
	 }*/
}
void RTC_Configuration(void) {
	/* Enable PWR and BKP clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);

	/* Reset Backup Domain */
	BKP_DeInit();

	/* Enable LSE */
	RCC_LSEConfig(RCC_LSE_ON);
	/* Wait till LSE is ready */
	//xprintf("gohere1\n\r");
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET) {

	}
	//xprintf("gohere2\n\r");
	/* Select LSE as RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

	/* Enable RTC Clock */
	RCC_RTCCLKCmd(ENABLE);

	/* Wait for RTC registers synchronization */
	RTC_WaitForSynchro();

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();

	/* Enable the RTC Second */
	//RTC_ITConfig(RTC_IT_SEC, ENABLE);
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();

	/* Set RTC prescaler: set RTC period to 1sec */
	RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
}
void set_time_RTC(void) {
	time_t ret;
	struct tm info;

	info.tm_year = 2017 - 1900;
	info.tm_mon = 12 - 1;
	info.tm_mday = 19;
	info.tm_hour = 9;
	info.tm_min = 45;
	info.tm_sec = 0;
	info.tm_isdst = -1;

	ret = mktime(&info);
	if (ret == -1) {
		xprintf("Error: unable to make time using mktime\n");
	} else {
		/* Wait until last write operation on RTC registers has finished */
		RTC_WaitForLastTask();
		/* Change the current time */
		RTC_SetCounter(ret);
		/* Wait until last write operation on RTC registers has finished */
		RTC_WaitForLastTask();
	}
}
void Main_Menu(void) {
	int vx;
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A6) {
		/* Backup data register value is not correct or not yet programmed (when
		 the first time the program is executed) */

		xprintf("\r\n\n RTC not yet configured....");

		/* RTC Configuration */
		RTC_Configuration();

		xprintf("\r\n RTC configured....");

		/* Adjust time by values entered by the user on the hyperterminal */
		//Time_Adjust();
		set_time_RTC();
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A6);
	} else {
		/* Check if the Power On Reset flag is set */
		if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET) {
			xprintf("\r\n\n Power On Reset occurred....");
		}
		/* Check if the Pin Reset flag is set */
		else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET) {
			xprintf("\r\n\n External Reset occurred....");
		}

		xprintf("\r\n No need to configure RTC....");
		/* Wait for RTC registers synchronization */
		RTC_WaitForSynchro();

		/* Enable the RTC Second */
		RTC_ITConfig(RTC_IT_SEC, ENABLE);
		/* Wait until last write operation on RTC registers has finished */
		RTC_WaitForLastTask();
	}
	RCC_ClearFlag();
	while (1) {
		process_command_from_pc();
		if (lastSentToTracker < MiliCount) {
			process_data();
			HC05_SendData(data);
			xprintf("%d,%d,%d,%d\n\r", taxi_cal(), PPS, CLK_count,
					PPS * 36000 / 2560);
			Time_Display(RTC_GetCounter());
			lastSentToTracker = MiliCount + 1000;
		}

	}
}
