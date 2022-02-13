/*----------------------------------------------------------------------------------------------------------
[MODULE NAME]: Micro - Configuration

[FILE NAME]: micro_config.h

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: File include all Microcontroller libraries

-----------------------------------------------------------------------------------------------------------*/

#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

/* 8MHz Clock frequency */
#ifndef F_CPU
#define F_CPU 8000000UL
#endif  

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#endif /* MICRO_CONFIG_H_ */
