/*----------------------------------------------------------------------------------------------------------

[FILE NAME]: timer.h

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Header file to timer module

-----------------------------------------------------------------------------------------------------------*/

#ifndef TIMER_H_
#define TIMER_H_

/*--------------------------------------------INCLUDES-----------------------------------------------------*/

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"


/*----------------------------------Difinations and configurations-----------------------------------------*/

#define NUMBER_OF_TICKS 250


/*--------------------------------------FUNCTION DECLARATIONS----------------------------------------------*/

/* Points to the required function */
void Timer0_setCallBack(void (*Ptr2Func)(void));

/* Description: this function responsible for :
*	1. Initialize Timer0 HW Driver to run in CTC Mode
*	2. Set the Compare Register Value to generate interrupt */
void timer0_init_CTC_mode(unsigned char tick);

#endif /* TIMER_H_ */
