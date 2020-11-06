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

#ifndef EEPROM_H_
#define EEPROM_H_

#include "TWI.h"

/**************************************************************
 * 						Preprocessor Constants
 *************************************************************/
#define ERROR		0
#define SUCCESS		1

/**************************************************************
 * 						Functions Prototypes
 *************************************************************/

/*Description: Function used to initialize the EEPROM module*/
void EEPROM_init(uint32 Baud);

/*Description: Function used to write data to a specific address in the EEPROM*/
uint8 EEPROM_write(uint16,uint8);

/*Description: Function used to read data from a specific address in the EEPROM and save it in a specific vale(the value is passed by reference)*/
uint8 EEPROM_read(uint16,uint8*);

#endif /* EEPROM_H_ */
