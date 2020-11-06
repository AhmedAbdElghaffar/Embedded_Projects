/*************************************************************************
 * Module: LCD
 *
 * File Name: LCD.c
 *
 * Description: All functions for LCD
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time:  28 / 12 / 2019, 2:20 PM
 *
 *************************************************************************/
#include "LCD.h"
/*
 * Function Name: LCD_init
 *
 * Description: This function is responsible for initializing the LCD According to the chose mode
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-No inputs (void)
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the LCD is initialized
 */
void LCD_init(void){

	LCD_CTRL_PORT_DIR |=(1<<RS) | (1<<RW) | (1<<E);
	#if(DATA_BITS_MODE==4)
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT_DIR |=0xf0;
		#else
			LCD_DATA_PORT_DIR |=0x0f;
		#endif
		LCD_sendCommand(FOUR_BITS_DATA_MODE); 			/* Switch LCD to bits mode */
		LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
	#elif(DATA_BITS_MODE==8)
		LCD_DATA_PORT_DIR=0xff;
		LCD_sendCommand(TWO_LINE_LCD_EIGHT_BITS_MODE);		/* Enable the 2lines and 8bit mode */
	#endif
	LCD_sendCommand(CURSOR_OFF);			/* Cursor off */
	LCD_sendCommand(CLEAR_DISPLAY);			/* clear_display*/
}

/*
 * Function Name: LCD_sendCommand
 *
 * Description: This function is responsible for sending a specific command to the LCD
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-uint8 (char) a_command
 *
 * 				this argument indicates the sent command to the LCD
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the LCD will receive the required command
 */

void LCD_sendCommand(uint8 a_command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS);		/* Clears RS to send Command*/
	CLEAR_BIT(LCD_CTRL_PORT,RW);		/* Clears the Read/write pin to write*/
	_delay_ms(1);						/* should be 1 micro but the hardware is not efficent so make it ms */
	SET_BIT(LCD_CTRL_PORT,E);			/* Enables the LCD*/
	_delay_ms(1);
	#if(DATA_BITS_MODE==4)

		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT =(LCD_DATA_PORT & 0x0f) | (a_command & 0xf0);
		#else
			LCD_DATA_PORT =(LCD_DATA_PORT & 0xf0) | ((a_command & 0xf0)>>4);
		#endif

		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT,E);			/* Disable the LCD*/
		_delay_ms(1);
		SET_BIT(LCD_CTRL_PORT,E);			/* Enables the LCD*/
		_delay_ms(1);


		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT =(LCD_DATA_PORT & 0x0f) | ((a_command & 0x0f)<<4);
		#else
			LCD_DATA_PORT =(LCD_DATA_PORT & 0xf0) | (a_command& 0x0f);
		#endif

		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT,E);			/* Disable the LCD*/
		_delay_ms(1);
	#elif(DATA_BITS_MODE==8)
		LCD_DATA_PORT=a_command;	/* Send a specific command to the LCD */
		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT,E);			/* Disable the LCD*/
		_delay_ms(1);
	#endif
}

/*
 * Function Name: LCD_displayCharacter
 *
 * Description: This function is responsible for sending a specific character to the LCD
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-uint8 (char) a_data
 *
 * 				this argument indicates the sent character to the LCD
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the LCD will receive the required character and display it
 */

void LCD_displayCharacter(uint8 a_data){

	SET_BIT(LCD_CTRL_PORT,RS);		/* Set RS to send Data*/
	CLEAR_BIT(LCD_CTRL_PORT,RW);		/* Clears the Read/write pin to write*/
	_delay_ms(1);						/* should be 1 micro but the hardware is not efficent so make it ms */
	SET_BIT(LCD_CTRL_PORT,E);			/* Enables the LCD*/
	_delay_ms(1);
	#if(DATA_BITS_MODE==4)

		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT =(LCD_DATA_PORT & 0x0f) | (a_data & 0xf0);
		#else
			LCD_DATA_PORT =(LCD_DATA_PORT & 0xf0) | ((a_data & 0xf0)>>4);
		#endif

		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT,E);			/* Disable the LCD*/
		_delay_ms(1);
		SET_BIT(LCD_CTRL_PORT,E);			/* Enables the LCD*/
		_delay_ms(1);


		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT =(LCD_DATA_PORT & 0x0f) | ((a_data & 0x0f)<<4);
		#else
			LCD_DATA_PORT =(LCD_DATA_PORT & 0xf0) | (a_data & 0x0f);
		#endif

		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT,E);			/* Disable the LCD*/
		_delay_ms(1);
	#elif(DATA_BITS_MODE==8)
		LCD_DATA_PORT=a_data;	/* Send a specific command to the LCD */
		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT,E);			/* Disable the LCD*/
		_delay_ms(1);
	#endif
}

/*
 * Function Name: LCD_displayString
 *
 * Description: This function is responsible for sending a string to the LCD
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-uint8* (pointer to char) a_str
 *
 * 				this argument indicates the sent string to the LCD
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the LCD will receive the required string and display it
 */

void LCD_displayString(const char *a_str){

	while(*a_str !='\0')
	{
		LCD_displayCharacter(*a_str);
		a_str++;
	}
}

/*
 * Function Name: LCD_goToRowColumn
 *
 * Description: This function is responsible for moving the cursor anywhere in the LCD
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-uint8 (pointer to char) a_row
 *
 * 				this argument indicates which row(line) the cursor will move to
 *
 * 			2-uint8 (pointer to char) a_col
 *
 * 				this argument indicates which column the cursor will move to
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the LCD cursor will move to the required location
 */
void LCD_goToRowColumn(uint8 a_row,uint8 a_col){

	uint8 address;		/* Address of the required location */
	switch(a_row)
	{
	case 0:
		address=0x00+a_col;		/*row 0, addresses from 0x00 to 0x0f */
		break;
	case 1:
		address=0x40+a_col;		/*row 1, addresses from 0x40 to 0x4f */
		break;
	case 2:
		address=0x10+a_col;		/*row 2, addresses from 0x10 to 0x1f */
		break;
	case 3:
		address=0x50+a_col;		/*row 3, addresses from 0x50 to 0x5f */
		break;
	}
	LCD_sendCommand(MOVE_CURSOR_LOCATION | address);
}

/*
 * Function Name: LCD_clearScreen
 *
 * Description: This function is responsible for clearing The screen
 *
 * Arguments:
 *
 * 		Arguments:
 *
 * 		Inputs:
 * 			1-No inputs (void)
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the LCD is cleared
 */

void LCD_clearScreen(void){
	LCD_sendCommand(CLEAR_DISPLAY);			/* clear_display*/
	LCD_goToRowColumn(0,0);					/*Locating the cursor at the beginning*/
}

/*
 * Function Name: LCD_integerToString
 *
 * Description: This function is responsible for displaying numbers in strings
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-sint16 (signed integer) a_data
 *
 * 				this argument represents number to be converted to string
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the number is now a string
 */

void LCD_integerToString(sint16 a_data){

	char buff[16];
	itoa(a_data,buff,10);
	LCD_displayString(buff);
}

/*
 * Function Name: LCD_displayStringRowColumn
 *
 * Description: This function is responsible for displaying a string in a specific location
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-uint8 (pointer to char) a_row
 *
 * 				this argument indicates which row(line) the cursor will move to
 *
 * 			2-uint8 (pointer to char) a_col
 *
 * 				this argument indicates which column the cursor will move to
 *
 * 			3-uint8* (pointer to char) a_str
 *
 * 				this argument indicates the sent string to the LCD
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the LCD cursor will move to the required location and string will show in this location
 */

void LCD_displayStringRowColumn(uint8 a_row,uint8 a_col,const char *Str)
{
	LCD_goToRowColumn(a_row,a_col); 		/* go to to the required LCD position */
	LCD_displayString(Str); 				/* display the string */
}
