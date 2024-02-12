/* 
 * File:   ecu_button.c
 * Author: xcite
 *
 * Created on December 7, 2023, 7:22 PM
 */

#include "ecu_button.h"

/**
 * @brief Initializes the button.
 *
 * This function initializes the button by configuring its GPIO pin.
 *
 * @param button Pointer to the button structure.
 * @return Returns E_OK if initialization is successful, otherwise E_NOT_OK.
 */
Std_ReturnType
button_intialize(const button_t *button) {
    Std_ReturnType ret = E_OK;

    // Check if the button pointer is valid
    if (NULL == button) {
        ret = E_NOT_OK;
    } else {
        // Initialize the GPIO pin associated with the button
        ret = gpio_pin_initialize(&(button->pin_config));
    }

    return ret;
}

/**
 * @brief Reads the state of the button.
 *
 * This function reads the logical state of the button and determines if it is pressed or released.
 *
 * @param button Pointer to the button structure.
 * @param button_state Pointer to the variable where the button state will be stored.
 * @return Returns E_OK if the state is read successfully, otherwise E_NOT_OK.
 */
Std_ReturnType button_read_state(const button_t *button, button_state_t *button_state) {
    Std_ReturnType ret = E_OK;
    logic_t Button_Logic = GPIO_LOW;

    // Check if the button and button_state pointers are valid
    if ((NULL == button) || (NULL == button_state)) {
        ret = E_NOT_OK;
    } else {
        // Read the logical state of the button from its GPIO pin
        gpio_pin_read_logic(&(button->pin_config), &Button_Logic);

        // Determine the button state based on the active level
        if (BUTTON_ACTVE_HIGH == button->button_active) {
            if (GPIO_LOW == Button_Logic) {
                *button_state = BUTTON_RELEASED;
            } else {
                *button_state = BUTTON_PRESSED;
            }
        } else if (BUTTON_ACTIVE_LOW == button->button_active) {
            if (GPIO_HIGH == Button_Logic) {
                *button_state = BUTTON_RELEASED;
            } else {
                *button_state = BUTTON_PRESSED;
            }
        }
    }

    return ret;
}
/*
   // Assuming these variables are declared and initialized somewhere in your code
// button_state_t btn_state;
// uint16_t btn_counter = 0;
// button_state_t btn_last_valid_state = BUTTON_RELEASED;
// button_state_t btn_valid_state;

// Your denouncing algorithm
ret = button_read_state(&button1, &btn_state);
if (BUTTON_PRESSED == btn_state)
{
    btn_counter++;
    if (btn_counter > 500)
    {
        btn_valid_state = BUTTON_PRESSED;
    }
}
else
{
    btn_counter = 0;
    btn_valid_state = BUTTON_RELEASED;
}

// Check if the button state has changed
if (btn_last_valid_state != btn_valid_state)
{
    btn_last_valid_state = btn_valid_state;
    if (BUTTON_PRESSED == btn_valid_state)
    {
        // Your code for button pressed event
    }
    else
    {
        // Your code for button released event
    }
}

            
 */