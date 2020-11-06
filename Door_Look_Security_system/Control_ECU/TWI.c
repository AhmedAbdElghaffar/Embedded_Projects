/*************************************************************************
 * Module: I2C
 *
 * File Name: TWI.c
 *
 * Description: TWI Main Functions
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time:  06 / 02 / 2020, 9:20 PM
 *
 *************************************************************************/


#include "TWI.h"

/*
 * Function Name: I2C_init
 *
 * Description: This function is responsible for initializing the I2C According to the chose mode
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-uint32 Baud : The requaired transfer rate
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the I2C module is initialized
 */

void I2C_init(uint32 Baud){

	uint8 TWBR_eqn_num , TWBR_eqn_den;  /*Two variables used to calculate the TWBR*/

	/*********************** Specify TWI registers as follows ***************
	 * 1- Select the TWBR value to select the transfer rate
	 * 2- Select the prescaler to be zero (TWSR = 0 )
	 * 3- Select the MC address in case that in master wants to call my device (address = 0x01 <<1)
	 * 4- Enable the TWI by setting TWEN in the TWCR register
	 *************************************************************************/
	TWBR_eqn_num=((F_CPU/Baud)-16);
	TWBR_eqn_den=2;
	TWBR=TWBR_eqn_num/TWBR_eqn_den;
	TWSR = 0x00;
	TWAR=0x02;
	TWCR=(1<<TWEN);
}

/*
 * Function Name: I2C_start
 *
 * Description: This function is responsible for sending the start bit in the i2c frame
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-NO inputs (void)
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the start bit is sent
 */

void I2C_start(void){

	/*********************** Specify TWCR registers as follows ***************
	 * 1- Clear the TWINT flag by writing a logical 1
	 * 2- Enable the TWI module
	 * 3- Enable sending the start bit by setting TWSTA
	 *************************************************************************/
	TWCR=(1<<TWINT) | (1<<TWEN) | (1<<TWSTA);
	while(BIT_IS_CLEARED(TWCR,TWINT))
	{
		/*Polling*/
	}
}

/*
 * Function Name: I2C_stop
 *
 * Description: This function is responsible for sending the stop bit in the i2c frame
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-No inputs (void)
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the stop bit is sent
 */
void I2C_stop(void){

	/*********************** Specify TWCR registers as follows ***************
	 * 1- Clear the TWINT flag by writing a logical 1
	 * 2- Enable the TWI module
	 * 3- Enable sending the stop bit by setting TWSTO
	 *************************************************************************/
	TWCR=(1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

/*
 * Function Name: I2C_write
 *
 * Description: This function is responsible for writing the data
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-uint8 a_data: the required data to be written
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the data is written in the frame
 */
void I2C_write(uint8 a_data){

	TWDR=a_data;			/*Load the TWDR with the data*/

	/*********************** Specify TWCR registers as follows ***************
	 * 1- Clear the TWINT flag by writing a logical 1
	 * 2- Enable the TWI module
	 *************************************************************************/
	TWCR=(1<<TWINT) | (1<<TWEN);
	while(BIT_IS_CLEARED(TWCR,TWINT))
	{
		/*Polling*/
	}
}

/*
 * Function Name: I2C_readWithACK
 *
 * Description: function used to read a data and receive a ack
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-1-No inputs (void)

 * 	returns:
 * 		returns the TWDR value which represents the data to be read
 */
uint8 I2C_readWithACK(void){


	/*********************** Specify TWCR registers as follows ***************
	 * 1- Clear the TWINT flag by writing a logical 1
	 * 2- Enable the TWI module
	 * 3- Enable sending the ACK by setting TWEA
	 *************************************************************************/
	TWCR=(1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(BIT_IS_CLEARED(TWCR,TWINT))
	{
		/*Polling*/
	}
	return TWDR;			/* Read the data from the TWDR*/
}

/*
 * Function Name: I2C_readWithNACK
 *
 * Description: function used to read a data and receive a negative ack
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-No inputs (void)

 * 	returns:
 * 		returns the TWDR value which represents the last data to be read
 */
uint8 I2C_readWithNACK(void){


	/*********************** Specify TWCR registers as follows ***************
	 * 1- Clear the TWINT flag by writing a logical 1
	 * 2- Enable the TWI module
	 * 3- Enable sending the Negative ACK by clearing the TWEA
	 *************************************************************************/
	TWCR=(1<<TWINT) | (1<<TWEN);
	while(BIT_IS_CLEARED(TWCR,TWINT))
	{
		/*Polling*/
	}
	return TWDR;			/* Read the data from the TWDR*/
}

/*
 * Function Name: I2C_getStatus
 *
 * Description: function used get the status in the TWSR status register
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-1-No inputs (void)

 * 	returns:
 * 		returns the TWDR value which represents the data to be read
 */
uint8 I2C_getStatus(void){

	return (TWSR & 0xf8);    /*Return the Most significant 5 bits from the TWSR*/
}
