/*
 * Motor.h
 *
 *  Created on: Feb 14, 2020
 *      Author: ahmed
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "Common_Macros.h"
#include "Micro_Config.h"
#include "Std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

#define MOTOR_CONTROL_PORT 			PORTB
#define MOTOR_DIRECTION_PORT 		DDRB

#define FIRST_OUTPUT_PIN			PB0
#define SECOND_OUTPUT_PIN			PB1

/*************************************************************************
 * 							Functions Prototype
 *************************************************************************/

/*Description: Function used to initialize the motor pins*/
void MOTOR_init(void);

/*Description: Function used to rotate the motor clock wise*/
void MOTOR_CW(void);

/*Description: Function used to rotate the motor anti clock wise*/
void MOTOR_ACW(void);

/*Description: Function used to stop the motor*/
void MOTOR_STOP(void);


#endif /* MOTOR_H_ */
