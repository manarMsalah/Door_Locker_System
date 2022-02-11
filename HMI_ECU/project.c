/*----------------------------------------------------------------------------------------------------------

[FILE NAME]: project.c

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]:  Resposible for initialize the ECU internal and external drivers, initialize pins and call the
                functions that responsible for control the system.

-----------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------INCLUDES-----------------------------------------------------*/

#include "hmi.h"


/*-----------------------------------------GLOBAL VARIABLES------------------------------------------------*/

uint8 g_receiveValue;
uint8 g_pressedKey;



int main(void)
{
	/* configure INT1/PD3 of PORTD as input pin */
	CLEAR_BIT(DDRD,PD3);

	/* Enable the internal pull up resistor at PD3 pin */
	SET_BIT(PORTD,PD3);


	/*  Enable interrupts by setting I-bit */
	SET_BIT(SREG,7);



	/* Init UART */
	UART_init();

	/* Init lcd */
	LCD_init();

	/* Init INT1 */
	HMI_initialInt1();


	/* Receive signal from control ECU */
	g_receiveValue=UART_recieveByte();

	/* If you did not set a password to the system yet */
	if(g_receiveValue == FIRST_TIME)
	{
		LCD_displayStringRowColumn(1,3,"WELCOME :)");
		_delay_ms(2000);
		LCD_clearScreen();
		LCD_displayString("       We");
		_delay_ms(700);
		LCD_displayStringRowColumn(1,6,"need");
		_delay_ms(1000);
		LCD_clearScreen();
		LCD_displayString("       to");
		_delay_ms(700);
		LCD_displayStringRowColumn(1,5,"create");
		_delay_ms(1000);
		LCD_clearScreen();
		LCD_displayStringRowColumn(1,3,"a password");
		_delay_ms(1300);
		LCD_clearScreen();
		LCD_displayString("       to");
		_delay_ms(1000);
		LCD_clearScreen();
		LCD_displayString("      the");
		_delay_ms(500);
		LCD_displayStringRowColumn(1,5,"system");
		_delay_ms(1500);
		LCD_clearScreen();
		LCD_displayString("MAX 10 numbers");
		LCD_displayStringRowColumn(1,0,"((No symbol !))");
		_delay_ms(2500);
		LCD_clearScreen();
		LCD_displayString("Enter password");
		LCD_displayStringRowColumn(1,0,"then press =");
		_delay_ms(2500);
		LCD_clearScreen();

		HMI_creatNewPassword();

	}
	/* A password already saved in memory */
	else if(g_receiveValue == NOT_FIRST_TIME)
	{
		/* No action needed */
	}


	while(1)
	{
		LCD_clearScreen();
		LCD_displayString("Main option");
		_delay_ms(1500);
		LCD_clearScreen();
		LCD_displayString("+ Open door");
		LCD_displayStringRowColumn(1,0,"x Change password");

		/* Get the pressed key from user */
		g_pressedKey= KeyPad_getPressedKey();

		if(g_pressedKey == '*')
		{
			HMI_changePassword();
		}
		if(g_pressedKey == '+')
		{
			HMI_openDoor();
		}
	}
}
