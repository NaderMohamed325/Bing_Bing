/* 
 * File:   ecu_motor.h
 * Author: xcite
 *
 * Created on December 13, 2023, 10:41 PM
 */

#ifndef ECU_MOTOR_H
#define	ECU_MOTOR_H

/*----------------INCLUDES-------------------*/
#include "../../MCAL_LAYER/GPIO/hal_gpio.h" // Include the GPIO hardware abstraction layer
#include "ecu_motor_cfg.h"

/*-----------------MACROS--------------------*/

/*--------------MACROS_FUNCTIONS-----------*/

/*------------DATA_TYPES-------------------*/

// Enum to represent the state of the DC motor

typedef enum {
    DC_MOTOR_PIN_1=0,
    DC_MOTOR_PIN_2
} Motor_index;

typedef enum {
    MOTOR_OFF = 0, // Motor is off
    MOTOR_ON // Motor is on
} Dc_motor_state_t;

// Structure to represent the DC motor, containing two sets of pins

typedef struct {
    pin_config_t dc_motor_pin[2]; // Two sets of pins for the DC motor
} Dc_motor_t;

/*------------FUNCTIONS_DECLARATION--------*/

/**
 * @brief Initializes the DC motor by configuring its pins.
 *
 * @param Dc_motor Pointer to the Dc_motor_t structure representing the DC motor.
 * @return Std_ReturnType Status of the initialization (E_OK if successful, E_NOT_OK otherwise).
 */
Std_ReturnType Dc_motor_initialize(const Dc_motor_t * Dc_motor);

/**
 * @brief Rotates the DC motor to the right.
 *
 * @param Dc_motor Pointer to the Dc_motor_t structure representing the DC motor.
 * @return Std_ReturnType Status of the rotation (E_OK if successful, E_NOT_OK otherwise).
 */
Std_ReturnType Dc_motor_rotate_right(const Dc_motor_t * Dc_motor);

/**
 * @brief Rotates the DC motor to the left.
 *
 * @param Dc_motor Pointer to the Dc_motor_t structure representing the DC motor.
 * @return Std_ReturnType Status of the rotation (E_OK if successful, E_NOT_OK otherwise).
 */
Std_ReturnType Dc_motor_rotate_left(const Dc_motor_t * Dc_motor);

/**
 * @brief Stops the DC motor.
 *
 * @param Dc_motor Pointer to the Dc_motor_t structure representing the DC motor.
 * @return Std_ReturnType Status of the stop operation (E_OK if successful, E_NOT_OK otherwise).
 */
Std_ReturnType Dc_motor_stop(const Dc_motor_t * Dc_motor);

#endif	/* ECU_MOTOR_H */
