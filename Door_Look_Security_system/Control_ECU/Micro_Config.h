/**********************************************************************
 * Module: Micro controler configurations
 *
 * File Name: Micro_Config.h
 *
 * Description: All configurations for a specific micro controller
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and Time: 28 / 12 / 2019,  2:12PM
 *
 *********************************************************************/

#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#ifndef F_CPU
#define F_CPU  8000000UL //1MHz Clock frequency
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#endif /* MICRO_CONFIG_H_ */
