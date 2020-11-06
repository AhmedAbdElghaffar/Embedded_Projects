/*************************************************************************
 * Module: External EEPROM
 *
 * File Name: EEPROM.c
 *
 * Description: EEPROM main functions
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time:  7 / 02 / 2020, 1:55 PM
 *
 *************************************************************************/

#include "EEPROM.h"
#include "TWI.h"


/*
 * Function Name: EEPROM_init
 *
 * Description: This function is responsible for initializing the EEPROM module by initializing the I2C serial communication
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-uint32 Baud:
 * 				The required transfer rate of the I2C module
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the EEPROM is initialized
 */
void EEPROM_init(uint32 Baud){

	I2C_init(Baud);   /*initializing the EEPROM module by initializing the I2C serial communication*/

}

/*
 * Function Name: EEPROM_write
 *
 * Description: Function used to write data to a specific address in the EEPROM
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-uint16 a_address:
 * 				The required address of the EEPROM to write the data in
 * 			2-uint8 a_data:
 * 				The required datat to be written
 *
 * 	returns:
 * 		uint8 Success/Failure condition: tells if the operations succeeded or not
 */
uint8 EEPROM_write(uint16 a_address ,uint8 a_data){

	I2C_start();    					/*Send the start bit*/

	if( I2C_getStatus() != TWI_START )  /*Check that the start bit is sent*/
	{
		return ERROR;
	}

	I2C_write((uint8)(((a_address & 0x0700)>>7) | (0x00A0)));  /*Send the most significant 3 bits of the address + write bit*/
	if( I2C_getStatus() != TWI_MT_SLA_W_ACK )  					/*Check that the address is written to the slave and an ack received*/
	{
		return ERROR;
	}

	I2C_write((uint8)(a_address));					/*Send the least significant 8 bits of the address*/
	if( I2C_getStatus() != TWI_MT_DATA_ACK )		/*Check that the address(Data) is written to the slave and an ack received*/
	{
		return ERROR;
	}

	I2C_write(a_data);							/*Send the required data to the required address*/
	if( I2C_getStatus() != TWI_MT_DATA_ACK )	/*Check that the data is written and an ack is received*/
	{
		return ERROR;
	}

	I2C_stop();				/*Send a stop bit to end the I2C frame*/

	return SUCCESS;
}

/*
 * Function Name: EEPROM_write
 *
 * Description: Function used to read data from a specific address in the EEPROM and save it in a specific vale(the value is passed by reference)
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-uint16 a_address:
 * 				The required address of the EEPROM to write the data in
 * 			2-uint8 *a_data:
 * 				variable passed by reference to carry the value in the required address of the EEPROM
 *
 * 	returns:
 * 		uint8 Success/Failure condition: tells if the operations succeeded or not
 */
uint8 EEPROM_read(uint16 a_address ,uint8 *a_data){


	I2C_start();							/*Send the start bit*/
	if( I2C_getStatus() != TWI_START )		/*Check that the start bit is sent*/
	{
		return ERROR;
	}

	I2C_write((uint8)(((a_address & 0x0700)>>7) | (0xA0)));			/*Send the most significant 3 bits of the address + write bit*/
	if( I2C_getStatus() != TWI_MT_SLA_W_ACK )						/*Check that the address is written to the slave and an ack received*/
	{
		return ERROR;
	}

	I2C_write((uint8)(a_address));						/*Send the least significant 8 bits of the address*/
	if( I2C_getStatus() != TWI_MT_DATA_ACK )			/*Check that the address(Data) is written to the slave and an ack received*/
	{
		return ERROR;
	}

	I2C_start();										/*SEND A REPEATED START BIT*/
	if( I2C_getStatus() != TWI_REP_START )				/*Check that the repeated start bit is sent*/
	{
		return ERROR;
	}

	I2C_write((uint8)(((a_address & 0x0700)>>7) | (0xA1)));		/*Send the most significant 3 bits of the required data to read data from and send a read bit */
	if( I2C_getStatus() != TWI_MT_SLA_R_ACK )					/*Check that the address is sent and a read bit is sent*/
	{
		return ERROR;
	}


	*a_data = I2C_readWithNACK();					/*read data with negative ack to state that this is the last byte to be read*/
	if( I2C_getStatus() != TWI_MR_DATA_NACK )		/*Check that Master received data but doesn't send ACK to slave*/
	{
		return ERROR;
	}

	I2C_stop();				/*Send a stop bit to end the I2C frame*/


	return SUCCESS;
}

