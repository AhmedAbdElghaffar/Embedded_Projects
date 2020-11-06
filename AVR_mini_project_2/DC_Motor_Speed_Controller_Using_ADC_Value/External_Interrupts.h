
/*******************************************************************
 * File name: External_Inturrupts.h
 *
 * Description: Contains External Interrupts settings values
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time: 7 / 1 / 2020,  7:20 PM
 *
 *********************************************************************/

#ifndef EXTERNAL_INTERRUPTS_H_
#define EXTERNAL_INTERRUPTS_H_

#include "Std_types.h"
#include "Micro_Config.h"
#include "Common_Macros.h"

/**************************************************************************
 * 							Type Declaration
 *************************************************************************/

typedef enum
{
	Low_Lvl , Logical_Change , Falling , Rising
}INT_0_1_senseControl;

typedef enum
{
	Falling_2 , Rinsing_2
}INT2_senseControl;

typedef struct
{
	INT_0_1_senseControl Mode_0;
}INT0_configType;

typedef struct
{
	INT_0_1_senseControl Mode_1;
}INT1_configType;

typedef struct
{
	INT2_senseControl    Mode_2;
}INT2_configType;

/******************************************************************************
 * 						Functions Prototype
 ****************************************************************************/

/* This function is responsible for initializing INT0 and
 * choosing the function that will be executed by Interrupt handler of INT0*/
void INT0_init(const INT0_configType *,void(* const)(void));

/* This function is responsible for initializing INT1 and
 * choosing the function that will be executed by Interrupt handler of INT1*/
void INT1_init(const INT1_configType *,void(* const)(void));

/* This function is responsible for initializing INT2 and
 * choosing the function that will be executed by Interrupt handler of INT2*/
void INT2_init(const INT2_configType *,void(* const)(void));


#endif /* EXTERNAL_INTERRUPTS_H_ */
