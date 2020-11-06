/*************************************************************************
 * Module: Timer1
 *
 * File Name: Timer1.c
 *
 * Description: Timer1 main functionalities
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time:  14 / 02 / 2020, 7:20 PM
 *
 *************************************************************************/

#include "Timer1.h"

/*A pointer to function that will carry the function address that will be called after the call back notification*/
static void(*volatile g_Timer1_CallBack)(void)=NULL;

/*Timer1 interrupt service routine*/
ISR(TIMER1_OVF_vect)
{
	if(g_Timer1_CallBack !=NULL){
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer1_CallBack)();
	}
}

/*
 * Function Name: TIMER1_init
 *
 * Description: This function is responsible for initializing the Timer1 module According to the chose mode
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-void(*const CallBack_ptr_Timer1)(void):
 * 					A pointer to function used to carry the address of the called back function.
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the Timer1 is initialized
 */
void TIMER1_init(void(*const CallBack_ptr_Timer1)(void))
{
	/*Configure TCCR1A/B as follows:
	 * 1- WGM13 , WGM12 , WGM11 , WGM10  are cleared to enable the Normal mode
	 * 2- FOC1A/B are set to specify non-PWM mode
	 * 3- CS12 is set , CS11 and CS10 are cleared (Pre-scaler = 256 )
	 */
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	TCCR1B = (1<<CS12);
	TIMSK |= (1<<TOIE1);	/*Enable interrupt at overflow*/
	TCNT1 = 0x00; 			/*Starting counting from 0*/
	g_Timer1_CallBack=CallBack_ptr_Timer1;    /*Load the pointer to function with the required call back function*/
}

/*
 * Function Name: TIMER1_stop
 *
 * Description: Function used to pause the Timer
 *
 * Arguments:
 *
 * 		Inputs:
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the Timer1 is paused
 */
void TIMER1_stop(void)
{
	TCCR1B = 0x00;			/*No clock source*/
	TCNT1  = 0x00;			/*Set counter to zero */
}

/*
 * Function Name: TIMER1_resume
 *
 * Description: Function used to resume the Timer
 *
 * Arguments:
 *
 * 		Inputs:
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the Timer1 is resumed
 */
void TIMER1_resume(void)
{
	TCCR1B = (1<<CS12);			/*256 Pre-scaler*/
	TCNT1  = 0x00;				/*Set counter to zero */
}

/*
 * Function Name: TIMER1_resume
 *
 * Description: Function used to de-initiate the timer
 *
 * Arguments:
 *
 * 		Inputs:
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but Timer1 no longer exist
 */
void TIMER1_deInit(void)
{
	/*Reset all the registers and make all values = 0 */
	TCCR1A = 0x00;
	TCCR1B = 0x00;
	TIMSK  = 0x00;
	TCNT1  = 0x00;
}

