/*----------------------------------------------------------------------------------------------------------
[MODULE NAME]: LCD

[FILE NAME]: lcd.h

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Header file for the LCD driver.

-----------------------------------------------------------------------------------------------------------*/
#ifndef LCD_H_
#define LCD_H_

/*--------------------------------------------INCLUDES-----------------------------------------------------*/

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/*-----------------------------------Difinations and configurations----------------------------------------*/

/* LCD HW Pins */
#define RS                              PC0
#define RW                              PC1
#define E                               PC2

#define LCD_CTRL_PORT_DIR               DDRC
#define LCD_CTRL_PORT                   PORTC
#define LCD_DATA_PORT_DIR               DDRA
#define LCD_DATA_PORT                   PORTA


/* LCD Commands */
#define CLEAR_COMMAND                   0x01
#define TWO_LINE_LCD_Eight_BIT_MODE     0x38
#define CURSOR_OFF                      0x0C
#define CURSOR_ON                       0x0E
#define SET_CURSOR_LOCATION             0x80


/*-------------------------------------------FUNCTION DECLARATIONS------------------------------------------*/

/* Responsible for initiating the LCD to be ready for displaying. */
void LCD_init(void);
/* Responsible for sending a command according to the timing diagram in the data sheet. */
void LCD_sendCommand(uint8 a_command);
/* Responsible for displaying a character according to the timing diagram in the data sheet. */
void LCD_displayCharacter(uint8 a_data);
/* Responsible for displaying a string with the help of LCD_displayCharacter function. */
void LCD_displayString(const char *Str);
/* Responsible for directing the cursor to a selected row and column. */
void LCD_goToRowColumn(uint8 a_row,uint8 a_column);
/* Responsible for displaying a string and its begin will be in a selected row and column. */
void LCD_displayStringRowColumn(uint8 a_row,uint8 a_column,const char *Str);
/* Use this function when the input data is decimal number and unknown in the coding time.*/
void LCD_intgerToString(int a_data);
/* Responsible for clearing the screen with the help of LCD_sendCommand function. */
void LCD_clearScreen(void);


#endif /* LCD_H_ */
