/*
 * HMI_main.c
 *
 *  Created on: Feb 9, 2020
 *      Author: ahmed
 */

#include "HMI_Application.h"

int main(void){

	/********************************* UART different configurations ********************************
	 * 1- Transfer Speed: Normal, Double
	 * 2- Data size: 	  Five , Six , Seven , Eight
	 * 3- Parity: 		  Disabled , Even , Odd
	 * 4- Stop bits:	  One ,  Two
	 * 5- Baude rate
	 */
	UART_Configurations UART_config={Double,Eight,Disabled,One,9600};
	UART_init(&UART_config);		/*initializing the UART module using the configuration structure*/
	UART_sendByte(M2_READY);		/*send a byte to enable the two micros synchronization*/
	LCD_init();						/*initiate the LCD*/
	/*Function used to interact with the user only at the first time after buying a the new system(Get the first time password)*/
	firstTimeOpeningNewSystem();
	SET_BIT(SREG,7);					/*Enable global interrupts*/
	TIMER1_init(&Timer1_Routine);		/*initialize the timer and define the function that will be called at the call back request*/
	TIMER1_stop();						/*Pause the timer until we need to resume it again */


	while(1)
	{
		userInteractions();		/*The function used to perform all the operations of the HMI*/

	}
}
