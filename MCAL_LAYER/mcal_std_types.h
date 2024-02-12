/* 
 * File:   mcal_std_types.h
 * Author: xcite
 *
 * Created on November 14, 2023, 8:23 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H


/*----------------INCLUDES-------------------*/
#include "std_lin.h"
#include "compiler.h"

/*-----------------MACROS--------------------*/



/*--------------MACROS_FUNCTIONS-----------*/



/*------------DATA_TYPES-------------------*/
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef signed int sint32;
typedef signed char sint8;
typedef signed short sint16;
typedef uint8 Std_ReturnType;
#define     E_OK        (Std_ReturnType)0X01
#define     E_NOT_OK    (Std_ReturnType)0X00




/*------------FUNCTIONS_DECLARATION--------*/

#endif	/* MCAL_STD_TYPES_H */

