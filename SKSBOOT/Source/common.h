/**
  ******************************************************************************
  * @file    IAP/inc/common.h
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    10/15/2010
  * @brief   This file provides all the headers of the common functions.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _COMMON_H
#define _COMMON_H

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "string.h"
#include "stm32f30x.h"

#define UBOOT_VERSION 0x1004

/* Exported types ------------------------------------------------------------*/
typedef  void (*pFunction)(void);

/* Exported constants --------------------------------------------------------*/
/* Constants used by Serial Command Line Mode */
#define CMD_STRING_SIZE       128

//#define ApplicationAddress    0x8008000 //32KB
//#define ApplicationAddress    0x800C000 //48KB

#if defined (STM32F10X_MD) || defined (STM32F10X_MD_VL)
 #define PAGE_SIZE                         (0x400)    /* 1 Kbyte */
 #define FLASH_SIZE                        (0x20000)  /* 128 KBytes */
#elif defined STM32F10X_CL
 #define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
 #define FLASH_SIZE                        (0x40000)  /* 256 KBytes */
#elif defined STM32F303xE
#define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
#define FLASH_SIZE                        (0x80000)  /* 512 KBytes */
// #define FLASH_SIZE                        (0x40000)  /* 256 KBytes */
#elif defined STM32F10X_XL
 #define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
 #define FLASH_SIZE                        (0x100000) /* 1 MByte */
#else 
 #error "Please select first the STM32 device to be used (in stm32f10x.h)"
#endif

//#define USE_STM32_SKS5 1
//#define NULL_BOX_512	1
//#define NULL_BOX_256	1
//#define VNET_BOX_256	1
//#define HLAB_BOX	1
//#define CNS1_BOX	1
//#define CNS3_BOX	1
//#define BA1_BOX	1
//#define BA3_BOX	1
//#define TAXI_BOX	1
//#define RFID_BOX	1

//#define PUBLIC_VERSION 0x4

 //PORT B: PIN 12 BEEP
 //PORT E: PIN 8: LED 1 (GREEN /GPS) / PIN 10: LED 2 (RED/GSM)

#if NULL_BOX_512						//NULLBOX
	#define PAGE_SIZE               (0x800)    /* 2 Kbytes */
	#define FLASH_SIZE              (0x80000)  /* 512 KBytes */
	#define USE_USART				1

//	#define RCC_GPIO_BUZZ 				RCC_APB2Periph_GPIOE
//	#define GPIO_BUZZ_PORT   			GPIOE
//	#define GPIO_BUZZ_PIN 				GPIO_Pin_4
//
//	#define RCC_GPIO_GSM_LED	RCC_APB2Periph_GPIOD
//	#define GPIO_GSM_LED_PORT   GPIOD
//	#define GPIO_GSM_LED_PIN 	GPIO_Pin_8
//
//	#define RCC_GPIO_GPS_LED	RCC_APB2Periph_GPIOD
//	#define GPIO_GPS_LED_PORT   GPIOD
//	#define GPIO_GPS_LED_PIN 	GPIO_Pin_9

#elif NULL_BOX_256 //
	#define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
	#define FLASH_SIZE                        (0x40000)  /* 512 KBytes */
#elif VNET_BOX_256
	#define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
	#define FLASH_SIZE                        (0x40000)  /* 512 KBytes */

	#define RCC_GPIO_BUZZ 				RCC_APB2Periph_GPIOD
	#define GPIO_BUZZ_PORT   			GPIOD
	#define GPIO_BUZZ_PIN 				GPIO_Pin_11

	//#define RCC_GPIOLed RCC_APB2Periph_GPIOE
//	#define RCC_GPIO_LED		RCC_APB2Periph_GPIOB
//	#define GPIO_LED_PORT   	GPIOB
	#define RCC_GPIO_GSM_LED	RCC_APB2Periph_GPIOE

	#define GPIO_GSM_LED_PORT   GPIOE
	#define GPIO_GSM_LED_PIN 	GPIO_Pin_11

	#define GPIO_GPS_LED_PORT   GPIOE
	#define GPIO_GPS_LED_PIN 	GPIO_Pin_10

	//SKYBOX
	//#define GPIO_WATCHDOG_PORT    	GPIOB
	//#define GPIO_WATCHDOG_PIN		GPIO_Pin_8
#elif HLAB_BOX
	#define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
	#define FLASH_SIZE                        (0x40000)  /* 512 KBytes */

	#define RCC_GPIO_BUZZ 				RCC_APB2Periph_GPIOA
	#define GPIO_BUZZ_PORT   			GPIOA
	#define GPIO_BUZZ_PIN 				GPIO_Pin_8

	//#define RCC_GPIOLed RCC_APB2Periph_GPIOE
	#define RCC_GPIO_LED		RCC_APB2Periph_GPIOB
	#define GPIO_LED_PORT   	GPIOB
	#define GPIO_GSM_LED_PORT   GPIOB
	#define GPIO_GSM_LED_PIN 	GPIO_Pin_0

	#define GPIO_GPS_LED_PORT   GPIOB
	#define GPIO_GPS_LED_PIN 	GPIO_Pin_1

	//SKYBOX
	//#define GPIO_WATCHDOG_PORT    	GPIOB
	//#define GPIO_WATCHDOG_PIN		GPIO_Pin_8
#elif RFID_BOX
	#define PAGE_SIZE                         (0x400)    /* 1 Kbytes */
	#define FLASH_SIZE                        (0x8000)  /* 32 KBytes */
#elif TAXI_BOX //TAXIBOX

	#define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
	#define FLASH_SIZE                        (0x80000)  /* 512 KBytes */
	#define RCC_GPIO_BUZZ 				RCC_APB2Periph_GPIOB
	#define GPIO_BUZZ_PORT   			GPIOB
	#define GPIO_BUZZ_PIN 				GPIO_Pin_9

	//#define RCC_GPIOLed RCC_APB2Periph_GPIOE
	#define RCC_GPIO_LED		RCC_APB2Periph_GPIOE
	#define GPIO_LED_PORT   	GPIOE
	#define GPIO_GSM_LED_PORT   GPIOE
	#define GPIO_GSM_LED_PIN 	GPIO_Pin_13

	#define GPIO_GPS_LED_PORT   GPIOE
	#define GPIO_GPS_LED_PIN 	GPIO_Pin_14

	#define GPIO_WATCHDOG_PORT    	GPIOC
	#define GPIO_WATCHDOG_PIN		GPIO_Pin_5
#elif CNS1_BOX	// CNS1
	#define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
	#define FLASH_SIZE                        (0x80000)  /* 512 KBytes */

	#define RCC_GPIO_BUZZ 		RCC_APB2Periph_GPIOB
	#define GPIO_BUZZ_PORT   	GPIOB
	#define GPIO_BUZZ_PIN 		GPIO_Pin_12

	#define RCC_GPIO_GSM_LED 	RCC_APB2Periph_GPIOE
	#define GPIO_GSM_LED_PORT   GPIOE
	#define GPIO_GSM_LED_PIN 	GPIO_Pin_8

	#define RCC_GPIO_GPS_LED 	RCC_APB2Periph_GPIOE
	#define GPIO_GPS_LED_PORT   GPIOE
	#define GPIO_GPS_LED_PIN 	GPIO_Pin_10

	#define GPIO_WATCHDOG_PORT    	GPIOB
	#define GPIO_WATCHDOG_PIN		GPIO_Pin_8
#elif BA1_BOX	// BA1 //not checked LED pins yet
	#define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
	#define FLASH_SIZE                        (0x80000)  /* 512 KBytes */

	#define RCC_GPIO_BUZZ 		RCC_APB2Periph_GPIOB
	#define GPIO_BUZZ_PORT   	GPIOB
	#define GPIO_BUZZ_PIN 		GPIO_Pin_12

	#define RCC_GPIO_GSM_LED 	RCC_APB2Periph_GPIOE
	#define GPIO_GSM_LED_PORT   GPIOE
	#define GPIO_GSM_LED_PIN 	GPIO_Pin_8

	#define RCC_GPIO_GPS_LED 	RCC_APB2Periph_GPIOE
	#define GPIO_GPS_LED_PORT   GPIOE
	#define GPIO_GPS_LED_PIN 	GPIO_Pin_10

	#define GPIO_WATCHDOG_PORT    	GPIOB
	#define GPIO_WATCHDOG_PIN		GPIO_Pin_8
#elif BA3_BOX //not checked LED pin yet
	#define PAGE_SIZE          (0x800)    /* 2 Kbytes */
	#define FLASH_SIZE         (0x80000)  /* 512 KBytes */

	#define RCC_GPIO_BUZZ 		RCC_APB2Periph_GPIOB
	#define GPIO_BUZZ_PORT   	GPIOB
	#define GPIO_BUZZ_PIN 		GPIO_Pin_12

	#define RCC_GPIO_GSM_LED 	RCC_APB2Periph_GPIOE
	#define GPIO_GSM_LED_PORT   GPIOE
	#define GPIO_GSM_LED_PIN 	GPIO_Pin_8

	#define RCC_GPIO_GPS_LED 	RCC_APB2Periph_GPIOE
	#define GPIO_GPS_LED_PORT   GPIOE
	#define GPIO_GPS_LED_PIN 	GPIO_Pin_10

	#define GPIO_WATCHDOG_PORT    	GPIOB
	#define GPIO_WATCHDOG_PIN		GPIO_Pin_8
#elif CNS3_BOX
	#define PAGE_SIZE           (0x800)    /* 2 Kbytes */
	#define FLASH_SIZE          (0x80000)  /* 512 KBytes */

	#define RCC_GPIO_BUZZ 		RCC_APB2Periph_GPIOC
	#define GPIO_BUZZ_PORT   	GPIOC
	#define GPIO_BUZZ_PIN 		GPIO_Pin_6

	#define RCC_GPIO_GSM_LED 	RCC_APB2Periph_GPIOA
	#define GPIO_GSM_LED_PORT   GPIOA
	#define GPIO_GSM_LED_PIN 	GPIO_Pin_15

	#define RCC_GPIO_GPS_LED 	RCC_APB2Periph_GPIOD
	#define GPIO_GPS_LED_PORT   GPIOD
	#define GPIO_GPS_LED_PIN 	GPIO_Pin_15

	#define GPIO_WATCHDOG_PORT  GPIOB
	#define GPIO_WATCHDOG_PIN	GPIO_Pin_8
#else	//Default, SKYBOX
//	#define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
//	#define FLASH_SIZE                        (0x80000)  /* 512 KBytes */

	#define RCC_GPIO_BUZZ 				RCC_AHBPeriph_GPIOE
	#define GPIO_BUZZ_PORT   			GPIOE
	#define GPIO_BUZZ_PIN 				GPIO_Pin_4

	#define RCC_GPIO_GSM_LED	RCC_AHBPeriph_GPIOD
	#define GPIO_GSM_LED_PORT   GPIOD
	#define GPIO_GSM_LED_PIN 	GPIO_Pin_8

	#define RCC_GPIO_GPS_LED	RCC_AHBPeriph_GPIOD
	#define GPIO_GPS_LED_PORT   GPIOD
	#define GPIO_GPS_LED_PIN 	GPIO_Pin_9

	//SKYBOX
	#define GPIO_WATCHDOG_PORT    	GPIOB
	#define GPIO_WATCHDOG_PIN		GPIO_Pin_8
#endif

#if (FLASH_SIZE==0x80000)
	#define UBOOT_CONFIG_ADDRESS    		((FLASH_SIZE-PAGE_SIZE)+0x8000000)//0x807F800  //Page 255
	#define BOOT_PRIMARY_ADDRESS    		ApplicationAddress							  //Page 255
#if (UBOOT_VERSION <= 0x1003)
	#define BOOT_IMAGE_PAGES	    		64  //128KB - 2KB/page
	#define FLASH_IMAGE_SIZE                (uint32_t)(BOOT_IMAGE_PAGES*PAGE_SIZE)
	#define BOOT_SECONDARY_ADDRESS    		(ApplicationAddress+BOOT_IMAGE_PAGES*PAGE_SIZE)  //Page 255
#else
	#define BOOT_SECONDARY_ADDRESS    		(0x8000000+110*PAGE_SIZE)  //Page 110 (10+100+100+44+1+1)
#endif
	//REPORT: PAGE 138
	#define APP_CONFIG_ADDRESS    			((FLASH_SIZE-PAGE_SIZE*2)+0x8000000)//0x807F800  //Page 255
	#if !PUBLIC_VERSION
		#define ApplicationAddress    			0x8005000  //20KB
	#else
		#define ApplicationAddress    			0x8004000  //20KB
	#endif

#elif (FLASH_SIZE==0x40000)
	#define UBOOT_CONFIG_ADDRESS    		((FLASH_SIZE-PAGE_SIZE)+0x8000000)//0x803F800  //Page 128

	#define BOOT_PRIMARY_ADDRESS    		ApplicationAddress							  //Page 255
	#define BOOT_SECONDARY_ADDRESS    		(ApplicationAddress+BOOT_IMAGE_PAGES*PAGE_SIZE)  //Page 255
	#define FLASH_IMAGE_SIZE                (uint32_t)(BOOT_IMAGE_PAGES*PAGE_SIZE)
	//REPORT: PAGE 138
	#define APP_CONFIG_ADDRESS    			((FLASH_SIZE-PAGE_SIZE*2)+0x8000000)//0x803F000  //Page 127
	//#define ApplicationAddress    			0x8005000  //20KB
	//#define BOOT_IMAGE_PAGES	    		58  //104KB - 2KB/page (256 - 20k boot - 2K config -2k app config )
	#define ApplicationAddress    			0x8003000  //10KB  (16K => BOOT_IMAGE_PAGES=52)
	#define BOOT_IMAGE_PAGES	    		54  //108KB - 2KB/page (256K -( 12k boot + 2K config + 2k app config + 10/12k pointer))
#elif (FLASH_SIZE==0x8000) //RFID
	#define UBOOT_CONFIG_ADDRESS    		((FLASH_SIZE-PAGE_SIZE)+0x8000000)//0x803F800  //Page 128

	#define BOOT_PRIMARY_ADDRESS    		ApplicationAddress							  //Page 255
	#define BOOT_SECONDARY_ADDRESS    		(ApplicationAddress+BOOT_IMAGE_PAGES*PAGE_SIZE)  //Page 255
	#define FLASH_IMAGE_SIZE                (uint32_t)(BOOT_IMAGE_PAGES*PAGE_SIZE)
	#define APP_CONFIG_ADDRESS    			((FLASH_SIZE-PAGE_SIZE*2)+0x8000000)//0x803F000  //Page 127
	#define ApplicationAddress    			0x8003000  //10KB  (16K => BOOT_IMAGE_PAGES=52)
	#define BOOT_IMAGE_PAGES	    		12  //108KB - 2KB/page (256K -( 12k boot + 2K config + 2k app config + 10/12k pointer))
#else
	#error "ERROR UNKNOW FLASH SIZE"
#endif


#ifndef USE_USART
	#define USE_USART	1
#endif

/* Compute the FLASH upload image size */
//#define FLASH_IMAGE_SIZE                   (uint32_t) (FLASH_SIZE - (ApplicationAddress - 0x08000000))

/* Exported macro ------------------------------------------------------------*/
/* Common routines */
#define IS_AF(c)  ((c >= 'A') && (c <= 'F'))
#define IS_af(c)  ((c >= 'a') && (c <= 'f'))
#define IS_09(c)  ((c >= '0') && (c <= '9'))
#define ISVALIDHEX(c)  IS_AF(c) || IS_af(c) || IS_09(c)
#define ISVALIDDEC(c)  IS_09(c)
#define CONVERTDEC(c)  (c - '0')

#define CONVERTHEX_alpha(c)  (IS_AF(c) ? (c - 'A'+10) : (c - 'a'+10))
#define CONVERTHEX(c)   (IS_09(c) ? (c - '0') : CONVERTHEX_alpha(c))


/*
 *  boot_info[0]: CRC of Primary ELF
 *  boot_info[1]: Size of Primary ELF
 *  boot_info[2]: CRC of Second ELF
 *  boot_info[3]: Size of Second ELF
 */
typedef struct _SKS_BOOT_INFO
{
#if PUBLIC_VERSION
	uint8_t pub[PUBLIC_VERSION];
#endif
	uint32_t PrimaryCRC;
	uint32_t PrimarySize;
	uint32_t SecondaryCRC;
	uint32_t SecondarySize;
	uint32_t BootVersion;
	uint32_t PrimaryAddress;
	uint32_t SecondaryAddress;
	uint32_t ConfigAddress;
	uint32_t UpdateFirmware;
	uint32_t FirmwareVersion;
	uint32_t BootCount;
	uint32_t UpdateTime;
	uint32_t BootAll;
	char  DATA[20];
	char pad[4];
}
SKS_BOOT_INFO;
void flash_read_uboot_info(SKS_BOOT_INFO *boot_info);
void flash_write_uboot_info(SKS_BOOT_INFO *boot_info);
int flash_verify_image(SKS_BOOT_INFO *boot_info);
int flash_copy_image(SKS_BOOT_INFO *boot_info);
uint16_t Cal_CRC16(const uint8_t* data, uint32_t size);
void PrintBootInfo();
//extern SKS_BOOT_INFO boot_info;
volatile extern uint32_t ulSecCount;
volatile extern uint32_t ulTickCount;
volatile extern uint32_t ulMiliCount;

#define SKS_MOBILE_NO_LEN 14
#define MAX_SERVICE_PROFILE 3

typedef enum
{
	GSM_SOCKET_INIT,
	GSM_SOCKET_CONNECTING,
	GSM_SOCKET_CONNECTED,
	GSM_SOCKET_CLOSING,
	GSM_SOCKET_UNKNOW
}GSM_SOCKET_STATE;

typedef enum
{
	GSM_SERVER_TCP,
	GSM_SERVER_UDP
}GSM_SERVER_TYPE;

typedef enum
{
	GSM_SEND_NONE,
	GSM_SEND_INIT,
//	GSM_SEND_ACK,  //CHECK ACK
	GSM_SEND_TCP_PENDING,
	GSM_SEND_UDP_PENDING,
	GSM_SEND_UDP2_PENDING,
	GSM_SEND_SMS_PENDING,
	GSM_SEND_TCP_SENDING,
	GSM_SEND_UDP_SENDING,
	GSM_SEND_UDP2_SENDING,
	GSM_SEND_TCP_SUCCESS,
	GSM_SEND_UDP_SUCCESS,
	GSM_SEND_UDP2_SUCCESS,
	GSM_SEND_SMS_SUCCESS,
	GSM_SEND_TCP_FAILURED,
	GSM_SEND_UDP_FAILURED,
	GSM_SEND_UDP2_FAILURED,
	GSM_SEND_SMS_FAILURED,
	GSM_SEND_UNKNOW
}GSM_SEND_STATE;

typedef struct _SKS_COM_CONFIG {
	unsigned char idx; 		//
	unsigned baud; 			//Baudrate
	unsigned char databits; //Data bit ->8
	unsigned char stop; 	//Stop bit: 1, 0.5, 2, 1.5
	unsigned char parity; 	//Parity: No, Even , Odd
	unsigned char flow; 	//FLOW CONTROL: Non, RTS, CTS, RTS-CTS
	unsigned short in_mode; //Input mod: TERMINAL, CAMERA,
	unsigned short out_mode;//Output mod
	unsigned char active; 	//
	unsigned char Ix; //I1-I8 Command: 1-8, I0:Disable
} SKS_COM_CONFIG;

typedef struct _GSM_APN_CONFIG
{
	char bAvailable; //Data in ptrOutput is available;
	char apn_name[20];
	char apn_dns[20];
	char apn_username[20];
	char apn_password[20];
}
GSM_APN_CONFIG;
typedef struct _GSM_SERVICE_CONFIG
{
	int id;
	GSM_SERVER_TYPE server_type;
	char address[50];
	char port[8];
	//GSM_SIM_STATE state;
	GSM_SOCKET_STATE state;
	GSM_SEND_STATE send_state;
	char max_reconnect;
}
GSM_SERVICE_CONFIG;
typedef struct _SKS_DEVICE_CONFIG {
	unsigned long SIGN; //Micro second since start application
	unsigned long size; //Size of this struct
	char deviceID[12]; 	//DEVICE ID 								#S90
	char adminCode[8]; 	//Admin Code for update config  			#S91
	char SECKEY[8]; 	//Security KEY, send with LOCATION Report, 	#S92

	char USERNO[SKS_MOBILE_NO_LEN]; 	// USER CONFIG NUMBER
	char SKSNO[SKS_MOBILE_NO_LEN]; 		// SKS Control No   				#S34
	char HOTLINE[SKS_MOBILE_NO_LEN]; 	//HOTLINE
	char SMSALARM[SKS_MOBILE_NO_LEN]; 	// SMS ALARM		#S35
	char USSDNO[SKS_MOBILE_NO_LEN]; 	// SMS ALARM		#S37
	char DIALOUT[4][SKS_MOBILE_NO_LEN]; //Dial out 			#S31
	char DIALIN[4][SKS_MOBILE_NO_LEN]; 	//Dial in 			#S32
	char SMSREF[4][SKS_MOBILE_NO_LEN]; 	//Tra cuu SMS		#S36

	char IMEI[20]; //IMEI
	long TimeZone; //Time Zone in second, default +7*60*60 = +25200, #S16
	GSM_APN_CONFIG apnConfig; //Thiet lap APN 							#N2
	GSM_SERVICE_CONFIG serviceConfig[MAX_SERVICE_PROFILE]; //Thiet lap ServerIP, Port #N1

	unsigned long logLevel; 							//Log to file   					#S3
	char SYSSET0; //									#S99
	char SYSSET1;

	char VIN_NO[32]; //Vin no
	char REGISTER_NO[32]; //Vin REG no
	char REGISTER_DATE[32]; //Vin REG DATE						#17

	unsigned long functionMask;
	unsigned long driverCount;
	/*
	 * Che do kinh te: #N6
	 * 0: Disable,
	 * 1: Khong gui khi tat may sau n phut
	 * 2: Khong gui du lieu sau khi dung n phut
	 * 3: Start Eco mode combine 1, 2
	 */
	char requireCleanUp;
	unsigned long ulSendIdleInterval;	//Send interval when idle
	unsigned long network; //SKS public network mask

	long deleteThreshold; //Nguong xoa du lieu #S4
	long deleteThreshold2; //Nguong xoa du lieu theo thoi gian #S5
	long ussdInterval; //Dinh ky kiem tra tien, gui tra ve sever = I Message #S6

	unsigned long ulUpdateSystimeInterval; 	//Update System Time interval, Default: 3600s = 1h
	unsigned long ulSDReportInterval; 		//Interval to save report, default 1, Tan suat ghi the nho #N5
	unsigned long ulSendReportInterval; 	//Report send Interval, default 10s, Tan Suat Bao Cao, #N4
	unsigned long ulSendReportMax; 			//Maximum number of reports to send

	unsigned long ulGSMBaudrate; 			//
	SKS_COM_CONFIG comConfig[3];

	unsigned char doorOpenMark; 		//Door Open Mark

	unsigned long limitSpeed; 			//Gioi han toc do toi da, vuot qua toc do nay se bao cao
	unsigned long alarmSpeed; 			//Gioi han toc do canh bao, vuot qua toc do nay se canh bao bang coi/den
	unsigned long contDurationMax; 		//Thoi gian lai xe lien tuc, tinh theo giay #S14
	unsigned long indayDurationMax; 		//Thoi gian lai xe toi da trong ngay #S13
	unsigned char abnormalBrake; 			//Phanh gap, toc do giam xuong ABNORMAL_STOP trong vong 1 giay thi canh bao #S11
	unsigned char abnormalSpeedUp; 			//Tang Toc dot ngot #S12
	unsigned char maxValidSpeed; 			//Tang Toc dot ngot #S12
	unsigned char enableMaxSpeed; 			//Gioi han toc do xung quanh max speed +-%5
	long reserved3; //Tang Toc dot ngot #S12
//	unsigned short roundSpeed;
//	unsigned short reserved3;
	unsigned long stopDurationMax; //Thoi gian dung nghi #S15
	unsigned long stopRedLightMax; //Thoi gian dung den do #S15
	unsigned long dayStartOffset; //Thoi diem tinh bat dau cua ngay (tinh bang giay), vd: tu 8h sang hom truoc den 8h sang hom sau
	unsigned long keepOverSpeedDuration; 		//Gioi han toc do toi da  #S10
	unsigned long lastUpdate; 			//Thoi diem cap nhat cuoi cung
	//unsigned long nightSilent; 		//Gioi han toc do toi da  #S10
	unsigned char nightSilent; 			//Gioi han toc do toi da  #S10
	unsigned char doorType;				//Loai cua
	unsigned char disableSpeedAndEngine;			//Chi tinh thiet bi dang chay khi dong co ON, default 0: mix, 1: disable
	unsigned char enableDebug;			//Cho phep debug
	unsigned char doorDetect;			//Tu dong detect cua dong/mo

	/*
	 * Serial Parameter
	 */


	//unsigned long COMBaud[3];   //Thiet lap tham so cong COM #P1

	//char UpdateRequire;				//Require update firmware from server
	/*
	 * Network config
	 */
	//char Roaming;				//Cho phep roaming #N3
	/*
	 * Camera Config #C2
	 */
	unsigned char camMask;
	unsigned char camMode;  	//Auto mode
	unsigned int  camFormat;
	unsigned long camAutoFlags;
	unsigned long camAutoParam;
	unsigned long camAutoParam2;
	unsigned long camRetries;
	unsigned char camTimeOut;
	unsigned char camType;
	unsigned char camReserved1;
	unsigned char camReserved2;
	unsigned char fuelParam1[4];
	unsigned char fuelParam2[4];
	unsigned long logMask;
	unsigned long rtcPeriod;
	unsigned long sdSerial;
	unsigned long sdAvailableTime;
	unsigned long installTime;
	unsigned long antiRepeatTime;	//RFID , Fuel repeat time
	//unsigned long ulSendIdleInterval;
	//unsigned long ulStopSendInterval;	 //Tan suat gui report
	char padding[12];
} SKS_DEVICE_CONFIG;


#endif  /* _COMMON_H */
/*******************(C)COPYRIGHT 2010 STMicroelectronics *****END OF FILE******/
