/* 
 * File:   ecu_button.h
 * Author: xcite
 *
 * Created on December 7, 2023, 7:22 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/*----------------INCLUDES-------------------*/
#include "ecu_button_cfg.h"
#include "../../MCAL_LAYER/GPIO/hal_gpio.h" // Include the GPIO hardware abstraction layer

/*-----------------MACROS--------------------*/

/*--------------MACROS_FUNCTIONS-----------*/
// No specific macros functions in this header file

/*------------DATA_TYPES-------------------*/
/**
 * @brief Enumeration for button states.
 */
typedef enum {
    BUTTON_PRESSED = 0, /**< Button is pressed. */
    BUTTON_RELEASED,    /**< Button is released. */
} button_state_t;

/**
 * @brief Enumeration for button active levels.
 */
typedef enum {
    BUTTON_ACTVE_HIGH = 0, /**< Button active high configuration. */
    BUTTON_ACTIVE_LOW,     /**< Button active low configuration. */
} button_active_t;

/**
 * @brief Structure representing a button.
 */
typedef struct {
    pin_config_t pin_config;     /**< Configuration for the associated GPIO pin. */
    button_active_t button_active; /**< Active level of the button. */
    button_state_t button_state;   /**< Current state of the button. */
} button_t;

/*------------FUNCTIONS_DECLARATION--------*/
/**
 * @brief Initializes the button.
 *
 * This function initializes the button by configuring its GPIO pin.
 *
 * @param button Pointer to the button structure.
 * @return Returns E_OK if initialization is successful, otherwise E_NOT_OK.
 */
Std_ReturnType button_intialize(const button_t *button);

/**
 * @brief Reads the state of the button.
 *
 * This function reads the logical state of the button and determines if it is pressed or released.
 *
 * @param button Pointer to the button structure.
 * @param button_state Pointer to the variable where the button state will be stored.
 * @return Returns E_OK if the state is read successfully, otherwise E_NOT_OK.
 */
Std_ReturnType button_read_state(const button_t *button, button_state_t *button_state);

#endif	/* ECU_BUTTON_H */
