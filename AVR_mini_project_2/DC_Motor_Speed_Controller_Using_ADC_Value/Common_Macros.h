/*************************************************************************
 * Module: Common Macros
 *
 * File Name: Common_Macros.h
 *
 * Description: Common macros used in AVR projets
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and time:  28 / 12 / 2019, 1:53 PM
 *
 *************************************************************************/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_
/* Set a specific bit in any register (make its value =1) */
#define SET_BIT(REG,BIT_NUMBER)			(REG |= (1<<BIT_NUMBER))

/* Claer a specific bit in any register (make its value = 0) */
#define	CLEAR_BIT(REG,BIT_NUMBER)		(REG &= ~(1<<BIT_NUMBER))

/* Toggle any bit in any register (Change its value form 1 to 0 or vice versa) */
#define TOGGLE_BIT(REG,BIT_NUMBER)		(REG ^= (1<<BIT_NUMBER))

/* Read a specific bit value in any register (1 or 0 ?) */
#define GET_BIT(REG,BIT_NUMBER)			(REG & (1<<BIT_NUMBER))

/* Check if a specific bit is set in any register and returns its value(true if it's set) */
#define BIT_IS_SET(REG,BIT_NUMBER)		(REG & (1<<BIT_NUMBER))

/* Check if a specific bit is cleared in any register and returns its value(true if it's cleared) */
#define BIT_IS_CLEARED(REG,BIT_NUMBER)	(!(REG & (1<<BIT_NUMBER)))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,NUM)	( REG = (REG>>NUM) | (REG<<8*sizeof(REG)-NUM) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,NUM)	( REG = (REG<<NUM) | (REG>>8*sizeof(REG)-NUM) )


#endif /* COMMON_MACROS_H_ */
