/*----------------------------------------------------------------------------------------------------------

[FILE NAME]: hmi.c

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Source file for HMI ECU that responsible for acting with user and sending signals to control
               ECU to real actions.

-----------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------INCLUDES-----------------------------------------------------*/

#include "hmi.h"



/*-----------------------------------------GLOBAL VARIABLES------------------------------------------------*/

uint16 g_overflow=0;
uint8 passwordContainer_Arr[11];
uint8 g_loopCounter;


/*----------------------------------------FUNCTION DIFINATIONS---------------------------------------------*/

void HMI_initialTimer0(void)
{
	Timer0_setCallBack(HMI_newTimer0Tick);
	timer0_init_CTC_mode(NUMBER_OF_TICKS);
}


void HMI_newTimer0Tick(void)
{
	g_overflow++;
	if(g_overflow == NUMBER_OF_OVERFLOWS_PER_MINUTE)
	{
		/* stop timer0 */
		TCCR0 &= ~((1<<CS02) | (1<<CS00));
	}
}


void HMI_initialInt1(void)
{
	INT1_setCallBack(HMI_newInt1Tick);
	INT1_Init();
}


void HMI_newInt1Tick(void)
{
	LCD_clearScreen();
	LCD_displayString("      Wait");

	for(g_loopCounter=5 ; g_loopCounter<=10 ; g_loopCounter++)
	{
		LCD_goToRowColumn(1,g_loopCounter);
		LCD_displayCharacter('-');
		_delay_ms(700);
	}

	LCD_clearScreen();
	LCD_displayString("Please turn off ");
	LCD_displayStringRowColumn(1,3,"the power");
	_delay_ms(1500);
	LCD_clearScreen();
	LCD_displayString("    to reset");
	LCD_displayStringRowColumn(1,3,"the system");
	_delay_ms(1500);
	LCD_clearScreen();
	LCD_displayString("  then turn on");
	LCD_displayStringRowColumn(1,5,"again");

	/* To stuck until turning off the power */
	while(1){}
}


void HMI_systemLocked(void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,5,"WRONG");
	_delay_ms(1000);
	LCD_clearScreen();
	LCD_displayStringRowColumn(1,2,"System locked");
	HMI_initialTimer0();
	while(g_overflow <= NUMBER_OF_OVERFLOWS_PER_MINUTE)
	{
		LCD_displayStringRowColumn(0,4,"WARNING");
		_delay_ms(1000);
		LCD_displayStringRowColumn(0,4,"       ");
		_delay_ms(1000);

		if(g_overflow == NUMBER_OF_OVERFLOWS_PER_MINUTE)
		{
			/* To break the while loop */
			g_overflow++;
		}
	}
	g_overflow=0;
}


void HMI_enterPassword(uint8 *key_Ptr , uint8 *arr)
{
	/* Press time because of the last press before calling the function */
	_delay_ms(500);

	/* for loop to fill the arr with password ending by = until the end of arr */
	for(g_loopCounter=0 ; g_loopCounter<=10 ; g_loopCounter++)
	{
    	/* get the pressed key number */
		*key_Ptr= KeyPad_getPressedKey(); /* get the pressed key number */

		/* To avoid filling the arr without pressing enter '=' */
			while((g_loopCounter==10) && (*key_Ptr != '='))
			{
				LCD_displayStringRowColumn(0,1,"Please press =");
				*key_Ptr = KeyPad_getPressedKey();
			}

		if((*key_Ptr <= 9) && (*key_Ptr >= 0))
		{
			arr[g_loopCounter]= *key_Ptr;

			/* If first number of the passaword */
			if(g_loopCounter == 0)
			{
				LCD_clearScreen();
				LCD_goToRowColumn(1,3);
			}

			/* Clear only the first row */
			LCD_displayStringRowColumn(0,0,"                ");

			/* Display the pressed keypad switch after the last '*' */
			LCD_goToRowColumn(1,g_loopCounter+3);

			/* Display the pressed keypad switch */
			LCD_displayCharacter('*');

			/* Press time */
			_delay_ms(500);

		}
		/* If entered the password then pressed enter '=' */
		else if(*key_Ptr== '=' && g_loopCounter!=0)
		{
			/* Save = until the end of arr */
			arr[g_loopCounter]= *key_Ptr;

		}
		/* If pressed enter '=' without entering password */
		else if(*key_Ptr== '=' && g_loopCounter==0)
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,4,"No symbol");

			/* Press time */
			_delay_ms(500);

			/* To try again right press in the same place */
			g_loopCounter--;
		}
		/* If pressed any symbol */
		else if(*key_Ptr== '*' || *key_Ptr== '+' || *key_Ptr== '-' || *key_Ptr== '/' || *key_Ptr== 13)
		{
			/*If first press clear the last screen */
			if(g_loopCounter == 0)
			{
				LCD_clearScreen();
			}

			LCD_displayStringRowColumn(0,4,"No symbol");

			/* Press time */
			_delay_ms(500);

			/* To try again right press in the same place */
			g_loopCounter--;
		}
	}
}


void HMI_creatNewPassword(void)
{
	uint8 firstEnter=0;

	/* Reset receive value */
	g_receiveValue=0;

	LCD_clearScreen();
	LCD_displayString("Please enter new");
	LCD_displayStringRowColumn(1,4,"password");

	/* Send signal to control ECU to call the required function */
	UART_sendByte(COMPARE_TO_WRITE);

	while(g_receiveValue != MATCH)
	{
		/* Get password from the user */
		HMI_enterPassword(&g_pressedKey, passwordContainer_Arr);

		/*If the user pressed enter '=' after entering password */
		if(g_pressedKey == '=')
		{
			if(firstEnter == 0)
			{
				/* Send the password to control ECU */
				UART_sendArray(passwordContainer_Arr);

				LCD_clearScreen();
				LCD_displayString("Please re-enter");
				LCD_displayStringRowColumn(1,0,"your password");

				firstEnter++;
			}
			else
			{
				/* Send the re-entered  password to control ECU */
				UART_sendArray(passwordContainer_Arr);

				/* Receive signal from control ECU */
				g_receiveValue= UART_recieveByte();

				if(g_receiveValue == MATCH)
				{
					/* break the while loop */
				}

				else if(g_receiveValue == NOTMATCH)
				{
					LCD_clearScreen();
					LCD_displayString("Not matching");
					_delay_ms(1000);
					LCD_clearScreen();
					LCD_displayString("Please enter new");
					LCD_displayStringRowColumn(1,4,"password");
					firstEnter=0;
				}
			}
		}
	}
}


void HMI_changePassword(void)
{
	/* Reset receive value */
	g_receiveValue=0;

	/* Send signal to control ECU to call the required function */
	UART_sendByte(READ_TO_COMPARE);

	while((g_receiveValue != MATCH) && (g_receiveValue != BLOCK))
	{
		LCD_clearScreen();
		LCD_displayString("Please enter the");
		LCD_displayStringRowColumn(1,2,"old password");

		/* Get the password from the user */
		HMI_enterPassword(&g_pressedKey, passwordContainer_Arr);

		/*If the user pressed enter '=' after entering the password */
		if(g_pressedKey == '=')
		{
			LCD_clearScreen();

			/* Send the password to control ECU */
			UART_sendArray(passwordContainer_Arr);

			/* Receive signal from control ECU */
			g_receiveValue= UART_recieveByte();

			if(g_receiveValue == MATCH)
			{
				HMI_creatNewPassword();
			}
			else if(g_receiveValue == NOTMATCH)
			{
				/* Receive signal from control ECU */
				g_receiveValue= UART_recieveByte();

				if(g_receiveValue == TRY_AGAIN)
				{
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,5,"Wrong");
					_delay_ms(1000);
				}
				else if(g_receiveValue == BLOCK)
				{
					HMI_systemLocked();
				}

			}
		}
	}
}


void HMI_openDoor(void)
{
	/* Reset receive value */
	g_receiveValue=0;

	/* Send signal to control ECU to call the required function */
	UART_sendByte(READ_TO_COMPARE);

	while((g_receiveValue != MATCH) && (g_receiveValue != BLOCK))
	{
		LCD_clearScreen();
		LCD_displayString("Please enter the");
		LCD_displayStringRowColumn(1,4,"password");

		/* Get the password from the user */
		HMI_enterPassword(&g_pressedKey, passwordContainer_Arr);

		/*If the user pressed enter '=' after entering the password */
		if(g_pressedKey == '=')
		{
			LCD_clearScreen();

			/* Send the password to control ECU */
			UART_sendArray(passwordContainer_Arr);

			/* Receive signal from control ECU */
			g_receiveValue= UART_recieveByte();

			if( g_receiveValue == MATCH)
			{
				/* Disable the external interrupt */
				CLEAR_BIT(GICR,INT1);

				/* Send signal to control ECU to call the required function */
				UART_sendByte(OPEN_DOOR);

				LCD_displayStringRowColumn(0,4,"Door is");
				LCD_displayStringRowColumn(1,3,"unlocking");

				/* Start timer0 */
				HMI_initialTimer0();

				while(g_overflow <= NUMBER_OF_OVERFLOWS_PER_HALF_MINUTE)
				{
					if(g_overflow == NUMBER_OF_OVERFLOWS_PER_QUARTER_MINUTE)
					{
						LCD_clearScreen();
						LCD_displayStringRowColumn(0,4,"Door is");
						LCD_displayStringRowColumn(1,4,"locking");
					}
					if(g_overflow == NUMBER_OF_OVERFLOWS_PER_HALF_MINUTE)
					{
						/* Stop timer0 */
						TCCR0 &= ~((1<<CS02) | (1<<CS00));

						/* To break the while loop */
						g_overflow++;

						/* Enable the external interrupt */
						SET_BIT(GICR,INT1);
					}
				}
				g_overflow=0;
			}
			else if(g_receiveValue == NOTMATCH)
			{
				/* Receive signal from control ECU */
				g_receiveValue= UART_recieveByte();

				if(g_receiveValue == TRY_AGAIN)
				{
					LCD_displayStringRowColumn(0,5,"Wrong");
					_delay_ms(1000);
				}
				else if(g_receiveValue == BLOCK)
				{
					HMI_systemLocked();
				}
			}
		}
	}
}

