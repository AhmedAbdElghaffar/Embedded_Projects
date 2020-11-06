/*************************************************************************
 * Module: Control_Application
 *
 * File Name: Control_Application.c
 *
 * Description: Main Control ECU systems and operation
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time:  07 / 02 / 2020, 4:35 PM
 *
 *************************************************************************/


#include "Control_Application.h"

/*Global counter that is used to count time in the application*/
uint8 oneMinuteCounter=0;

/*
 * Function Name: Timer1_Routine
 *
 * Description: Function that will be called after the call back notification
 *
 * Arguments:
 *
 * 		Inputs:
 * 			No inputs
 *
 * 	returns:
 * 		no returns(void)
 */
void Timer1_Routine(void){

	oneMinuteCounter++;		/*Need 28 interrupts to complete a minute*/
}



/*
 * Function Name: receiveNewPassword
 *
 * Description: Function used to receive the new password of the system
 *
 * Arguments:
 *
 * 		Inputs:
 * 			No inputs
 *
 * 	returns:
 * 		no returns(void)
 */
void receiveNewPassword(void)
{
	uint8 First_Password[PASSWORD_SIZE] , Second_Password[PASSWORD_SIZE] , Saved_Password[PASSWORD_SIZE] ; /*Arrays to carry different passwords*/
	uint8 Password_Check_Flag;	/*Flag used to check password match*/
	while(1)
	{
		UART_receivePassword(First_Password , PASSWORD_SIZE);  /*receiving the first password*/
		_delay_ms(5);
		UART_receivePassword(Second_Password , PASSWORD_SIZE); /*receiving the second password*/

		Password_Check_Flag = checkPassword(First_Password ,Second_Password , PASSWORD_SIZE);

		if(Password_Check_Flag)
		{
			EEPROM_savePassword(First_Password , PASSWORD_SIZE);   /*saving the new password in the EEPROM*/
			_delay_ms(10);
			EEPROM_readPassword(Saved_Password , PASSWORD_SIZE);   /*reading the password from the EEPROM*/
			UART_sendByte(PASSWORD_SAVED);
			return;
		}
		else
		{
			UART_sendByte(PASSWORD_NOT_SAVED);
		}
	}

}


/*
 * Function Name: controlEcuOptions
 *
 * Description: Function used to perform all the operations of the Control ECU
 *
 * Arguments:
 *
 * 		Inputs:
 * 			No inputs
 *
 * 	returns:
 * 		no returns(void)
 */
void controlEcuOptions(void)
{
	uint8 Compare_Password[PASSWORD_SIZE] , Saved_Password[PASSWORD_SIZE];
	uint8 Options , Password_Check_flag , passwordErrorCounter , Flag=1 ;

	EEPROM_readPassword(Saved_Password,PASSWORD_SIZE);

	while(UART_receiveByte() != HMI_SEND_OPTIONS);   /*Polling tell HMI send options*/

	Options=UART_receiveByte();
	if(Options == CHANGE_PASSWORD)   	/* "#" is pressed in the HMI(change password) */
	{
		UART_receivePassword(Compare_Password,PASSWORD_SIZE);
		Password_Check_flag = checkPassword(Compare_Password ,Saved_Password , PASSWORD_SIZE);
		if(Password_Check_flag) 		/*Password matched*/
		{
			UART_sendByte(CONTROL_SEND_OPTIONS);
			_delay_ms(5);
			UART_sendByte(EDIT_PASSWORD);
			receiveNewPassword();		/*Call the function of receiving the new password*/
		}
		else
		{
			UART_sendByte(CONTROL_SEND_OPTIONS);
			_delay_ms(5);
			UART_sendByte(PASSWORD_KEPT);
		}
	}
	else if (Options == SEND_OLD_PASSWORD)		/* "*" is pressed in the HMI(Open door) */
	{
		UART_receivePassword(Compare_Password,PASSWORD_SIZE);
		Password_Check_flag = checkPassword(Compare_Password ,Saved_Password , PASSWORD_SIZE);

		if(Password_Check_flag)
		{
			/*Opening Door*/
			UART_sendByte(CONTROL_SEND_OPTIONS);
			_delay_ms(10);
			UART_sendByte(OPEN_DOOR);

			MOTOR_CW();
			myDelay(7);
			MOTOR_ACW();
			myDelay(7);
			MOTOR_STOP();

		}
		else
		{
			/*Password is wrong and there are 2 trials only left*/
			UART_sendByte(CONTROL_SEND_OPTIONS);
			_delay_ms(5);
			UART_sendByte(WRONG_PASSWORD_FOR_OPENNING);

			/*For loop used to check the password 2 times and if it's wrong the buzzer will fire*/
			for(passwordErrorCounter=0 ; passwordErrorCounter< WRONG_PASSWORD_COUNTER-1 ; passwordErrorCounter++)
			{
				UART_sendByte(SYNCH);
				if(Flag)   /*general Flag used to check if the password is right in the second or third trials*/
				{
					while(UART_receiveByte() != HMI_SEND_OPTIONS);		/*Polling tell HMI send options*/
					UART_receivePassword(Compare_Password,PASSWORD_SIZE);
					Password_Check_flag = checkPassword(Compare_Password ,Saved_Password , PASSWORD_SIZE);
					if(Password_Check_flag)
					{
						/*Opening Door*/
						UART_sendByte(CONTROL_SEND_OPTIONS);
						_delay_ms(5);
						UART_sendByte(PASSWORD_CHECKED_TRUE);
						MOTOR_CW();				/*rotate motor clock wise*/
						myDelay(7);				/*15 seconds delay (every 1 count = 2.09 seconds)*/
						MOTOR_ACW();			/*rotate motor anti clock wise*/
						myDelay(7);				/*15 seconds delay (every 1 count = 2.09 seconds)*/
						MOTOR_STOP();			/* Stop motor*/
						Flag=0;
					}
					else
					{	/*Pass is wrong*/
						UART_sendByte(CONTROL_SEND_OPTIONS);
						_delay_ms(5);
						UART_sendByte(PASSWORD_CHECKED_FALSE);

						if(passwordErrorCounter==(WRONG_PASSWORD_COUNTER-2))
						{
							Buzzer(28);			/*Fire the buzzer for 1 minute(2.09 seconds = 1 in the input of Buzzer function)*/
						}
					}
				}
			}
		}

	}
}

/*
 * Function Name: UART_receivePassword
 *
 * Description: Function used receive a password from the HMI
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1- uint8 *Arr: array to receive the password
 *			2- uint8 size: size of the array
 * 	returns:
 * 		no returns(void)
 */
void UART_receivePassword(uint8 *Arr,uint8 size)
{
	uint8 i=0;
	while(UART_receiveByte() != SEND_PASSWORD ); /*Polling tell the HMI sends the password*/
	for(i=0;i<size;i++)
	{
		Arr[i]=UART_receiveByte();
	}
}


/*
 * Function Name: UART_receivePassword
 *
 * Description: Function used to compare the 2 input passwords
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1- uint8 *Arr1: Fist array to be checked
 * 			2- uint8 *Arr2: second array to be checked
 *			3- uint8 size: size of the array
 * 	returns:
 * 		uint8, return 1 if the passwords are matched
 */
uint8 checkPassword(uint8 *Arr1 , uint8 *Arr2 ,uint8 size)
{
	uint8 i=0;
	for(i=0;i<size;i++)
	{
		if(Arr1[i] != Arr2[i])
		{
			return 0;
		}
	}
	return 1;
}

/*
 * Function Name: EEPROM_savePassword
 *
 * Description: Function used save password in the EEPROM
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1- uint8 *Arr: array carrying the password
 *			2- uint8 size: size of the array
 * 	returns:
 * 		no returns(void)
 */
void EEPROM_savePassword(uint8 *Arr , uint8 size)
{
	uint8 i=0;
	for(i=0;i<size;i++)
	{
		EEPROM_write((0x0311 + i),Arr[i]);
		_delay_ms(10);
	}
}

/*
 * Function Name: EEPROM_readPassword
 *
 * Description: Function used read password from the EEPROM
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1- uint8 *Arr: array to carry the password
 *			2- uint8 size: size of the array
 * 	returns:
 * 		no returns(void)
 */
void EEPROM_readPassword(uint8 *Arr , uint8 size)
{
	uint8 i=0;
	for(i=0;i<size;i++)
	{
		EEPROM_read((0x0311 + i),&Arr[i]);
		_delay_ms(10);
	}
}


/*
 * Function Name: firstTimeOpeningNewSystem
 *
 * Description: Function used to interact with the user only at the first time after buying a the new system(Get the first time password)
 *
 * Arguments:
 *
 * 		Inputs:
 *
 * 	returns:
 * 		no returns(void)
 */
void firstTimeOpeningNewSystem(void)
{
	uint8 EEPROM_First_Address_Value , EEPROM_Second_Address_Value ,Indicator ;

	EEPROM_read(0x0000 , &EEPROM_First_Address_Value);
	_delay_ms(5);
	EEPROM_read(0x0001 , &EEPROM_Second_Address_Value);
	UART_sendByte(SYNCH);
	_delay_ms(5);
	UART_sendByte(EEPROM_First_Address_Value);
	_delay_ms(5);
	UART_sendByte(EEPROM_Second_Address_Value);
	if(EEPROM_First_Address_Value==0 && (EEPROM_Second_Address_Value))
	{
		Indicator=0;
	}
	else
	{
		Indicator=1;
		EEPROM_write(0x0000,0x00);
		_delay_ms(10);
		EEPROM_write(0x0001 + (uint16)1,0x01);
	}
	if(Indicator)
	{
		receiveNewPassword();
	}
}

/*
 * Function Name: myDelay
 *
 * Description: Function used make delays
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-uint8 a_delay: required delay time  (every 1 in input = 2.09 seconds)
 *
 * 	returns:
 * 		no returns(void)
 */
void myDelay(uint8 a_delay)
{
	TIMER1_resume();
	oneMinuteCounter=0;
	while(oneMinuteCounter < a_delay);
	oneMinuteCounter=0;
	TIMER1_stop();
}

/*
 * Function Name: Buzzer
 *
 * Description: Function used make delaysfire buzzer
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-uint8 a_delay: required buzzer time
 *
 * 	returns:
 * 		no returns(void)
 */
void Buzzer(uint8 a_delay)
{

	SET_BIT(BUZZER_CONTROL_DIRECTION,BUZZER_PIN);
	TIMER1_resume();
	oneMinuteCounter=0;
	while(oneMinuteCounter < a_delay )
	{
		TOGGLE_BIT(BUZZER_CONTROL_PORT,BUZZER_PIN);
		_delay_ms(500);
	}
	CLEAR_BIT(BUZZER_CONTROL_PORT,BUZZER_PIN);
	oneMinuteCounter=0;
	TIMER1_stop();
}

