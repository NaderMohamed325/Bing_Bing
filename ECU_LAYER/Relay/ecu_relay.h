/*
 * File:   ecu_relay.h
 * Author: xcite
 * Created on December 13, 2023, 7:05 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/*----------------INCLUDES-------------------*/
#include "../../MCAL_LAYER/GPIO/hal_gpio.h" // Include the GPIO hardware abstraction layer
#include "ecu_relay_cfg.h"

/*-----------------MACROS--------------------*/

/*--------------MACROS_FUNCTIONS-----------*/

/*------------DATA_TYPES-------------------*/
typedef enum {
    RELAY_OFF = 0,
    RELAY_ON
} Relay_state_t;

typedef struct {
    uint8 pin_index : 3;      /**< Index of the relay pin. */
    uint8 port_index : 3;     /**< Index of the GPIO port. */
    uint8 Relay_state : 1;    /**< State of the relay (RELAY_OFF or RELAY_ON). */
} Relay_t;

/*------------FUNCTIONS_DECLARATION--------*/

/**
 * @brief Initializes the relay.
 *
 * @param _Relay Pointer to the Relay_t structure.
 *
 * @return Std_ReturnType Returns the status of the initialization (success or failure).
 */
Std_ReturnType Relay_initialize(const Relay_t *_Relay);

/**
 * @brief Turns the relay on.
 *
 * @param _Relay Pointer to the Relay_t structure.
 *
 * @return Std_ReturnType Returns the status of the operation (success or failure).
 */
Std_ReturnType Relay_on(const Relay_t *_Relay);

/**
 * @brief Turns the relay off.
 *
 * @param _Relay Pointer to the Relay_t structure.
 *
 * @return Std_ReturnType Returns the status of the operation (success or failure).
 */
Std_ReturnType Relay_off(const Relay_t *_Relay);

#endif	/* ECU_RELAY_H */
