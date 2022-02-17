/*----------------------------------------------------------------------------------------------------------
[MODULE NAME]: KEYPAD

[FILE NAME]: keypad.h

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Header file for the KEYPAD driver.

-----------------------------------------------------------------------------------------------------------*/
#ifndef KEYPAD_H_
#define KEYPAD_H_

/*--------------------------------------------INCLUDES-----------------------------------------------------*/

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/*--------------------------------------Difinations and configurations--------------------------------------*/

/* Keypad configurations for number of rows and columns */
#define NUMBER_OF_ROWS             4
#define NUMBER_OF_COLUMNS          4

/* Keypad Port Configurations */
#define KEYPAD_PORT_DIR            DDRB
#define KEYPAD_PORT_IN             PINB
#define KEYPAD_PORT_OUT            PORTB

/*-------------------------------------------FUNCTION DECLARATIONS------------------------------------------*/

/*Responsible for getting the pressed keypad key*/
uint8 KeyPad_getPressedKey(void);


#endif /* KEYPAD_H_ */
