/*******************************************************************
 * File name:Timer0.c
 *
 * Description: Main Functions of Timer0
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time: 7 / 1 / 2020,  1:00 PM
 *
 *********************************************************************/
#include "Timer0.h"

void Timer0_GeneratePWM(uint8 a_duty_cycle){

	/*Configure TCCR0 as follows:
	 * 1- WGM01 and WGM00 are set to 1 to enable fast PWM mode
	 * 2- CS01 is set to 1 to choose prescaler=8, FCPU/8
	 * 3- COM01 is set to clear OC0 on compare match
	 */
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS01);
	TCNT0=0;			/* Start counting from 0 */
	OCR0=a_duty_cycle;	/*Choose the compare value to set the PWM duty cycle*/
	SET_BIT(DDRB,PB3);	/*Setting PB3(OC0) pin to be output*/
}
