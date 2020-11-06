/*************************************************************************
 * Module: UART
 *
 * File Name: UART.C
 *
 * Description: UART Main Functions
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time:  25 / 01 / 2020, 3:50 PM
 *
 *************************************************************************/



#include "UART.h"

/*
 * Function Name: UART_init
 *
 * Description: This function is responsible for initializing the UART According to the chose mode
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-UART_Configurations *UART_Config:
 * 					A structure containing the main configurations to initialize the UART
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the UART is initialized
 */
void UART_init(UART_Configurations *UART_Config){

	/******************************** UCSRA OPTIONS *****************************************
	 * 1-Select the  USART Transmission Speed(Normal or Double)
	 *************************************************************************************/
	UCSRA = (UCSRA & 0xfd) | ((UART_Config ->Speed)<<U2X);

	/******************************** UCSRB OPTIONS *****************************************
	 * 1- Enable/disaple Interrupt at receive complete(Set RXCIE)
	 * 2- Receiver Enable(Set RXEN)
	 * 3- Transmitter Enable(Set TXEN)
	 * 4- Defining Character size(UCSZ2 takes the 3rd bit from character size)
	 *************************************************************************************/

	UCSRB = (1<<RXEN) | (1<<TXEN) |
			(((UART_Config ->Size) & 0x04));


	/******************************** UCSRC OPTIONS *****************************************
	 * 1- Set URSEL to enable editing the UCSRC register
	 * 2- Selecting Parity Options (UPM0 and UPM1)
	 * 3- Selecting number of stop bits (0 for 1 bit, 1 for 2 bits)
	 * 4- Defining Character size(UCSZ1:0 take the 2rd, 1st bits from character size)
	 *************************************************************************************/

	UCSRC  = (1<<URSEL);
	UCSRC |= ((UART_Config->Parity)<<UPM0) | /*Parity is 2 bits so it's shifted only to UPM0 and UPM1 is filled by second bit*/
			((UART_Config->Stop)<<USBS) | (((UART_Config ->Size) & 0x03)<<UCSZ0);

	/******************************** UBBR OPTIONS *****************************************
	 * 1- Clear URSEL to enable editing the UBBR register
	 * 2- Writing the equation for calculating UBBRL,UBBRH values
	 *************************************************************************************/

	CLEAR_BIT(UCSRC,URSEL);
	/*
	 * the equation is Fcpu*(1+U2X value)/(16*Baude)-1
	 * if U2x is 0(Normal speed ) the deviser will be 16
	 * if U2x is 1(Double speed ) the deviser will be 8
	 */
	UBRRH=((F_CPU*((UART_Config->Speed)+1))/(16*UART_Config->Baud)-1)>>8;
	UBRRL=((F_CPU*((UART_Config->Speed)+1))/(16*UART_Config->Baud)-1);

}

/*
 * Function Name: UART_sendByte
 *
 * Description: This function is responsible for sending a specific character size
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-uint8 a_data:
 * 					the required data to be sent
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the data is sent
 */
void UART_sendByte(uint8 a_data){

	while(BIT_IS_CLEARED(UCSRA,UDRE))
	{
		/*
		 * Polling
		 * Waiting till the UDR register is empty to send the data
		 */
	}
	UDR=a_data;  /*Loading the UDR with required data*/
}

/*
 * Function Name: UART_receiveByte
 *
 * Description: This function is responsible for receiving a specific character size
 *
 * Arguments:
 *
 * 		Inputs:
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the data is received
 */
uint8 UART_receiveByte(void){

	while(BIT_IS_CLEARED(UCSRA,RXC))
	{
		/*
		 * Polling
		 * Waiting till the RXC is set to be sure that receive is complete
		 */
	}

	return UDR;   /*Read the value of UDR*/
}

/*
 * Function Name: UART_sendString
 *
 * Description: This function is responsible for specific string
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1- uint8 *a_str
 * 					the required string to be sent
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the string is sent
 */
void UART_sendString(uint8 *a_str){

	while(*a_str != '\0')
	{
		UART_sendByte(*a_str);
		a_str++;				/*Pointer moves to next character*/
	}
}


/*
 * Function Name: UART_receiveString
 *
 * Description: This function is responsible for receiving a specific string
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1- uint8 *a_str
 * 					Array that will be loaded with the received string
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the string is received
 */
void UART_receiveString(uint8 *a_str){

	do{
		*a_str=UART_receiveByte();
		a_str++;				/*Pointer moves to next character*/
	}while(*(a_str-1) != '#');	/*Checks for a virtual Null as the real Null can't be send or received*/
	*(a_str-1)='\0';			/*End your array with Null to be a string*/
}






