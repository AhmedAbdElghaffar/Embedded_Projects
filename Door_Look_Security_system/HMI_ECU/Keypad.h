/*************************************************************************
 * Module: Keypad
 *
 * File Name: Keypad.h
 *
 * Description: Common Keypad Configurations
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time:  5 / 1 / 2020, 9:30 PM
 *
 *************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "Common_Macros.h"
#include "Micro_Config.h"
#include "Std_types.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/


/*********** Keybad Mode*********
 * Choose 3 for 3 columns Keybad
 * choose 4 for 4 Columns Keybad
 ********************************/
#define NUMBER_OF_COLUMNS 	3
#define NUMBER_OF_ROWS		4

#if(NUMBER_OF_COLUMNS==3 | NUMBER_OF_COLUMNS==4)
#else
#error "The Number of Columns is Wrong(It should be only 3 or 4)"
#endif

/******** Connection Mode************
 * Choose 1 for Internal PULL UP
 * Choose 2 for External PULL UP
 * Choose 3 for PULL dOWN
 ***********************************/
#define CONNECTION_MODE 1

#if(CONNECTION_MODE==1 | CONNECTION_MODE==2 | CONNECTION_MODE==3)
#else
#error "Error in choosing Connection Mode"
#endif

/****************** PORT OPTIONS**********
 * Choose the connection port A,B,C,D
 *****************************************/
#define KEYPAD_PORT_OUT 	PORTA
#define KEYPAD_PORT_DIR 	DDRA
#define KEYPAD_PORT_IN		PINA



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

uint8 KEYBAD_GetPressedKey();
void stop(void);

#endif /* KEYPAD_H_ */
