/**************************************************************
 * File name: ADC.h
 *
 * Description: Normal ADC settings
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time: 7 / 1 / 2020,  1:09 AM
 *
 **************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "Std_types.h"
#include "Micro_Config.h"
#include "Common_Macros.h"

/**************************************************************
 * 				Type Declaration
 *************************************************************/


volatile extern uint16 g_ADC_reading; 		/* Global variable to carry the ADC reading */

/*
 * Pointer to function to carry the address of the operating function according to the chose mode (Interrupt or Pooling)
 */
extern void (*ADC_readChannel)(uint8);

typedef enum
{
	AREF , AVCC , Reserved , Internal_2_56
}ADC_ReferenceVolt;

typedef enum
{
	F_CPU_2=1 , F_CPU_4 , F_CPU_8 , F_CPU_16 , F_CPU_32 ,
	F_CPU_64 , F_CPU_128
}ADC_Frequency;

typedef enum
{
	Polling, Interrupt
}ADC_Mode;

typedef struct
{
	ADC_ReferenceVolt V_ref;
	ADC_Frequency Frequency;
	ADC_Mode Mode;
}ADC_Configurations;

/**************************************************************
 * 				Functions Prototype
 *************************************************************/


void ADC_init(const ADC_Configurations*); /*function used to initialize the ADC and choosing
											the address of the "ADC_readChannel" pointer to function */


#endif /* ADC_H_ */
