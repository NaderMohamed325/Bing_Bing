/* 
 * File:   mcal_interrupt_manager.h
 * Author: xcite
 *
 * Created on February 1, 2024, 8:28 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define MCAL_INTERRUPT_MANAGER_H

/*----------------INCLUDES-------------------*/
#include "mcal_interrupt_cfg.h"  // Include configuration file for interrupts
#include "../GPIO/hal_gpio.h"    // Include GPIO header for pin initialization

/*-----------------MACROS--------------------*/
// No macros are defined in this header file

/*--------------MACROS_FUNCTIONS-----------*/
// No macros-related functions are defined in this header file

/*------------DATA_TYPES-------------------*/
// No specific data types are defined in this header file

/*------------FUNCTIONS_DECLARATION--------*/

// Interrupt service routines (ISRs) declarations
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 source);
void RB5_ISR(uint8 source);
void RB6_ISR(uint8 source);
void RB7_ISR(uint8 source);

#endif /* MCAL_INTERRUPT_MANAGER_H */
