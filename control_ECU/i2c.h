/*----------------------------------------------------------------------------------------------------------
[MODULE NAME]: I2C

[FILE NAME]: i2c.h

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: Header file for the I2C driver.

-----------------------------------------------------------------------------------------------------------*/

#ifndef I2C_H_
#define I2C_H_

/*--------------------------------------------INCLUDES-----------------------------------------------------*/

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*-----------------------------------Difinations and configurations----------------------------------------*/

/* I2C Status Bits in the TWSR Register from data sheet. */

#define I2C_START                    0x08
#define I2C_REPEAT_START             0x10
/* Master transmit slave address and write request to slave + Ack received from slave. */
#define I2C_MT_SLA_WRITE_ACK         0x18
/* Master transmit slave address and read request to slave + Ack received from slave. */
#define I2C_MT_SLA_READ_ACK          0x40
/* Master transmit data and ACK has been received from Slave. */
#define I2C_MT_DATA_ACK              0x28
/* Master received data and send ACK to slave. */
#define I2C_MR_DATA_ACK              0x50
/* Master received data but doesn't send ACK to slave. */
#define I2C_MR_DATA_NACK             0x58


/*-------------------------------------------FUNCTION DECLARATIONS-----------------------------------------*/

/* Responsible for initiating and enabling I2C. */
void I2C_init(void);
/* Responsible for sending the start bit. */
void I2C_start(void);
/* Responsible for sending the stop bit. */
void I2C_stop(void);
/* Responsible for sending byte. */
void I2C_write(uint8 a_data);
/* Responsible for receiving byte with ack. */
uint8 I2C_readWithACK(void);
/* Responsible for receiving byte without ack. */
uint8 I2C_readWithNACK(void);
/* Responsible for returning the status of the I2C logic to make sure it done correctly. */
uint8 I2C_getStatus(void);


#endif /* I2C_H_ */
