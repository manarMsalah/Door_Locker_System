/*----------------------------------------------------------------------------------------------------------

[FILE NAME]: control.h

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Header file for control ECU

-----------------------------------------------------------------------------------------------------------*/

#ifndef CONTROL_H_
#define CONTROL_H_

/*--------------------------------------------INCLUDES-----------------------------------------------------*/

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

#include "uart.h"
#include "external_eeprom.h"
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

#define INITIAL_VALUE_FOR_FIRST_ADDRESS 0x0F
#define MAX_PASSWORD_LENGTH_PLUS_ENTER 11
#define NUMBER_OF_OVERFLOWS_PER_MINUTE 1920
#define NUMBER_OF_OVERFLOWS_PER_HALF_MINUTE 960
#define NUMBER_OF_OVERFLOWS_PER_QUARTER_MINUTE 480


/*-------------------------------------------FUNCTION DECLARATIONS------------------------------------------*/

/* Initiate timer0 setting */
void CONTROL_initialTimer0(void);

/* Actions when timer0 ISR fired */
void CONTROL_newTimer0Tick(void);

/* Initiate interrupt1 setting */
void CONTROL_initialInt1(void);

/* Actions when INT1 ISR fired */
void CONTROL_newInt1Tick(void);

/* Compare two entered password and save it in memory if match */
void CONTROL_compareAndWrite(void);

/* Fire buzzer once the system locked */
void CONTROL_fireBuzzer(void);

/* Read password from memory and compare it with entered password */
void CONTROL_readAndCompare(void);

/* Rotate motor to open the door if entered the right password */
void CONTROL_rotateMotor(void);

#endif /* CONTROL_H_ */
