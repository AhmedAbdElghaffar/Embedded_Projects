/**************************************************************
 * File name: ADC.h
 *
 * Description: Normal ADC Functions
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time: 7 / 1 / 2020 ,  1:00 AM
 *
 **************************************************************/

#include "ADC.h"

volatile uint16 g_ADC_reading; /* Global variable to carry the ADC reading */

/*
 * Pointer to function to carry the address of the operating function according to the chose mode (Interrupt or Pooling)
 */
void (*ADC_readChannel)(uint8);


/*********************************************************************************
 * 							Private Functions Prototypes
 ********************************************************************************/

static void ADC_readChannelPolling(uint8);		/*Function used to read the value of ADC in case of pooling*/
static void ADC_readChannelInterrupt(uint8);	/*Function used to read the value of ADC in case of Interrupt*/



/*
 * Function Name: ADC_init_init
 *
 * Description: This function is responsible for initializing the ADC According to the chosen mode
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-const ADC_Configurations *config_ptr
 * 					A constant data pointer to receive the ADC_configuraton structure data
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the ADC is initialized
 */
void ADC_init(const ADC_Configurations *config_ptr){

	/******************************** ADMUX OPTIONS *****************************************
	 * 1-Select the V_reference
	 * 2- Channel zero is selected by default
	 *************************************************************************************/

	ADMUX = (ADMUX & 0x3f) | ((config_ptr->V_ref)<<REFS0);
	SET_BIT(ADCSRA,ADEN);
	/*
	 * 1-Enable ADC by setting ADEN
	 * 2-Disaple interrupts  by clearing ADIE (Polling only)
	 * 	 Enable Interrupts by setting ADIE (Interruts only)
	 * 3-Select prescaler
	 */
	ADCSRA= (ADCSRA & 0xf7 ) | ((config_ptr->Mode)<<ADIE);
	ADCSRA= (ADCSRA & 0xf8 ) | (config_ptr->Frequency);

	/*Choosing the addres that will be placed in the global ADC pointer to function*/
	if((config_ptr->Mode)==Polling)
	{
		ADC_readChannel=&ADC_readChannelPolling; 	/*pointer to function now carries the address of the polling function*/
	}
	else
	{
		ADC_readChannel=&ADC_readChannelInterrupt;	/*pointer to function now carries the address of the Interrupt function*/
	}

}


/*
 * Function Name:ADC_readChannelPolling
 *
 * Description: This function is responsible reading the ADC register value
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-uint8 a_channel_num
 * 					the required channel that reads the analog input
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the ADC value is obtained using Polling
 */
static void ADC_readChannelPolling(uint8 a_channel_num){

	/*
	 * 1-Selecting the channel from ADMUX
	 * 2-Start Conversion
	 */
	ADMUX = (ADMUX & 0xE0 ) | (a_channel_num & 0x07);
	SET_BIT(ADCSRA,ADSC);

	/*
	 * 3-Polling tell tha ADC register is updated
	 */
	while(BIT_IS_CLEARED(ADCSRA,ADIF))
	{

	}
	/*
	 * 4-Clear the ADC interrupt flag
	 * 5-Read the ADC value
	 */
	SET_BIT(ADCSRA,ADIF);
	g_ADC_reading=ADC;
}


/*
 * Function Name:ADC_readChannelInterrupt
 *
 * Description: This function is responsible reading the ADC register value
 *
 * Arguments:
 *
 * 		Inputs:
 * 			1-uint8 a_channel_num
 * 					the required channel that reads the analog input
 *
 * 		Outputs:
 *
 * 	returns:
 * 		no returns(void), but the ADC value is obtained using Interrupt
 */
static void ADC_readChannelInterrupt(uint8 a_channel_num){
	/*
	 * 1-Selecting the channel from ADMUX
	 * 2-Start Conversion
	 */
	ADMUX = (ADMUX & 0xE0 ) | (a_channel_num & 0x07);
	SET_BIT(ADCSRA,ADSC);
}

/*
 * The interrupt handler of ADC
 */
ISR(ADC_vect){

	g_ADC_reading=ADC;

}
