 /*************************************************************************
 * Module: Motor
 *
 * File Name: Motor.h
 *
 * Description: Motor main functions
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time:  14 / 02 / 2020, 8:10 PM
 *
 *************************************************************************/
#include "Motor.h"

/*
 * Function Name: MOTOR_init
 *
 * Description: Function used to initialize the motor pins
 *
 * Arguments:
 *
 * 		Inputs:
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the Motor pins are initialized
 */
void MOTOR_init(void)
{
	/*Make the motor pins output pins*/
	SET_BIT(MOTOR_DIRECTION_PORT, FIRST_OUTPUT_PIN);
	SET_BIT(MOTOR_DIRECTION_PORT, SECOND_OUTPUT_PIN);

	/*Set the initial output of the motor pin to be zero*/
	CLEAR_BIT(MOTOR_CONTROL_PORT, FIRST_OUTPUT_PIN);
	CLEAR_BIT(MOTOR_CONTROL_PORT, SECOND_OUTPUT_PIN);
}

/*
 * Function Name: MOTOR_init
 *
 * Description: Function used to rotate the motor clock wise
 *
 * Arguments:
 *
 * 		Inputs:
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the Motor rotates Clock Wise
 */
void MOTOR_CW(void)
{
	CLEAR_BIT(MOTOR_CONTROL_PORT, SECOND_OUTPUT_PIN);
	SET_BIT(MOTOR_CONTROL_PORT, FIRST_OUTPUT_PIN);
}

/*
 * Function Name: MOTOR_init
 *
 * Description: Function used to rotate the motor anti clock wise
 *
 * Arguments:
 *
 * 		Inputs:
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the Motor rotates anti Clock Wise
 */
void MOTOR_ACW(void)
{
	SET_BIT(MOTOR_CONTROL_PORT, SECOND_OUTPUT_PIN);
	CLEAR_BIT(MOTOR_CONTROL_PORT, FIRST_OUTPUT_PIN);

}


/*
 * Function Name: MOTOR_init
 *
 * Description: Function used to stop the motor
 *
 * Arguments:
 *
 * 		Inputs:
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the Motor stops
 */
void MOTOR_STOP(void)
{
	CLEAR_BIT(MOTOR_CONTROL_PORT, FIRST_OUTPUT_PIN);
	CLEAR_BIT(MOTOR_CONTROL_PORT, SECOND_OUTPUT_PIN);
}


