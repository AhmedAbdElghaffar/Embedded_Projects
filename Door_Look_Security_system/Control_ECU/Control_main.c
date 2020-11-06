/*************************************************************************
 * Module: Control_main
 *
 * File Name: Control_main.c
 *
 * Description: Main functionality of the Control ECU
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time:  7 / 02 / 2020, 4:30 PM
 *
 *************************************************************************/

#include "Control_Application.h"


int main(void){

	/********************************* UART different configurations ********************************
	 * 1- Transfer Speed: Normal, Double
	 * 2- Data size: 	  Five , Six , Seven , Eight
	 * 3- Parity: 		  Disabled , Even , Odd
	 * 4- Stop bits:	  One ,  Two
	 * 5- Baude rate
	 */
	UART_Configurations UART_Config={Double,Eight,Disabled,One,9600};


	UART_init(&UART_Config);				/*initializing the UART module using the configuration structure*/
	while(UART_receiveByte() != M2_READY);	/*Polling untill a specific bit is sent for synchronization between the 2 micro-controllers*/
	EEPROM_init(400000);					/*initialize the EEPROM to transmit/receive data with a 400000 transfer rate*/

	/*Function used to interact with the user only at the first time after buying a the new system(Get the first time password)*/
	firstTimeOpeningNewSystem();

	SET_BIT(SREG,7);   					/*Enable global interrupts*/

	TIMER1_init(&Timer1_Routine);		/*initialize the timer and define the function that will be called at the call back request*/
	TIMER1_stop();						/*Pause the timer until we need to resume it again */
	MOTOR_init();						/*Initialize the motor driver*/

	while(1)
	{
		controlEcuOptions();			/*The function used to perform all the operations of the Control ECU*/
	}

}
