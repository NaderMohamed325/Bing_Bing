/* 
 * File:   mcal_interrupt_cfg.h
 * Author: xcite
 *
 * Created on February 1, 2024, 8:39 PM
 */

#ifndef MCAL_INTERRUPT_CFG_H
#define	MCAL_INTERRUPT_CFG_H

/*----------------INCLUDES-------------------*/
#include <xc.h>
#include "../mcal_std_types.h"    // Include standard data types header file
#include "mcal_interrupt_gen_cfg.h"
#include "../GPIO/hal_gpio.h"
/*-----------------MACROS--------------------*/

// Macros for interrupt enable/disable states
#define INTERRUPT_ENABLE        1
#define INTERRUPT_DISABLE       0

// Macros for interrupt occurrence states
#define INTERRUPT_OCCUR         1
#define INTERRUPT_NOT_OCCUR     0

// Macros for interrupt priority enable/disable states
#define INTERRUPT_PRIORITY_ENABLE     1
#define INTERRUPT_PRIORITY_DISABLE    0

/*--------------MACROS_FUNCTIONS-----------*/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE   

// Macros to enable/disable interrupt priority levels
#define INTERRUPT_Pirority_Level_Enable()           (RCONbits.IPEN   = 1)
#define INTERRUPT_Pirority_Level_Disable()          (RCONbits.IPEN   = 0)

// Macros to enable/disable global high priority interrupts
#define INTERRUPT_Global_Interrupt_High_Enable()    (INTCONbits.GIEH = 1)
#define INTERRUPT_Global_Interrupt_High_Disnable()  (INTCONbits.GIEH = 0)

// Macros to enable/disable global low priority interrupts
#define INTERRUPT_Global_Interrupt_Low_Enable()     (INTCONbits.GIEL = 1)
#define INTERRUPT_Global_Interrupt_Low_Disnable()   (INTCONbits.GIEL = 0)


#else
#define INTERRUPT_Global_Interrupt_Enable()    (INTCONbits.GIEH = 1)
#define INTERRUPT_Global_Interrupt_Disable()  (INTCONbits.GIEH = 0)

// Macros to enable/disable peripheral interrupts
#define INTERRUPT_Peripheral_Interrupt_Enable()     (INTCONbits.PEIE = 1)
#define INTERRUPT_Peripheral_Interrupt_Disable()    (INTCONbits.PEIE = 0)

#endif

/*------------DATA_TYPES-------------------*/

typedef enum {
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY
} interrupt_priority_cfg;


/*------------FUNCTIONS_DECLARATION--------*/

// No function declarations in this file

#endif	/* MCAL_INTERRUPT_CFG_H */
