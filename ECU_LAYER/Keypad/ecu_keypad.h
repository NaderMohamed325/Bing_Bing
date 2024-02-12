/**
 * @file    ecu_keypad.h
 * @brief   Header file for the ECU (Electronic Control Unit) Keypad module.
 * @author  xcite
 * @date    December 25, 2023
 *
 * This file contains the declaration of functions and data types
 * necessary for interacting with a keypad in an embedded system.
 */

#ifndef ECU_KEYPAD_H
#define ECU_KEYPAD_H

/*---------------- INCLUDES -------------------*/
#include "../../MCAL_LAYER/GPIO/hal_gpio.h" // Include the GPIO hardware abstraction layer
#include "ecu_keypad_cfg.h"

/*---------------- MACROS --------------------*/
#define ECU_KEYPAD_ROW 4
#define ECU_KEYPAD_COL 4

/*---------------- DATA TYPES -----------------*/
/**
 * @struct Keypad_t
 * @brief Structure to store the configuration of a keypad.
 */
typedef struct {
    pin_config_t keypad_row_pins[ECU_KEYPAD_ROW]; /**< Array of pin configurations for keypad rows. */
    pin_config_t keypad_col_pins[ECU_KEYPAD_COL]; /**< Array of pin configurations for keypad columns. */
} Keypad_t;

/*------------ FUNCTION DECLARATIONS ----------*/
/**
 * @brief Initializes the keypad.
 * @param keypad Pointer to a Keypad_t structure containing the keypad configuration.
 * @return Standard return type indicating success or failure.
 */
Std_ReturnType keypad_initialize(const Keypad_t *keypad);

/**
 * @brief Retrieves the value from the keypad.
 * @param keypad Pointer to a Keypad_t structure containing the keypad configuration.
 * @param value Reference parameter to store the retrieved value.
 * @return Standard return type indicating success or failure.
 */
Std_ReturnType keypad_get_value(const Keypad_t *keypad, uint8 *value);

#endif /* ECU_KEYPAD_H */
