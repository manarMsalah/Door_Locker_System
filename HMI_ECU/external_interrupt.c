/*----------------------------------------------------------------------------------------------------------

[FILE NAME]: external_interrupt.c

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Source file for external interrupt module

-----------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------INCLUDES-----------------------------------------------------*/

#include"external_interrupt.h"


/*----------------------------------------Global variables-------------------------------------------------*/

/* Global pointer to function used to point to functions be used in Call Back */
static volatile void (*g_INT1_Call_Back_Ptr)(void)= NULL_PTR;


/*--------------------------------------------FUNCTIONS-----------------------------------------------------*/

void INT1_Init(void)
{
    /* Enable external interrupt pin INT1 */
	GICR  |= (1<<INT1);
	/* Trigger INT1 with the falling edge */
	MCUCR |= (1<<ISC11);
	MCUCR &= ~(1<<ISC10);
}


void INT1_setCallBack(void(*Ptr2Func)(void))
{
	g_INT1_Call_Back_Ptr = Ptr2Func;
}

/* Interrupt Service Routine for external interrupt1 */
ISR(INT1_vect)
{
	/* Check if the INT1_setCallBack is already called */
	if(g_INT1_Call_Back_Ptr != NULL_PTR)
	{
		/* Call the function in the scheduler using call-back concept */
		(*g_INT1_Call_Back_Ptr)();
	}
}

