/*----------------------------------------------------------------------------------------------------------
[MODULE NAME]: External EEPROM

[FILE NAME]: external_eeprom.h

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Header file for the External EEPROM driver.

-----------------------------------------------------------------------------------------------------------*/


#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

/*--------------------------------------------INCLUDES-----------------------------------------------------*/

#include "std_types.h"


/*-----------------------------------Difinations and configurations----------------------------------------*/

#define SUCCESS 1
#define FAIL 0


/*---------------------------------------FUNCTION DECLARATIONS---------------------------------------------*/

/* Responsible for initiating the EEPROM Module by just initiate the I2C. */
void EEPROM_init(void);
/* Responsible for writing a byte in the EEPROM. */
uint8 EEPROM_writeByte(uint16 a_address,uint8 a_data);
/* Responsible for reading a byte from the EEPROM. */
uint8 EEPROM_readByte(uint16 a_address,uint8 *data);
 
#endif /* EXTERNAL_EEPROM_H_ */
