/*----------------------------------------------------------------------------------------------------------
[MODULE NAME]: LCD

[FILE NAME]: lcd.c

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Source file for the LCD driver.

-----------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------INCLUDES-----------------------------------------------------*/

#include "lcd.h"

/*----------------------------------------FUNCTION DIFINATIONS---------------------------------------------*/

void LCD_init(void)
{
	/* Configure the data port as output port. */
	LCD_DATA_PORT_DIR = 0xFF;
	/* Configure the control pins as output pins. */
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW);
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);
	LCD_sendCommand(CURSOR_OFF);
	/* clear LCD at the beginning. */
	LCD_sendCommand(CLEAR_COMMAND);
}

void LCD_sendCommand(uint8 a_command)
{
	/* Instruction Mode. */
	CLEAR_BIT(LCD_CTRL_PORT,RS);
	/* Write data. */
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	/* Delay for processing Tas = 50ns */
	_delay_ms(1);
	/* Enable LCD. */
	SET_BIT(LCD_CTRL_PORT,E);
	/* Delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);
	/* Out the required command to the data bus. */
	LCD_DATA_PORT = a_command;
	/* Delay for processing Tdsw = 100ns */
	_delay_ms(1);
	/* Disable LCD. */
	CLEAR_BIT(LCD_CTRL_PORT,E);
	/* delay for processing Th = 13ns */
	_delay_ms(1);
}

void LCD_displayCharacter(uint8 a_data)
{
	/* Data Mode.*/
	SET_BIT(LCD_CTRL_PORT,RS);
	/* Write data to LCD. */
	CLEAR_BIT(LCD_CTRL_PORT,RW);
    /* Delay for processing Tas = 50ns */
	_delay_ms(1);
	/* Enable LCD.*/
	SET_BIT(LCD_CTRL_PORT,E);
	/* Delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);
	/* Out the required data char to the data bus. */
	LCD_DATA_PORT = a_data;
	/* Delay for processing Tdsw = 100ns */
	_delay_ms(1);
	/* Disable LCD.*/
	CLEAR_BIT(LCD_CTRL_PORT,E);
	/* Delay for processing Th = 13ns */
	_delay_ms(1);
}

void LCD_displayString(const char *Str)
{
	while(*Str != '\0')
	{
		LCD_displayCharacter(*Str);
		Str++;
	}

}

void LCD_goToRowColumn(uint8 a_row, uint8 a_column)
{
	uint8 Address;

	/* Calculate the address of each position on the screen. */
	switch(a_row)
	{
		case 0:
				Address= a_column;
				break;
		case 1:
				Address= a_column + 0x40;
				break;
		case 2:
				Address= a_column + 0x10;
				break;
		case 3:
				Address= a_column + 0x50;
				break;
	}

	/* Calculate the command that force the cursor to goto a specific address. */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 a_row,uint8 a_column,const char *Str)
{
	LCD_goToRowColumn(a_row, a_column);
	LCD_displayString(Str);
}

void LCD_intgerToString(int a_data)
{
   /* String to hold the ASCII result. */
   char buff[16];
   /* Function to convert the integer to ASCII.
    *  10 for decimal */
   itoa(a_data,buff,10);
   LCD_displayString(buff);
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND);
}
