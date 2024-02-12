/* 
 * File:   ecu_motor.c
 * Author: xcite
 *
 * Created on December 13, 2023, 10:41 PM
 */
#include "ecu_motor.h"

// Static variables to hold the pin configurations for the DC motor

/**
 * @brief Initializes the DC motor by configuring its pins.
 *
 * @param Dc_motor Pointer to the Dc_motor_t structure representing the DC motor.
 * @return Std_ReturnType Status of the initialization (E_OK if successful, E_NOT_OK otherwise).
 */
Std_ReturnType Dc_motor_initialize(const Dc_motor_t * Dc_motor) {
    Std_ReturnType ret = E_OK;

    // Check if the input parameter is NULL
    if (NULL == Dc_motor) {
        ret = E_NOT_OK;
    } else {
       
        // Initialize the GPIO pins for the DC motor
        gpio_pin_initialize(&(Dc_motor->dc_motor_pin[DC_MOTOR_PIN_1]));
        gpio_pin_initialize(&(Dc_motor->dc_motor_pin[DC_MOTOR_PIN_2]));
    }

    return ret;
}

/**
 * @brief Rotates the DC motor to the right.
 *
 * @param Dc_motor Pointer to the Dc_motor_t structure representing the DC motor.
 * @return Std_ReturnType Status of the rotation (E_OK if successful, E_NOT_OK otherwise).
 */
Std_ReturnType Dc_motor_rotate_right(const Dc_motor_t * Dc_motor) {
    Std_ReturnType ret = E_OK;

    // Check if the input parameter is NULL
    if (NULL == Dc_motor) {
        ret = E_NOT_OK;
    } else {
        // Rotate the DC motor to the right by controlling the GPIO pins
        gpio_pin_write_logic(&(Dc_motor->dc_motor_pin[DC_MOTOR_PIN_1]), GPIO_HIGH);
        gpio_pin_write_logic(&(Dc_motor->dc_motor_pin[DC_MOTOR_PIN_2]), GPIO_LOW);
    }

    return ret;
}

/**
 * @brief Rotates the DC motor to the left.
 *
 * @param Dc_motor Pointer to the Dc_motor_t structure representing the DC motor.
 * @return Std_ReturnType Status of the rotation (E_OK if successful, E_NOT_OK otherwise).
 */
Std_ReturnType Dc_motor_rotate_left(const Dc_motor_t * Dc_motor) {
    Std_ReturnType ret = E_OK;

    // Check if the input parameter is NULL
    if (NULL == Dc_motor) {
        ret = E_NOT_OK;
    } else {
        // Rotate the DC motor to the left by controlling the GPIO pins
        gpio_pin_write_logic(&(Dc_motor->dc_motor_pin[DC_MOTOR_PIN_2]), GPIO_HIGH);
        gpio_pin_write_logic(&(Dc_motor->dc_motor_pin[DC_MOTOR_PIN_1]), GPIO_LOW);
    }

    return ret;
}

/**
 * @brief Stops the DC motor.
 *
 * @param Dc_motor Pointer to the Dc_motor_t structure representing the DC motor.
 * @return Std_ReturnType Status of the stop operation (E_OK if successful, E_NOT_OK otherwise).
 */
Std_ReturnType Dc_motor_stop(const Dc_motor_t * Dc_motor) {
    Std_ReturnType ret = E_OK;

    // Check if the input parameter is NULL
    if (NULL == Dc_motor) {
        ret = E_NOT_OK;
    } else {
        // Stop the DC motor by setting both GPIO pins to low
        gpio_pin_write_logic(&(Dc_motor->dc_motor_pin[DC_MOTOR_PIN_1]), GPIO_LOW);
        gpio_pin_write_logic(&(Dc_motor->dc_motor_pin[DC_MOTOR_PIN_2]), GPIO_LOW);
    }

    return ret;
}
