/* 
 * File:   ecu_keypad.c
 * Author: xcite
 *
 * Created on December 25, 2023, 2:21 PM
 */

#include "ecu_keypad.h"

// Define the values corresponding to each button on the keypad
const static uint8 btn_values[ECU_KEYPAD_ROW][ECU_KEYPAD_COL] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'#', '0', '=', '+'}
};

/**
 * @brief Initializes the keypad.
 * @param keypad Pointer to a Keypad_t structure containing the keypad configuration.
 * @return Standard return type indicating success or failure.
 */
Std_ReturnType keypad_initialize(const Keypad_t *keypad) {
    Std_ReturnType ret = E_OK;

    // Check if the keypad pointer is valid
    if (NULL == keypad) {
        ret = E_NOT_OK;
    } else {
        // Initialize each row pin of the keypad
        for (int i = 0; i < ECU_KEYPAD_ROW; i++) {
            ret = gpio_pin_initialize(&(keypad->keypad_row_pins[i]));
        }
        
        // Initialize each column pin of the keypad
        for (int i = 0; i < ECU_KEYPAD_COL; i++) {
            ret = gpio_pin_initialize(&(keypad->keypad_col_pins[i]));
        }
    }

    return ret;
}

/**
 * @brief Retrieves the value from the keypad.
 * @param keypad Pointer to a Keypad_t structure containing the keypad configuration.
 * @param value Reference parameter to store the retrieved value.
 * @return Standard return type indicating success or failure.
 */
Std_ReturnType keypad_get_value(const Keypad_t *keypad, uint8 *value) {
    Std_ReturnType ret = E_OK;

    // Check if the keypad and value pointers are valid
    if ((NULL == keypad) || (NULL == value)) {
        ret = E_NOT_OK;
    } else {
        // Iterate through each row of the keypad
        for (int i = 0; i < ECU_KEYPAD_ROW; i++) {
            logic_t value_pin = 0;

            // Set all rows to GPIO_LOW
            for (int j = 0; j < ECU_KEYPAD_ROW; j++) {
                ret = gpio_pin_write_logic(&(keypad->keypad_row_pins[j]), GPIO_LOW);
            }

            // Set the current row to GPIO_HIGH
            ret = gpio_pin_write_logic(&(keypad->keypad_row_pins[i]), GPIO_HIGH);
            __delay_ms(30);  // You may need to adjust this delay based on your requirements

            // Read the columns
            for (int j = 0; j < ECU_KEYPAD_COL; j++) {
                ret = gpio_pin_read_logic(&(keypad->keypad_col_pins[j]), &value_pin);

                // Check if the button is pressed (GPIO_HIGH)
                if (value_pin == GPIO_HIGH) {
                    *value = btn_values[i][j];
                    break;  // Exit the loop once a button is found
                }
            }
        }
    }

    return ret;
}