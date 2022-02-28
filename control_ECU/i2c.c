/*----------------------------------------------------------------------------------------------------------
[MODULE NAME]: I2C

[FILE NAME]: i2c.c

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Source file for the I2C driver.

-----------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------INCLUDES-----------------------------------------------------*/
 
#include "i2c.h"

/*----------------------------------------FUNCTION DIFINATIONS---------------------------------------------*/

void I2C_init(void)
{
    /* The value of the bit rate register when the SCL frequency is 400 kbps, F_CPU is 8MHZ and pre-scaler is 1. */
    TWBR = 0x02;
    TWSR = 0x00;
    /* Address for this MC in case it is a slave device. */
    TWAR = 0xF0;
    /* Enable I2C module */
    TWCR = (1<<TWEN);
}

void I2C_start(void)
{
	/* Clear the TWINT flag, send the start bit and enable the I2C module to keep it set. */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    /* Polling on the TWINT flag until it clear to ensure that start bit is send. */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

void I2C_stop(void)
{
	/* Clear the TWINT flag, send the stop bit and enable the I2C module to keep it set. */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void I2C_write(uint8 a_data)
{
    /* Put the data On TWDR Register. */
    TWDR = a_data;
    /* Clear the TWINT flag and enable the I2C module to keep it set. */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Polling on the TWINT flag until it clear to ensure that the data is send. */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 I2C_readWithACK(void)
{
	/* Clear the TWINT flag, enable ack and enable the I2C module to keep it set. */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Polling on the TWINT flag until it clear to ensure that the data is received. */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read data. */
    return TWDR;
}

uint8 I2C_readWithNACK(void)
{
	/* Clear the TWINT flag and enable the I2C module to keep it set. */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Polling on the TWINT flag until it clear to ensure that the data is received. */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read data. */
    return TWDR;
}

uint8 I2C_getStatus(void)
{
    uint8 status;
    /* Masking to keep the prescaler bits. */
    status = TWSR & 0xF8;
    return status;
}
