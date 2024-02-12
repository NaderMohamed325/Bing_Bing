
/* 
 * File:   EEPROM.c
 * Author: xcite
 *
 * Created on February 6, 2024, 4:00 PM
 */

/*----------------INCLUDES-------------------*/
#include "hal_eeprom.h"

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
Std_ReturnType EEPROM_Write_Byte(uint16 bAdd, uint8 bData) {
    Std_ReturnType ret = E_OK;

    // Save the global interrupt status
    uint8 Global_Interrupt_Status = INTCONbits.GIE;

    // Set the high and low bytes of the EEPROM address
    EEADRH = (uint8) ((bAdd >> 8) & (0b11111111));
    EEADR = (uint8) (bAdd & 0b000000011);

    // Set the data to be written
    EEDATA = bData;

    // Configure EEPROM control bits
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;

    // Disable global interrupts during write operation

    INTERRUPT_Global_Interrupt_Disable();

    // Enable write sequence
    EECON2 = 0X55;
    EECON2 = 0XAA;
    EECON1bits.WR = 1;

    // Wait for write completion
    while (EECON1bits.WR);

    // Disable write after completion
    EECON1bits.WR = 0;

    // Enable global interrupts
    INTERRUPT_Global_Interrupt_Enable();

    return ret;
}

/**
 * @brief Reads a byte from the EEPROM at the specified address.
 * @param bAdd The EEPROM address to read the data from.
 * @param bData Pointer to a variable where the read data will be stored.
 * @return Std_ReturnType Returns E_OK if the read operation is successful, otherwise E_NOT_OK.
 */
Std_ReturnType EEPROM_Read_Byte(uint16 bAdd, uint8 *bData) {
    Std_ReturnType ret = E_OK;

    // Check if the pointer is valid
    if (NULL == bData) {
        ret = E_NOT_OK;
    } else {
        // Set the high and low bytes of the EEPROM address
        EEADRH = (uint8) ((bAdd >> 8) & (0b11111111));
        EEADR = (uint8) (bAdd & 0b000000011);

        // Configure EEPROM control bits for read operation
        EECON1bits.EEPGD = 0;
        EECON1bits.CFGS = 0;
        EECON1bits.RD = 1;

        // Nop instructions for delay
        NOP();
        NOP();

        // Read the data
        *bData = EEDATA;
    }

    return ret;
}
