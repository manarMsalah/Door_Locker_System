/*----------------------------------------------------------------------------------------------------------

[FILE NAME]: control.c

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Source file for control ECU that responsible for read from and write in the EEPROM memmory,
               rotate motor, save and check password.

-----------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------INCLUDES-----------------------------------------------------*/

#include"control.h"



/*-----------------------------------------GLOBAL VARIABLES------------------------------------------------*/

uint8 g_rightPassword=0;
uint16 g_overflow=0;
uint8 g_loopCounter;



/*----------------------------------------FUNCTION DIFINATIONS---------------------------------------------*/

void CONTROL_initialTimer0(void)
{
	Timer0_setCallBack(CONTROL_newTimer0Tick);
	timer0_init_CTC_mode(NUMBER_OF_TICKS);
}



void CONTROL_newTimer0Tick(void)
{
	g_overflow++;
	if(g_overflow==NUMBER_OF_OVERFLOWS_PER_MINUTE)
	{
		/* stop timer0 */
		TCCR0 &= ~((1<<CS02) | (1<<CS00));
	}
}


void CONTROL_initialInt1(void)
{
	INT1_setCallBack(CONTROL_newInt1Tick);
	INT1_Init();
}


void CONTROL_newInt1Tick(void)
{
	/* Write initial value in first place in memmory to check it once turn on the power */
	EEPROM_writeByte(0x0001, INITIAL_VALUE_FOR_FIRST_ADDRESS);

	/* To stuck until turning off the power */
	while(1){}
}


void CONTROL_fireBuzzer(void)
{
	/* Start timer0 */
	CONTROL_initialTimer0();

	while(g_overflow <= NUMBER_OF_OVERFLOWS_PER_MINUTE)
	{
		/* Start buzzer */
		SET_BIT(PORTC,PC5);
		_delay_ms(1);
		CLEAR_BIT(PORTC,PC5);
		_delay_ms(1);

		if(g_overflow == NUMBER_OF_OVERFLOWS_PER_MINUTE)
		{
			g_overflow++;
		}
	}
	g_overflow=0;
}


void CONTROL_compareAndWrite(void)
{
	uint8 passwordContainer_Arr1[11]={0};
	uint8 passwordContainer_Arr2[11]={0};

	while(g_rightPassword <= MAX_PASSWORD_LENGTH_PLUS_ENTER)
	{
		/* Receive password first time */
		UART_receiveArray(passwordContainer_Arr1);
		/* Receive password second time */
		UART_receiveArray(passwordContainer_Arr2);

		/* for loop to check if matching */
		for(g_loopCounter=0  ;  g_loopCounter < MAX_PASSWORD_LENGTH_PLUS_ENTER  ;  g_loopCounter++)
		{
			if(passwordContainer_Arr1[g_loopCounter] == passwordContainer_Arr2[g_loopCounter])
			{
				g_rightPassword++;
			}
		}

		if(g_rightPassword == MAX_PASSWORD_LENGTH_PLUS_ENTER)
		{
			/* Send match to HMI ECU */
			UART_sendByte(MATCH);

			/* Save the right entered password */
			EEPROM_writeByte(0x0001, passwordContainer_Arr2[0]);
			_delay_ms(10);
			EEPROM_writeByte(0x0002, passwordContainer_Arr2[1]);
			_delay_ms(10);
			EEPROM_writeByte(0x0003, passwordContainer_Arr2[2]);
			_delay_ms(10);
			EEPROM_writeByte(0x0004, passwordContainer_Arr2[3]);
			_delay_ms(10);
			EEPROM_writeByte(0x0005, passwordContainer_Arr2[4]);
			_delay_ms(10);
			EEPROM_writeByte(0x0006, passwordContainer_Arr2[5]);
			_delay_ms(10);
			EEPROM_writeByte(0x0007, passwordContainer_Arr2[6]);
			_delay_ms(10);
			EEPROM_writeByte(0x0008, passwordContainer_Arr2[7]);
			_delay_ms(10);
			EEPROM_writeByte(0x0009, passwordContainer_Arr2[8]);
			_delay_ms(10);
			EEPROM_writeByte(0x000A, passwordContainer_Arr2[9]);
			_delay_ms(10);
			EEPROM_writeByte(0x000B, passwordContainer_Arr2[10]);

			/* To break the while loop */
			g_rightPassword++;
		}
		else
		{
			g_rightPassword=0;

			/* Send not match to HMI ECU */
			UART_sendByte(NOTMATCH);
		}
	}
	g_rightPassword=0;
}


void CONTROL_readAndCompare(void)
{
	uint8 wrongPassword=0;
	uint8 passwordContainer_Arr3[11]={0};
	uint8 passwordContainer_Arr4[11]={0};

	while((g_rightPassword <= MAX_PASSWORD_LENGTH_PLUS_ENTER) && (wrongPassword <= 3))
	{
		/* Receive entered password */
		UART_receiveArray(passwordContainer_Arr3);

		/* Read saved password from memory */
		EEPROM_readByte(0x0001, &passwordContainer_Arr4[0]);
		_delay_ms(10);
		EEPROM_readByte(0x0002, &passwordContainer_Arr4[1]);
		_delay_ms(10);
		EEPROM_readByte(0x0003, &passwordContainer_Arr4[2]);
		_delay_ms(10);
		EEPROM_readByte(0x0004, &passwordContainer_Arr4[3]);
		_delay_ms(10);
		EEPROM_readByte(0x0005, &passwordContainer_Arr4[4]);
		_delay_ms(10);
		EEPROM_readByte(0x0006, &passwordContainer_Arr4[5]);
		_delay_ms(10);
		EEPROM_readByte(0x0007, &passwordContainer_Arr4[6]);
		_delay_ms(10);
		EEPROM_readByte(0x0008, &passwordContainer_Arr4[7]);
		_delay_ms(10);
		EEPROM_readByte(0x0009, &passwordContainer_Arr4[8]);
		_delay_ms(10);
		EEPROM_readByte(0x000A, &passwordContainer_Arr4[9]);
		_delay_ms(10);
		EEPROM_readByte(0x000B, &passwordContainer_Arr4[10]);

		/* for loop to check if matching */
		for(g_loopCounter=0 ; g_loopCounter < MAX_PASSWORD_LENGTH_PLUS_ENTER ; g_loopCounter++)
		{
			if(passwordContainer_Arr3[g_loopCounter] == passwordContainer_Arr4[g_loopCounter])
			{
				g_rightPassword++;
			}
		}
		if(g_rightPassword == MAX_PASSWORD_LENGTH_PLUS_ENTER)
		{
			/* To break the while loop */
			g_rightPassword++;

			/* Send match to HMI ECU */
			UART_sendByte(MATCH);
		}
		else
		{
			g_rightPassword=0;

			/* Send not match to HMI ECU */
			UART_sendByte(NOTMATCH);

			wrongPassword++;

			/* Try again if entered wrong password 1 or 2 times */
			if((wrongPassword == 1) || (wrongPassword == 2))
			{
				UART_sendByte(TRY_AGAIN);
			}
			/* Lock the system and fire the buzzer if entered wrong password 3 times */
			else if(wrongPassword == 3)
			{
				/* To break the while loop */
				wrongPassword++;

				UART_sendByte(BLOCK);
				CONTROL_fireBuzzer();
			}
		}
	}
	wrongPassword=0;
	g_rightPassword=0;
}


void CONTROL_rotateMotor(void)
{
	/* Start timer0 */
	CONTROL_initialTimer0();

	/* Rotate motor with clockwise */
	CLEAR_BIT(PORTD,PD6);
	SET_BIT(PORTD,PD7);

	while(g_overflow <= NUMBER_OF_OVERFLOWS_PER_HALF_MINUTE)
	{
		if(g_overflow == NUMBER_OF_OVERFLOWS_PER_QUARTER_MINUTE)
		{
			/* Rotate motor anti clockwise */
			SET_BIT(PORTD,PD6);
			CLEAR_BIT(PORTD,PD7);
		}
		if(g_overflow == NUMBER_OF_OVERFLOWS_PER_HALF_MINUTE)
		{
			/* Stop timer0 */
			TCCR0 &= ~((1<<CS02) | (1<<CS00));

			/*Stop motor*/
			CLEAR_BIT(PORTD,PD6);
			CLEAR_BIT(PORTD,PD7);

			/* To break the while loop */
			g_overflow++;
		}
	}
	g_overflow=0;
}
