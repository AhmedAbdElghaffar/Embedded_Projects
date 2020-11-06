/*******************************************************************
 * File name: Main_Dc_speed_controller.c
 *
 * Description: The main that contains the application ( Controlling DC motor speed using Potentiometer )
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time: 7 / 1 / 2020,  2:30 PM
 *
 *********************************************************************/
#include "LCD.h"
#include "ADC.h"
#include "External_Interrupts.h"
#include "Timer0.h"

void Interrupt0_Routine(void){
	/*
	 * Write your application here
	 */
	TOGGLE_BIT(PORTB,PB0);
	TOGGLE_BIT(PORTB,PB1);

}

int main(void){

	INT0_configType INT0_Config={Rising};  /*Interrupt zero settings*/

	ADC_Configurations ADC_Config={AREF,F_CPU_8,Polling}; /*ADC settings*/

	LCD_init();					/*Initialize the LCD*/
	LCD_clearScreen();			/*Clears the LCD*/
	LCD_displayString("ADC value = ");

	ADC_init(&ADC_Config);		/*Initialize the ADC*/
	DDRB |= (1<<PB0) | (1<<PB1);/*PB0 and PB1 are output pins*/
	PORTB =(PORTB & 0xfc) | (1);/*PB0 initial output =1 and PB1 =0 */
	sei();						/*Enable Global interrupts*/
	INT0_init(&INT0_Config,&Interrupt0_Routine);/*Initialize INT0*/
	while(1)
	{
		LCD_displayString("    ");
		LCD_goToRowColumn(0,12);
		ADC_readChannel(0);
		Timer0_GeneratePWM(g_ADC_reading/4);
		LCD_integerToString(g_ADC_reading);


	}
}

