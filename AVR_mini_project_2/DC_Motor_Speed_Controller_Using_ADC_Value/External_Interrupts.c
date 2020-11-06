/*******************************************************************
 * File name: External_Inturrupts.c
 *
 * Description: External Interrupts functions
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time: 7 / 1 / 2020,  7:30 PM
 *
 *********************************************************************/

#include "External_Interrupts.h"


/*
 * Next 3 pointers to functions are to refer to the functions that
 * will be executed when the interrupts handler starts executing.
 * (Global variables to hold the address of the call back function in the application)
 */
static void(*volatile g_INT0_CallBack)(void)=NULL;
static void(*volatile g_INT1_CallBack)(void)=NULL;
static void(*volatile g_INT2_CallBack)(void)=NULL;


/******************************************************************************
 * 						Functions Definitions
 ****************************************************************************/


/*
 * Function Name: INT0_init
 *
 * Description: This function is responsible for initializing INT0 and
 * choosing the function that will be executed by Interrupt handler of INT0
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1- const INT0_configType *Config_data_0
 * 					A constant data pointer to a structure that has the initializing values of INT0
 * 			2- void(*const CallBack_ptr_INT0)(void)
 * 					A pointer to function that receives the address of
 * 					function that will be executed by Interrupt handler of INT0
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), INT0 is now initialized.
 */

void INT0_init(const INT0_configType *Config_data_0,void(*const CallBack_ptr_INT0)(void)){
	MCUCR |= (MCUCR & 0xfc) | (Config_data_0->Mode_0);
	GICR |= (1<<INT0);
	CLEAR_BIT(DDRD,PD2);
	g_INT0_CallBack=CallBack_ptr_INT0;
}


/*
 * Function Name: INT1_init
 *
 * Description: This function is responsible for initializing INT1 and
 * choosing the function that will be executed by Interrupt handler of INT1
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1- const INT1_configType *Config_data_1
 * 					A constant data pointer to a structure that has the initializing values of INT1
 * 			2- void(*const CallBack_ptr_INT1)(void)
 * 					A pointer to function that receives the address of
 * 					function that will be executed by Interrupt handler of INT1
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), INT1 is now initialized.
 */

void INT1_init(const INT1_configType *Config_data_1,void(*const CallBack_ptr_INT1)(void)){
	MCUCR |= (MCUCR & 0xf3) | (Config_data_1->Mode_1);
	GICR |= (1<<INT1);
	CLEAR_BIT(DDRD,PD3);
	g_INT1_CallBack=CallBack_ptr_INT1;
}

/*
 * Function Name: INT2_init
 *
 * Description: This function is responsible for initializing INT2 and
 * choosing the function that will be executed by Interrupt handler of INT2
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1- const INT2_configType *Config_data_2
 * 					A constant data pointer to a structure that has the initializing values of INT2
 * 			2- void(*const CallBack_ptr_INT2)(void)
 * 					A pointer to function that receives the address of
 * 					function that will be executed by Interrupt handler of INT2
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), INT2 is now initialized.
 */
void INT2_init(const INT2_configType *Config_data_2,void(*const CallBack_ptr_INT2)(void)){
	MCUCSR |= ((Config_data_2->Mode_2)<<ISC2);
	GICR |= (1<<INT2);
	CLEAR_BIT(DDRB,PB2);
	g_INT2_CallBack=CallBack_ptr_INT2;
}


/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(INT0_vect){
	if(g_INT0_CallBack!=NULL){
		/* Call the Call Back function in the application after the edge is detected */
		(*g_INT0_CallBack)();
	}
}

ISR(INT1_vect){
	if(g_INT2_CallBack!=NULL){
		/* Call the Call Back function in the application after the edge is detected */
		(*g_INT2_CallBack)();
	}

}

ISR(INT2_vect){
	if(g_INT2_CallBack!=NULL){
		/* Call the Call Back function in the application after the edge is detected */
		(*g_INT2_CallBack)();
	}

}
