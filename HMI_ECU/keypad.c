/*----------------------------------------------------------------------------------------------------------
[MODULE NAME]: KEYPAD

[FILE NAME]: keypad.c

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Source file for the KEYPAD driver.

-----------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------INCLUDES-----------------------------------------------------*/

#include "keypad.h"

/*----------------------------------PRIVATE FUNCTION PROTOTYPES--------------------------------------------*/

#if (NUMBER_OF_COLUMNS == 3)

 /* Function responsible for exchanging the key number for 4x3 keypad with the correspond in real keypad */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 a_buttonNumber);

#elif (NUMBER_OF_COLUMNS == 4)

/* Function responsible for exchanging the key number for 4x4 keypad with the correspond in real keypad */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 a_buttonNumber);

#endif

/*----------------------------------------FUNCTION DIFINATIONS---------------------------------------------*/

#if (NUMBER_OF_COLUMNS == 3)

static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 a_buttonNumber)
{
	switch(a_buttonNumber)
	{
		case 10: return '*';
				 break;
		case 11: return 0;
				 break;
		case 12: return '#';
				 break;

		default: return a_buttonNumber;
	}
}

#elif (NUMBER_OF_COLUMNS == 4)

static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 a_buttonNumber)
{
	switch(a_buttonNumber)
	{
		case 1: return 7;
				break;
		case 2: return 8;
				break;
		case 3: return 9;
				break;
		case 4: return '/';
				break;
		case 5: return 4;
				break;
		case 6: return 5;
				break;
		case 7: return 6;
				break;
		case 8: return '*';
				break;
		case 9: return 1;
				break;
		case 10: return 2;
				break;
		case 11: return 3;
				break;
		case 12: return '-';
				break;
		case 13: return 13;
				break;
		case 14: return 0;
				break;
		case 15: return '=';
				break;
		case 16: return '+';
				break;

		default: return a_buttonNumber;
	}
}

#endif

uint8 KeyPad_getPressedKey(void)
{
	uint8 row, column;

	while(1)
	{
		for(column=0 ; column < NUMBER_OF_COLUMNS ; column++)
		{
			 /* Each time only one of the column pins will be output pin.
			  * the rest will be input pins. */
			KEYPAD_PORT_DIR = (0x10 << column);

			/* Each time only one of the column output pins is clear.
			 * Enable the internal pull up resistors for the rows pins. */
			KEYPAD_PORT_OUT = ( ~(0x10 << column) );

			/* Loop in the rows for each column */
			for(row=0 ; row < NUMBER_OF_ROWS ; row++)
			{
				/* If the switch is press in this row */
				if(BIT_IS_CLEAR(KEYPAD_PORT_IN, row))
				{
					#if (NUMBER_OF_COLUMNS == 3)
					/* The passed value is an equation to calculate the button number */
						return KEYPAD_4x3_adjustKeyNumber( (row*NUMBER_OF_COLUMNS) + column+1);

					#elif (NUMBER_OF_COLUMNS == 4)
						return KEYPAD_4x4_adjustKeyNumber( (row*NUMBER_OF_COLUMNS) + column+1);

					#endif
				}
			}
		}
	}
}


