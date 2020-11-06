/*************************************************************************
 * Module: Timer1_overflow
 *
 * File Name: Timer1.h
 *
 * Description: UART Configuratins
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time:  14 / 02 / 2020, 7:45 PM
 *
 *************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_

#include "Common_Macros.h"
#include "Micro_Config.h"
#include "Std_types.h"


/**************************************************************
 * 						Functions Prototype
 *************************************************************/

/*Description: Function used to initiate the Timer */
void TIMER1_init(void(*const CallBack_ptr_Timer1)(void));

/*Description: Function used to stop the clock source and pause the timer */
void TIMER1_stop(void);

/*Description: Function used to set the clock source and resume the timer */
void TIMER1_resume(void);

/*Description: Function used to de-initiate the timer */
void TIMER1_deInit(void);


#endif /* TIMER1_H_ */
