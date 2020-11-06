/*
 * HMI_Application.h
 *
 *  Created on: Feb 9, 2020
 *      Author: ahmed
 */

#ifndef HMI_APPLICATION_H_
#define HMI_APPLICATION_H_

#include "Common_Macros.h"
#include "Micro_Config.h"
#include "Std_types.h"
/*******************************************************************
 * 								Libraries
 *******************************************************************/
#include "Keypad.h"
#include "LCD.h"
#include "UART.h"
#include "Timer1.h"


/*******************************************************************
 * 						   Preprocessor Constants
 *******************************************************************/

#define PASSWORD_SIZE				5
#define WRONG_PASSWORD_COUNTER		3


/*******************************************************************
 * 						   Synchronization Constants
 *******************************************************************/

#define M2_READY					0xA0		/*Check if the other micro is ready and initialized*/
#define SEND_PASSWORD				0xA1		/*Tells the other Control that the password is being sent*/
#define PASSWORD_COMPARE_DONE		0xA2		/*Tells the HMI that password compare is done*/
#define CHANGE_PASSWORD				0xA3		/*Tells the Control that the password needs to be changed*/
#define HMI_SEND_OPTIONS			0xA4		/*Tells control that HMI is sending user option*/
#define SEND_OLD_PASSWORD			0xA5		/*Tells the Control that the HMI is sending the old password*/
#define PASSWORD_SAVED				0x00		/*Control saved password and tells the HMI*/
#define PASSWORD_NOT_SAVED			0x01		/*Control didn't save password and tells the HMI*/
#define OPEN_DOOR					0xA6		/*Control tells the HMI that the door is opening*/
#define CONTROL_SEND_OPTIONS		0xA7		/*Synchronization order sent by control to make HMI ready for receiving orders*/
#define ALARM						0xA8		/*Control tells HMI that buzzer will fire*/
#define WRONG_PASSWORD_FOR_OPENNING 0xA9		/*Control tells the HMI that the password is wrong*/
#define PASSWORD_CHECKED_TRUE		0xAA		/*Control tells the HMI that password is accurate*/
#define PASSWORD_CHECKED_FALSE		0xAB		/*Control tells the HMI that password is not accurate*/
#define EDIT_PASSWORD				0XAC		/*Control tells the HMI that new password is needed*/
#define PASSWORD_KEPT				0xAD		/*Control tells the HMI password will be the same*/
#define SYNCH						0xff		/*General Synchronization constant*/





/*******************************************************************
 * 							Function Prototypes
 *******************************************************************/

void sendNewPassword(void);

void userInteractions(void);

void chooseOptions(uint8 a_option);

void getPassword(uint8 *Arr , uint8 a_passwordSize);

void sendPassword(uint8 *Arr,uint8 size);

void firstTimeOpeningNewSystem(void);

void Timer1_Routine(void);

void myDelay(uint8 a_delay);

#endif /* HMI_APPLICATION_H_ */
