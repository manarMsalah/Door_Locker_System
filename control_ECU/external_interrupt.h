/*----------------------------------------------------------------------------------------------------------

[FILE NAME]: external_interrupt.h

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Header file for external interrupt module

-----------------------------------------------------------------------------------------------------------*/

#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_

/*--------------------------------------------INCLUDES-----------------------------------------------------*/

#include "micro_config.h"
#include "common_macros.h"
#include "std_types.h"


/*--------------------------------------FUNCTION DECLARATIONS----------------------------------------------*/

/* Points to the required function */
void INT1_setCallBack(void (*Ptr2Func)(void));

/* Initialize INT1 HW Driver */
void INT1_Init(void);

#endif /* EXTERNAL_INTERRUPT_H_ */
