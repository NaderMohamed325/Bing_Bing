/* 
 * File:   app.h
 * Author: xcite
 *
 * Created on November 14, 2023, 8:33 PM
 */
#ifndef APP_H
#define APP_H

/*----------------INCLUDES-------------------*/
#include "ECU_LAYER/ecu_layer_init.h"
#include "MCAL_LAYER/Interrupt/mcal_external_interrupt.h"
#include "MCAL_LAYER/EEPROM/hal_eeprom.h"
/*-----------------MACROS--------------------*/

extern lcd_4bit_mode lcd;
extern Seven_Segment_t seg2;
extern Seven_Segment_t seg1;

/*--------------MACROS_FUNCTIONS-----------*/


/*------------DATA_TYPES-------------------*/

/*------------FUNCTIONS_DECLARATION--------*/
void Application_initialize(void);


#endif	/* APP_H */

