/* 
 * File:   EEPROM.h
 * Author: xcite
 *
 * Created on February 6, 2024, 4:00 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H
/*----------------INCLUDES-------------------*/
#include "../../MCAL_LAYER/Interrupt/mcal_internal_interrupt.h"

/*-----------------MACROS--------------------*/



/*--------------MACROS_FUNCTIONS-----------*/



/*------------DATA_TYPES-------------------*/



/*------------FUNCTIONS_DECLARATION--------*/

/**
 * @brief Writes a byte to the EEPROM at the specified address.
 * @param bAdd The EEPROM address to write the data to.
 * @param bData The byte of data to be written.
 * @return Std_ReturnType Returns E_OK if the write operation is successful, otherwise E_NOT_OK.
 */
Std_ReturnType EEPROM_Write_Byte(uint16 bAdd, uint8 bData);

/**
 * @brief Reads a byte from the EEPROM at the specified address.
 * @param bAdd The EEPROM address to read the data from.
 * @param bData Pointer to a variable where the read data will be stored.
 * @return Std_ReturnType Returns E_OK if the read operation is successful, otherwise E_NOT_OK.
 */
Std_ReturnType EEPROM_Read_Byte(uint16 bAdd, uint8 *bData);

#endif	/* EEPROM_H */


