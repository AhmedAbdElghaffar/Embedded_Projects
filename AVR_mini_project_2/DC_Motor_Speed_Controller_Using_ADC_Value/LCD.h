/*************************************************************************
 * Module: LCD
 *
 * File Name: LCD.h
 *
 * Description: LCD Configuratins
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time:  28 / 12 / 2019, 2:16 PM
 *
 *************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "Micro_config.h"
#include "Common_Macros.h"
#include "Std_types.h"

#include <stdlib.h>			/* You have to check if it's only included in one place */

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

#define DATA_BITS_MODE 8		/* 4 for 4 bits mode ,  8 for 8 bits mode */

#if(DATA_BITS_MODE==4)
	#define UPPER_PORT_PINS
	/*
	 * If you choose pins 0 to 3 to be data/command pins in any port output select True
	 * IF you choose pins 4 to 7 to be data/command pins in any port output select False
	 */
	#if False
	#undef UPPER_PORT_PINS
	#endif
#endif

/*
 * Defining Controlling pins and Ports
 */
#define RS PD4							/* Data/command pin */
#define RW PD5							/* Read/write pin   */
#define E  PD6							/* Enable pin       */

#define LCD_CTRL_PORT 		PORTD
#define LCD_CTRL_PORT_DIR 	DDRD

#define LCD_DATA_PORT 		PORTC
#define LCD_DATA_PORT_DIR 	DDRC

#define CURSOR_OFF			  	0x0c
#define CURSOR_ON				0x0E
#define	MOVE_CURSOR_LEFT		0X10
#define MOVE_CURSOR_RIGHT		0X14
#define MOVE_CURSOR_LOCATION	0x80
#define CLEAR_DISPLAY			0x01

#if(DATA_BITS_MODE==4)
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define ONE_LINE_LCD_Four_BIT_MODE 0x20

#elif(DATA_BITS_MODE==8)
#define TWO_LINE_LCD_EIGHT_BITS_MODE 	0x38
#define ONE_LINE_LCD_EIGHT_BITS_MODE 	0x30
#endif




/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_init(void);
void LCD_sendCommand(uint8);
void LCD_displayCharacter(uint8);
void LCD_displayString(const char*);
void LCD_goToRowColumn(uint8,uint8);
void LCD_clearScreen(void);
void LCD_integerToString(sint16);
void LCD_displayStringRowColumn(uint8,uint8,const char*);

#endif /* LCD_H_ */
