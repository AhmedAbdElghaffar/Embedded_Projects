/*
 * HMI_Application.c
 *
 *  Created on: Feb 9, 2020
 *      Author: ahmed
 */

#include "HMI_Application.h"

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

	oneMinuteCounter++;		/*Need 28 interrupts TO COUNT ONE MINUTE , 2 SEC / INTERRUPT*/
}


void sendNewPassword(void)
{
	uint8 First_Password[PASSWORD_SIZE] , Second_Password[PASSWORD_SIZE];
	uint8 Password_Check_flag=1;

	while(Password_Check_flag)
	{
		LCD_clearScreen();
		LCD_displayString("Please Enter New Password");
		LCD_goToRowColumn(1,0);
		getPassword(First_Password , PASSWORD_SIZE);
		sendPassword(First_Password , PASSWORD_SIZE);

		LCD_clearScreen();
		LCD_displayString("Please Re-enter New Password");
		LCD_goToRowColumn(1,0);
		getPassword(Second_Password , PASSWORD_SIZE);
		sendPassword(Second_Password , PASSWORD_SIZE);

		Password_Check_flag=UART_receiveByte();
		if(Password_Check_flag)
		{
			LCD_clearScreen();
			LCD_displayString("Password not matched, try again");
			_delay_ms(1000);
		}
		else
		{
			LCD_clearScreen();
			LCD_displayString("PASSWORD SAVED");
			_delay_ms(1000);
		}
	}
}

void userInteractions(void)
{
	uint8 Old_Password[PASSWORD_SIZE];
	uint8 userChoice , Control_ECU_Choice , passwordErrorCounter , Flag=1;
	LCD_clearScreen();
	LCD_displayString("System Options");
	_delay_ms(1000);
	LCD_clearScreen();
	LCD_displayString(" * : Open The Door");
	LCD_goToRowColumn(1,0);
	LCD_displayString(" # : Change Password");

	userChoice=KEYBAD_GetPressedKey();
	stop();

	if(userChoice=='*')
	{
		UART_sendByte(HMI_SEND_OPTIONS);
		UART_sendByte(SEND_OLD_PASSWORD);
		LCD_clearScreen();
		LCD_displayString("Enter The Password");
		LCD_goToRowColumn(1,0);
		getPassword(Old_Password , PASSWORD_SIZE);
		sendPassword(Old_Password , PASSWORD_SIZE);

		while(UART_receiveByte() != CONTROL_SEND_OPTIONS);

		Control_ECU_Choice=UART_receiveByte();
		if(Control_ECU_Choice == OPEN_DOOR)
		{
			LCD_clearScreen();
			LCD_displayString("Door Is Opening");
			myDelay(7);
			LCD_clearScreen();
			LCD_displayString("Door Is Closing");
			myDelay(7);
		}
		else if(Control_ECU_Choice == WRONG_PASSWORD_FOR_OPENNING)
		{
			LCD_clearScreen();
			LCD_displayString("Wrong Password");
			_delay_ms(1000);
			for(passwordErrorCounter=0 ; passwordErrorCounter<WRONG_PASSWORD_COUNTER-1 ; passwordErrorCounter++)
			{
				while(UART_receiveByte() != SYNCH);
				if(Flag)
				{
					LCD_clearScreen();
					LCD_displayString("Please Re-Enter Password");
					LCD_goToRowColumn(1,0);
					getPassword(Old_Password , PASSWORD_SIZE);
					UART_sendByte(HMI_SEND_OPTIONS);
					sendPassword(Old_Password , PASSWORD_SIZE);
					while(UART_receiveByte() != CONTROL_SEND_OPTIONS);
					Control_ECU_Choice=UART_receiveByte();

					if(Control_ECU_Choice== PASSWORD_CHECKED_TRUE)
					{
						LCD_clearScreen();
						LCD_displayString("Door Is Opening");
						myDelay(7);
						LCD_clearScreen();
						LCD_displayString("Door Is Closing");
						myDelay(7);
						Flag=0;
					}

					else if(Control_ECU_Choice== PASSWORD_CHECKED_FALSE)
					{
						LCD_clearScreen();
						LCD_displayString("Wrong Password");
						_delay_ms(500);
						if(passwordErrorCounter==(WRONG_PASSWORD_COUNTER-2))
						{
							LCD_clearScreen();
							LCD_displayString("		RUUUUN		");
							myDelay(1);
							LCD_clearScreen();
							LCD_displayString("ALAAAAAARM");
							myDelay(27);
						}
					}
				}
			}
		}
	}
	else if(userChoice=='#')
	{
		LCD_clearScreen();
		LCD_displayString("Enter The Old Password");
		LCD_goToRowColumn(1,0);
		UART_sendByte(HMI_SEND_OPTIONS);
		_delay_ms(5);
		UART_sendByte(CHANGE_PASSWORD);
		getPassword(Old_Password , PASSWORD_SIZE);
		sendPassword(Old_Password , PASSWORD_SIZE);
		while(UART_receiveByte() != CONTROL_SEND_OPTIONS);
		Control_ECU_Choice=UART_receiveByte();
		if(Control_ECU_Choice == EDIT_PASSWORD)
		{
			sendNewPassword();
		}
		else if(Control_ECU_Choice == PASSWORD_KEPT)
		{
			LCD_clearScreen();
			LCD_displayString("Wrong Password");
			_delay_ms(1000);
		}

	}
}


/*
 * Function Name: getPassword
 *
 * Description: Function used get password from the user
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1- uint8 *Arr: array to carry the password
 *			2- uint8 a_passwordSize: size of the array
 * 	returns:
 * 		no returns(void)
 */
void getPassword(uint8 *Arr , uint8 a_passwordSize)
{
	uint8 i=0;
	for(i=0;i<a_passwordSize;i++)
	{
		Arr[i]=KEYBAD_GetPressedKey();
		LCD_displayCharacter('*');  /*Shows the input as "*" */
		stop();						/*Don't get input till user release the key*/
	}
}


/*
 * Function Name: sendPassword
 *
 * Description: Function used to send the entered password by the user
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1- uint8 *Arr: array to carry the password
 *			2- uint8 a_size: size of the array
 *
 * 	returns:
 * 		no returns(void)
 */
void sendPassword(uint8 *Arr,uint8 size)
{
	uint8 i=0;
	UART_sendByte(SEND_PASSWORD);
	for(i=0;i<size;i++)
	{
		UART_sendByte(Arr[i]);
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
	uint8 EEPROM_First_Address_Value , EEPROM_Second_Address_Value ,  Indicator ;
	while(UART_receiveByte() != SYNCH);
	EEPROM_First_Address_Value = UART_receiveByte();
	_delay_ms(5);
	EEPROM_Second_Address_Value = UART_receiveByte();
	if(EEPROM_First_Address_Value==0 && (EEPROM_Second_Address_Value))
	{
		Indicator=0;
	}
	else
	{
		Indicator=1;
	}
	if(Indicator)
	{
		sendNewPassword();
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
 * 			1-uint8 a_delay: required delay time (every 1 in input = 2.09 seconds)
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
