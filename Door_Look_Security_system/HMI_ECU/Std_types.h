/*********************************************************
 * Module: Common platform types
 *
 * File Name: Std_types.h
 *
 * Description: Common Data types for AVR
 *
 * Author: Ahmed Abd Elghaffar
 *
 * Date and Time: 28 / 12 / 2019, 1:35 PM
 *
 ********************************************************/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* Boolean Data Type */
typedef unsigned char bool;

/* Boolean Values */

#ifndef True
#define True 		(1u)
#endif

#ifndef False
#define False 		(0u)
#endif

#ifndef HIGH
#define HIGH 		(1u)
#endif

#ifndef LOW
#define LOW 		(0u)
#endif

#define NULL ((void*)0)

typedef unsigned char 			uint8;			/* from 	0 			to 		255						*/
typedef signed char				sint8;			/* from 	-128 		to 		127 					*/
typedef unsigned short			uint16;			/* from 	0 			to 		65535 					*/
typedef signed short			sint16;			/* from 	-32768 		to 		32677 					*/
typedef unsigned long			uint32;			/* from 	0 			to 		4294967295 				*/
typedef signed long				sint32;			/* from 	-2147483648 to 		2147483647 				*/
typedef unsigned long long    	uint64;         /* from 	0 			to		18446744073709551615  	*/
typedef signed long long      	sint64;
typedef float                 	float32;
typedef double                	float64;


#endif /* STD_TYPES_H_ */
