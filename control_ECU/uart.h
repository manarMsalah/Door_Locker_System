 /*----------------------------------------------------------------------------------------------------------
[MODULE NAME]: UART

[FILE NAME]: uart.h

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Header file for the UART driver.

-----------------------------------------------------------------------------------------------------------*/
#ifndef UART_H_
#define UART_H_

/*--------------------------------------------INCLUDES-----------------------------------------------------*/
#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*--------------------------------------Difinations and configurations--------------------------------------*/

/* UART Driver Baud Rate */
#define USART_BAUDRATE 9600

/* If send or receive array*/
#define SIZE_OF_ARRAY 10

/* Equation to calculate the baud prescale */
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)

/*-------------------------------------------FUNCTION DECLARATIONS------------------------------------------*
/* Responsible for adjusting the frame formate */
void UART_init(void);

/* Responsible for sending a single byte */
void UART_sendByte(const uint8 data);

/* Responsible for receiving a single byte */
uint8 UART_receiveByte(void);

/* Send array with defined size */
void UART_sendArray(const uint8 *a_array);

/* Receive array with defined size */
void UART_receiveArray(uint8 *a_array);

/* Responsible for sending a string */
void UART_sendString(const uint8 *Str);

/* Responsible for receiving a string */
void UART_receiveString(uint8 *Str);


#endif /* UART_H_ */
