/*----------------------------------------------------------------------------------------------------------

[FILE NAME]: project.c

[AUTHOR]: Manar Maohamed Malah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Resposible for initialize the ECU internal and external drivers, initialize pins and call the
               functions that responsible for control the system.

-----------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------INCLUDES-----------------------------------------------------*/

#include"control.h"



int main(void)
{

	uint8 receiveValue;
	uint8 initialValue=0;

	/* configure pin 6 of PORTD as output pin */
	SET_BIT(DDRD,PD6);

	/* configure pin 7 of PORTD as output pin */
	SET_BIT(DDRD,PD7);

	/* configure pin 5 of PORTC as output pin */
	SET_BIT(DDRC,PC5);

	/* configure INT1/PD3 of PORTD as input pin */
	CLEAR_BIT(DDRD,PD3);


	/* Enable the internal pull up resistor at PD3 pin */
	SET_BIT(PORTD,PD3);

	/* Initialize the DC-Motor */
	CLEAR_BIT(PORTD,PD6);
	CLEAR_BIT(PORTD,PD7);


	/*  Enable interrupts by setting I-bit */
	SET_BIT(SREG,7);


	/* Init UART */
	UART_init();

   /* Init EEPROM */
	EEPROM_init();

	/* Init INT1 */
	CONTROL_initialInt1();

	/* Write 0x0F in the external EEPROM .. Remove // if you want to soft reset the system */
	//EEPROM_writeByte(0x0001, INITIAL_VALUE_FOR_FIRST_ADDRESS);
	_delay_ms(10);
	/* Read the value for first address */
	EEPROM_readByte(0x0001, &initialValue);

	if(initialValue == INITIAL_VALUE_FOR_FIRST_ADDRESS)
	{
		/* If you did not set a password to the system yet */
		UART_sendByte(FIRST_TIME);
	}
	else
	{
		/* A password already saved in memory */
		UART_sendByte(NOT_FIRST_TIME);
	}

	while(1)
	{
		/* Receive signal from HMI ECU */
		receiveValue= UART_recieveByte();

		if(receiveValue == COMPARE_TO_WRITE)
		{

			CONTROL_compareAndWrite();

		}
		else if(receiveValue==READ_TO_COMPARE)
		{

			CONTROL_readAndCompare();
		}
		else if(receiveValue==OPEN_DOOR)
		{
			/* Disable the external interrupt */
			CLEAR_BIT(GICR,INT1);

			CONTROL_rotateMotor();

			/* Enable the external interrupt */
			SET_BIT(GICR,INT1);
		}


	}
}
