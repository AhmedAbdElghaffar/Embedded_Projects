/*************************************************************************
 * Module: Keypad
 *
 * File Name: Keypad.c
 *
 * Description: All functions for Keypad
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time:  5 / 1 / 2020, 9:20 PM
 *
 *************************************************************************/

#include "Keypad.h"
/*******************************************************************
 *
 *    				Functions Prototype (Private)
 *
 ********************************************************************/

#if(NUMBER_OF_COLUMNS==3)
	static uint8 keybad_4x3_adjustKeyNumber(uint8 a_Button_Number);
#elif(NUMBER_OF_COLUMNS==4)
	static uint8 keybad_4x4_adjustKeyNumber(uint8 a_Button_Number);
#endif

/*
 *Function Name: KEYBAD_GetPressedKey
 *
 * Description: This function finds the exact button that was pressed in the keypad
 *
 * Arguments:
 *
 * 		Inputs:
 * 			No inputs (void)
 * 		Outputs:
 *
 * 	returns:
 * 		uint8 number: the pressed number
 *
 */
uint8 KEYBAD_GetPressedKey(void){
	uint8 row,col;
	while(1)
	{
		for(col=0 ; col < NUMBER_OF_COLUMNS ; col++)
		{
			#if(CONNECTION_MODE==1)  /* Internal PULL UP*/
				KEYPAD_PORT_DIR= (0b00010000<<col);
				KEYPAD_PORT_OUT= ~(0b00010000<<col);

			#elif(CONNECTION_MODE==2) /* External PULL UP*/
				KEYPAD_PORT_DIR= (0b00010000<<col);
				KEYPAD_PORT_OUT= ~(0b00010000<<col) & (0xf0);

			#elif(CONNECTION_MODE==3) /* PULL DOWN */
				KEYPAD_PORT_DIR= (0b00010000<<col);
				KEYPAD_PORT_OUT= (0b00010000<<col);
			#endif

			for(row=0 ;  row < NUMBER_OF_ROWS ; row++)
			{
				#if(CONNECTION_MODE==3) /*PULL DOWN CONNECTION*/
					if(BIT_IS_SET(KEYPAD_PORT_IN,row))
					{
						#if(NUMBER_OF_COLUMNS==3)
							return (keybad_4x3_adjustKeyNumber(row*4+col+1));
						#elif(NUMBER_OF_COLUMNS==4)
							return (keybad_4x4_adjustKeyNumber(row*4+col+1));
						#endif
					}
				#else
					if(BIT_IS_CLEARED(KEYPAD_PORT_IN,row))
					{
						#if(NUMBER_OF_COLUMNS==3)
							return keybad_4x3_adjustKeyNumber((row*NUMBER_OF_COLUMNS)+col+1);
						#elif(NUMBER_OF_COLUMNS==4)
							return keybad_4x4_adjustKeyNumber((row*NUMBER_OF_COLUMNS)+col+1);
						#endif
					}
				#endif
			}
		}
	}

}

#if(NUMBER_OF_COLUMNS==3)

/*
 * Function used to map the pressed number to its corresponding
 * true value according to Proteus Keybad 4*3, it's static as it will only be used in this file
 *
 * Function Name: keybad_4x3_adjustKeyNumber
 *
 * Description: This Function used to map the pressed number to its corresponding
 * 				true value according to Proteus Keybad 4*3
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1- a_Button_Number : The actual pressed key vale
 * 		Outputs:
 *
 * 	returns:
 * 		uint8 number: The corrected number
 *
 */
	static uint8 keybad_4x3_adjustKeyNumber(uint8 a_Button_Number){
		switch(a_Button_Number)
		{
		case 10:
			return '*';
			break;
		case 11:
			return 0;
			break;
		case 12:
			return '#';
			break;
		default:
			return a_Button_Number;
		}
	}
#elif(NUMBER_OF_COLUMNS==4)

	/*
	 *Function Name: keybad_4x4_adjustKeyNumber
	 *
	 * Description: Function used to map the pressed number to its corresponding
	 * 				true value according to Proteus Keybad 4*4, it's static as it will only be used in this file
	 *
	 * Arguments:
	 *
	 * 		Inputs:
	 * 			1- a_Button_Number : The actual pressed key vale
	 * 		Outputs:
	 *
	 * 	returns:
	 * 		uint8 number: The corrected number
	 *
	 */

	static uint8 keybad_4x4_adjustKeyNumber(uint8 a_Button_Number){
		switch(a_Button_Number)
		{
		case 1:
			return 7;
			break;
		case 2:
			return 8;
			break;
		case 3:
			return 9;
			break;
		case 4:
			return '%';		/* ASCII Code of '%' */
			break;
		case 5:
			return 4;
			break;
		case 6:
			return 5;
			break;
		case 7:
			return 6;
			break;
		case 8:
			return '*';		/* ASCII Code of '*' */
			break;
		case 9:
			return 1;
			break;
		case 10:
			return 2;
			break;
		case 11:
			return 3;
			break;
		case 12:
			return '-';		/* ASCII Code of '-' */
			break;
		case 13:
			return 13;		/* ASCII Code of enter */
			break;
		case 14:
			return 0;
			break;
		case 15:
			return '=';		/* ASCII Code of '=' */
			break;
		case 16:
			return '+';		/* ASCII Code of '+' */
			break;
		default:
			return a_Button_Number;
		}
	}
#endif

/*
 *Function Name: stop
 *
 * Description: used to get only one value even if one key is kept pressed
 *
 * Arguments:
 *
 * 		Inputs:
 * 			No inputs (void)
 * 		Outputs:
 *
 * 	returns:
 * 		No returns, void
 *
 */
void stop(void){
	uint8 row;
	while(1)
	{
			for(row=0 ;  row < NUMBER_OF_ROWS ; row++)
			{
					while(BIT_IS_CLEARED(KEYPAD_PORT_IN,row));
			}
			return;
	}
}



