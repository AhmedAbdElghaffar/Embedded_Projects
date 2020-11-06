/*************************************************************************
 * Module: I2C
 *
 * File Name: TWI.h
 *
 * Description: TWI Configuratins
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time:  06 / 02 / 2020, 9:15 PM
 *
 *************************************************************************/

#ifndef TWI_H_
#define TWI_H_

#include "Common_Macros.h"
#include "Std_types.h"
#include "Micro_Config.h"


/********************************************************************************
 * 								Type Declarations
 ********************************************************************************/

typedef enum{
	F_CPU_1 , F_CPU_4 , F_CPU_16 , F_CPU_64
}TWI_Prescaler;

typedef struct			/* Structure used to configure the I2C module */
{
	TWI_Prescaler Prescaler;
	uint32 Baud;
	uint8 Address;
}TWI_Configurations;

/****************************************************************************************
 * 								TWI Status Register Values
 ****************************************************************************************/

#define TWI_START         0x08 		/* start has been sent */
#define TWI_REP_START     0x10 		/* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 		/* Master transmit ( slave address + Write request ) to slave + Ack received from slave */
#define TWI_MT_SLA_R_ACK  0x40 		/* Master transmit ( slave address + Read request ) to slave + Ack received from slave */
#define TWI_MT_DATA_ACK   0x28 		/* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 		/* Master received data and send ACK to slave */
#define TWI_MR_DATA_NACK  0x58 		/* Master received data but doesn't send ACK to slave */

/********************************************************************************
 * 								Function Prototypes
 ********************************************************************************/

/*Description: This function is responsible for initializing the I2C According to the chose mode*/
void I2C_init(uint32 Baud);

/*Description: This function is responsible for sending the start bit in the i2c frame*/
void I2C_start(void);

/*Description: This function is responsible for sending the stop bit in the i2c frame*/
void I2C_stop(void);

/*Description: This function is responsible for writing the data*/
void I2C_write(uint8);

/*Description: function used to read a data and receive an ack*/
uint8 I2C_readWithACK(void);

/*Description: function used to read a data and receive a negative ack*/
uint8 I2C_readWithNACK(void);

/*Description: function used get the status in the TWSR status register*/
uint8 I2C_getStatus(void);


#endif /* TWI_H_ */

