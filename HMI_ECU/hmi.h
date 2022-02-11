/*----------------------------------------------------------------------------------------------------------

[FILE NAME]: hmi.h

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Header file for HMI ECU

-----------------------------------------------------------------------------------------------------------*/

#ifndef HMI_H_
#define HMI_H_

/*--------------------------------------------INCLUDES-----------------------------------------------------*/

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

#include "uart.h"
#include "lcd.h"
#include "keypad.h"
#include "timer.h"
#include"external_interrupt.h"


/*--------------------------------------Difinations and configurations--------------------------------------*/

#define FIRST_TIME 0x10
#define NOT_FIRST_TIME 0x20
#define MATCH 0x30
#define NOTMATCH 0x40
#define COMPARE_TO_WRITE 0xA0
#define READ_TO_COMPARE 0xB0
#define OPEN_DOOR 0XC0
#define TRY_AGAIN 0x50
#define BLOCK 0x60

/* Number of overflows per a minute 1920 minus Number of overflows per two seconds 64 =1856 */
#define NUMBER_OF_OVERFLOWS_PER_MINUTE 1856

#define NUMBER_OF_OVERFLOWS_PER_HALF_MINUTE 960
#define NUMBER_OF_OVERFLOWS_PER_QUARTER_MINUTE 480


/*----------------------------------Extern moudle shared global variables-----------------------------------*/

extern uint8 g_receiveValue;
extern uint8 g_pressedKey;


/*-------------------------------------------FUNCTION DECLARATIONS------------------------------------------*/

/* Initiate timer0 setting */
void HMI_initialTimer0(void);

/* Actions when timer0 ISR fired */
void HMI_newTimer0Tick(void);

/* Initiate interrupt1 setting */
void HMI_initialInt1(void);

/* Actions when INT1 ISR fired */
void HMI_newInt1Tick(void);

/* Actions when entering wrong password three times */
void HMI_systemLocked(void);

/* Action and conditions while entering password */
void HMI_enterPassword(uint8 *key_Ptr, uint8 *arr);

/* Steps to creat new password */
void HMI_creatNewPassword(void);

/* Steps to change the old password */
void HMI_changePassword(void);

/* Steps to open the door */
void HMI_openDoor(void);

#endif /* HMI_H_ */
