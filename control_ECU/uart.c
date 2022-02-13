 /*----------------------------------------------------------------------------------------------------------
[MODULE NAME]: UART

[FILE NAME]: uart.c

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Source file for the UART driver.

-----------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------INCLUDES-----------------------------------------------------*/

#include "uart.h"


/*----------------------------------------FUNCTION DIFINATIONS---------------------------------------------*/

void UART_init(void)
{
	/* Set U2X for double transmission speed */
	UCSRA = (1<<U2X);

	/* Receiver and Transmitter Enable.
	 * Disable other options. */
	UCSRB = (1<<RXEN) | (1<<TXEN);


	/* The URSEL must be one when writing the UCSRC.
	 * Select the Asynchronous Operation.
	 * Disable parity bit.
	 * Select the one stop bit option.
	 * Select the 8-bit data mode. */
	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);

	/* Generic way to set the first 8 bits from the baud prescale in UBRRL and last 4 bits in UBRRH */
	UBRRH = BAUD_PRESCALE>>8;
	UBRRL = BAUD_PRESCALE;
}

void UART_sendByte(const uint8 data)
{
	/* Polling on UDRE flag until is set to one when the Tx buffer (UDR) is empty and ready for
	 * transmition*/
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/* Puttting the required data in the UDR register to send it */
	UDR = data;
}

uint8 UART_receiveByte(void)
{
	/* Polling on RXC flag until this flag is set to one after receiving data */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/* RXC flag will be cleared after reading the data */
	return UDR;
}

void UART_sendArray(const uint8 *a_array)
{
	uint8 index = 0;

	while(index != SIZE_OF_ARRAY)
	{
		UART_sendByte(a_array[index]);
		index++;
	}

}

void UART_receiveArray(uint8 *a_array)
{
	uint8 index = 0;

	while(index != SIZE_OF_ARRAY)
	{
		a_array[index] = UART_receiveByte();
		index++;
	}

}

void UART_sendString(const uint8 *Str)
{
	uint8 index = 0;
	while(Str[index] != '\0')
	{
		UART_sendByte(Str[index]);
		index++;
	}

}

void UART_receiveString(uint8 *Str)
{
	uint8 index = 0;
	uint8 str_lenght;
	str_lenght = UART_receiveByte();
	while(index != str_lenght)
	{
		Str[index] = UART_receiveByte();
		index++;
	}
	Str[index] = '\0';
}


