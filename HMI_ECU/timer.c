/*----------------------------------------------------------------------------------------------------------

[FILE NAME]: timer.c

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Source file for timer module

-----------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------INCLUDES-----------------------------------------------------*/

#include "timer.h"


/*----------------------------------------Global variables-------------------------------------------------*/

/* Global pointer to function used to point to functions be used in Call Back */
static volatile void (*g_Timer0_Call_Back_Ptr)(void)= NULL_PTR;



/*--------------------------------------------FUNCTIONS-----------------------------------------------------*/


void timer0_init_CTC_mode(unsigned char tick)
{
	/* timer initial value */
	TCNT0 = 0;
	/* compare value */
	OCR0  = tick;
	/* //enable compare interrupt */
	TIMSK |= (1<<OCIE0);
	/* Configure timer0 control register
	 * 1. Non PWM mode FOC0=1
	 * 2. CTC Mode WGM01=1 & WGM00=0
	 * 3. No need for OC0 in this example so COM00=0 & COM01=0
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1<<FOC0) | (1<<WGM01) | (1<<CS02) | (1<<CS00);
}


void Timer0_setCallBack(void(*Ptr2Func)(void))
{
	g_Timer0_Call_Back_Ptr = Ptr2Func;
}


/* Interrupt Service Routine for Timer0 compare mode */
ISR(TIMER0_COMP_vect)
{
	/* Check if the Timer0_setCallBack is already called */
	if(g_Timer0_Call_Back_Ptr != NULL_PTR)
	{
		/* Call the function in the scheduler using call-back concept */
		(*g_Timer0_Call_Back_Ptr)();
	}
}


