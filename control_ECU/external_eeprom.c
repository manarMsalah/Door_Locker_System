/*----------------------------------------------------------------------------------------------------------
[MODULE NAME]: External EEPROM

[FILE NAME]: external_eeprom.c

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Source file for the External EEPROM driver.

-----------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------INCLUDES-----------------------------------------------------*/

#include "i2c.h"
#include "external_eeprom.h"


/*----------------------------------------FUNCTION DIFINATIONS---------------------------------------------*/

void EEPROM_init(void)
{
	I2C_init();
}


uint8 EEPROM_writeByte(uint16 a_address, uint8 a_data)
{
	/* Send the start bit */
	I2C_start();
	/* Make sure it done. */
    if (I2C_getStatus() != I2C_START)
        return FAIL;
		
    /* Send the device address + the last three bits in the memory location. */
    I2C_write((uint8)(0xA0 | ((a_address & 0x0700)>>7)));
    /* Make sure it done. */
    if (I2C_getStatus() != I2C_MT_SLA_WRITE_ACK)
        return FAIL;
		 
    /* Send the required memory location address (firts 8 bits). */
    I2C_write((uint8)(a_address));
    /* Make sure it done. */
    if (I2C_getStatus() != I2C_MT_DATA_ACK)
        return FAIL;
		
    /* write byte to EEPROM. */
    I2C_write(a_data);
    /* Make sure it done. */
    if (I2C_getStatus() != I2C_MT_DATA_ACK)
        return FAIL;

    /* Send the stop bit. */
    I2C_stop();
	
    return SUCCESS;
}


uint8 EEPROM_readByte(uint16 a_address, uint8 *data)
{
	/* Send the start bit. */
	I2C_start();
	/* Make sure it done. */
    if (I2C_getStatus() != I2C_START)
        return FAIL;
		
    /* Send the device address + the last three bits in the memory location. */
    I2C_write((uint8)((0xA0) | ((a_address & 0x0700)>>7)));
    /* Make sure it done. */
    if (I2C_getStatus() != I2C_MT_SLA_WRITE_ACK)
        return FAIL;
		
    /* Send the required memory location address (firts 8 bits). */
    I2C_write((uint8)(a_address));
    /* Make sure it done. */
    if (I2C_getStatus() != I2C_MT_DATA_ACK)
        return FAIL;
		
    /* Send the repeated start bit. */
    I2C_start();
    /* Make sure it done. */
    if (I2C_getStatus() != I2C_REPEAT_START)
        return FAIL;
		
    /* Send the device address + the last three bits in the memory location + R=1. */
    I2C_write((uint8)((0xA0) | ((a_address & 0x0700)>>7) | 1));
    /* Make sure it done. */
    if (I2C_getStatus() != I2C_MT_SLA_READ_ACK)
        return FAIL;

    /* Read byte from memory without sending ACK */
    *data = I2C_readWithNACK();
    /* Make sure it done. */
    if (I2C_getStatus() != I2C_MR_DATA_NACK)
        return FAIL;

    /* Send the stop bit. */
    I2C_stop();

    return SUCCESS;
}
