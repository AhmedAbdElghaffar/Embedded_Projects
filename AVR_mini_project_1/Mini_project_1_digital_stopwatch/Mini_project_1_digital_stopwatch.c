/*
 * Mini_project_1_digital_stopwatch.c
 *
 *  Created on: Dec 10, 2019
 *      Author: ahmed
 */
#include <avr/io.h>   		//Include definition of all IO peripherals registers
#include <avr/delay.h> 		//delay
#include <avr/interrupt.h>	//Interrupt

#define set_bit(reg,n) ( reg=reg | (1<<n) )			//Set specific pin to 1
#define clear_bit(reg,n) ( reg=reg & (~(1<<n)) )	//Set specific pin to 0
#define toggle_bit(reg,n) ( reg=reg ^ (1<<n) )		//Change any pin condition (1 to 0 ) or (0 to 1)

typedef unsigned int 	u_int32; 		//Change to unsigned long in case the compiler has (int) of size 2
typedef unsigned char	u_char8;


u_int32 g_counter=0;		//Counter used to get each 7 segment number
u_char8 g_tick =0;			//The timer counter
u_char8 hh=0, mm=0, ss=0;	//Hours , Minutes , Seconds

void ALL_INTERRUPTS_INIT(void){

	/* Configuration of MCUCR (INT0 and INT1):
	 * 1- INT0 with falling edge >> Set ISC01 to 1 , ISC00 to 0 (default)
	 * 2- INT1 with rising edge  >> Set ISC11 to 1 , ISC00 to 1
	 */
	MCUCR |= (1<<ISC01) | (1<<ISC11) | (1<<ISC10);

	/*Configuration of MCUCSR (INT2):
	 * Set ISC2 to 0 (Falling edge)
	 */
	MCUCSR &= ~(1<<ISC2);
	GICR |= (1<<INT0) | (1<<INT1) | (1<<INT2);	//Model Interrupt enable ( Enable all the 3 Interrupts)

	clear_bit(DDRB,PB2);	//clear PB1 , Make it input pin (INT2)
	clear_bit(DDRD,PD2);	//clear PD2 , Make it input pin	(INT0)
	clear_bit(DDRD,PD3);	//clear PD3 , Make it input pin	(INT1)
	set_bit(PORTB,PB2);		//Enable internal pull up
	set_bit(PORTD,PD2);		//Enable internal pull up
}

void Timer1_CMP_INIT(void){

	TCNT1 = 0x00; 			//Starting counting from 0
	OCR1A = 976;			//Compare value

	/*Configure TCCR1A/B as follows:
	 * 1- WGM12 is set to 1 , WGM10, WGM11, WGM13 is set to 0 (default) to enable CTC
	 * 2- CS11 set to 0 , CS10 and CS12 to 1 (Pre-scaler = 1024 )
	 */
	TCCR1B |= (1<<WGM12) | (1<<CS10) | (1<<CS12);
	TIMSK |= (1<<OCIE1A);	//Enable interrupt at compare match

}

ISR(TIMER1_COMPA_vect){

	SREG |= (1<<7);	//Enable Global Interrupts to enable interrupt nesting

	g_tick++;
	if(g_tick==1)
	{
		g_tick=0;
		g_counter++;
	}


	hh=g_counter/3600;			//Extract the hours from the global counter g_counter
	mm=(g_counter%3600)/60;		//Extract the minutes from the global counter g_counter
	ss=g_counter%60;			//Extract the seconds from the global counter g_counter

	/*Or
	 * mm=(g_counter-hh*3600)/60;
	 * ss=g_counter-hh*3600-mm*60;
	 */
}

// ISR of INT0 supposed to reset the stop-watch
ISR(INT0_vect){
	//Doesn't need enabling the I bit as it's the highest priority and no ISR can interrupt it
	g_tick=0;
	g_counter=0;
	ss=0;
	TCNT1 = 0; 							//restart the counter from 0
	TCCR1B |= (1<<CS10) | (1<<CS12);	//To ensure that you start timer again after pausing it in case of  the pause ISR is executed
}

// ISR of INT1 supposed to pause the stop-watch
ISR(INT1_vect){

	SREG |= (1<<7);	//Enable Global Interrupts to enable interrupt nesting

	/*We need to pause the timer so we
	 * need to stop the clock source (Timer/Counter)
	 * so will set CS00 , CS01 , CS02 to 0;
	 */
	TCCR1B &= ~(1<<CS10) & ~(1<<CS11) & ~(1<<CS12);		//No clock source (Timer/Counter stopped).

}

// ISR of INT2 supposed to resume the stop-watch
ISR(INT2_vect){

	SREG |= (1<<7);	//Enable Global Interrupts to enable interrupt nesting

	/*We need to resume the timer so we
	 * need to resume the clock source (Timer/Counter) with the starting prescalar
	 * so will set CS00 , CS02 to 1;
	 */

	TCCR1B |= (1<<CS10) | (1<<CS12);

}

int main(void){


	DDRC |=0x0f;	//Set first 4 pins in PORTC to be output
	DDRA |= 0x3f;	//Set first 6 pins in PORTA to be output
	PORTC &=0xf0;	//Initialize first 4 pins in portC to be 0
	PORTA &=0xc0;	//Initialize first 6 pins in portA to be 0

	SREG |= (1<<7);	//Enable Global Interrupts

	Timer1_CMP_INIT();
	ALL_INTERRUPTS_INIT();

	while(1)
	{
		_delay_ms(2);
		set_bit(PORTA,PA0); 		//Enable first 7 segment
		PORTC=(PORTC & 0xf0) | ((ss%10) & 0x0f);
		_delay_ms(2);
		clear_bit(PORTA,PA0);		//Disable it


		set_bit(PORTA,PA1);			//Enable second 7 segment
		PORTC=(PORTC & 0xf0) | ((ss/10) & 0x0f);
		_delay_ms(2);
		clear_bit(PORTA,PA1);		//Disable it

		set_bit(PORTA,PA2); 		//Enable third 7 segment
		PORTC=(PORTC & 0xf0) | ((mm%10) & 0x0f);
		_delay_ms(2);
		clear_bit(PORTA,PA2);		//Disable it

		set_bit(PORTA,PA3); 		//Enable forth 7 segment
		PORTC=(PORTC & 0xf0) | ((mm/10) & 0x0f);
		_delay_ms(2);
		clear_bit(PORTA,PA3);		//Disable it

		set_bit(PORTA,PA4); 		//Enable fifth 7 segment
		PORTC=(PORTC & 0xf0) | ((hh%10) & 0x0f);
		_delay_ms(2);
		clear_bit(PORTA,PA4);		//Disable it

		set_bit(PORTA,PA5); 		//Enable sixth 7 segment
		PORTC=(PORTC & 0xf0) | ((hh/10) & 0x0f);
		_delay_ms(2);
		clear_bit(PORTA,PA5);		//Disable it

		if(g_counter==360000) 		//Time is 99:59:59
		{
			g_tick=0;
			g_counter=0;

		}

	}

}
