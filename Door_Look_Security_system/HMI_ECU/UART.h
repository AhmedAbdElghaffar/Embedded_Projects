/*************************************************************************
 * Module: UART
 *
 * File Name: UART.h
 *
 * Description: UART Configuratins
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time:  25 / 01 / 2020, 3:50 PM
 *
 *************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "Common_Macros.h"
#include "Std_types.h"
#include "Micro_Config.h"

/**************************************************************
 * 						Type Declaration
 *************************************************************/

typedef enum
{
	Normal , Double  /*Normal speed or double speed(related to Baud)*/
}UART_speed;

typedef enum
{
	Five , Six , Seven , Eight   /*Sent and received character size*/
}UART_dataSize;

typedef enum
{
	Disabled , Even= 2 , Odd	/*Parity Check*/
}UART_parity;

typedef enum
{
	One ,  Two		/*Number of stop bits*/
}UART_stopBit;

typedef struct		/* Structure used to configure the UART module */
{
	UART_speed Speed;
	UART_dataSize Size;
	UART_parity Parity;
	UART_stopBit Stop;
	uint32 Baud;

}UART_Configurations;

/**************************************************************
 * 						Functions Prototype
 *************************************************************/

/*Function Description: used to initialize the UART module*/
void UART_init(UART_Configurations*);

/*Function Description: used to send one Byte*/
void UART_sendByte(uint8);

/*Function Description: used to receive one Byte*/
uint8 UART_receiveByte(void);

/*Function Description: used to send a string*/
void UART_sendString(uint8*);

/*Function Description: used to receive a string*/
void UART_receiveString(uint8*);

#endif /* UART_H_  */
