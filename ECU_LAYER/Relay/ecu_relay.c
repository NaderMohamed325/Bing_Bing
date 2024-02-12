/* 
 * File:   ecu_led.c
 * Author: xcite
 *
 * Created on November 14, 2023, 8:31 PM
 */

#include "ecu_relay.h"

/**
 * @brief Initializes the relay.
 *
 * @param _Relay Pointer to the Relay_t structure.
 *
 * @return Std_ReturnType Returns the status of the initialization (E_OK if successful, E_NOT_OK if an error occurs).
 */
Std_ReturnType Relay_initialize(const Relay_t *_Relay)
{
  Std_ReturnType ret = E_OK;
  if (NULL == _Relay)
  {
    ret = E_NOT_OK;
  } else
  {
    // Configure the pin for the relay
    pin_config_t pin_obj = {
        .direction = GPIO_OUTPUT,
        .logic = _Relay->Relay_state,
        .pin = _Relay->pin_index,
        .port = _Relay->port_index
    };

    // Initialize the GPIO pin
    gpio_pin_initialize(&(pin_obj));
  }

  return ret;
}

/**
 * @brief Turns the relay on.
 *
 * @param _Relay Pointer to the Relay_t structure.
 *
 * @return Std_ReturnType Returns the status of the operation (E_OK if successful, E_NOT_OK if an error occurs).
 */
Std_ReturnType Relay_on(const Relay_t *_Relay)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _Relay)
    {
        ret = E_NOT_OK;
    } else
    {
        // Configure the pin for the relay
        pin_config_t pin_obj = {
            .direction = GPIO_OUTPUT,
            .logic = _Relay->Relay_state,
            .pin = _Relay->pin_index,
            .port = _Relay->port_index
        };

        // Set the GPIO pin logic to high to turn on the relay
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }

    return ret;
}

/**
 * @brief Turns the relay off.
 *
 * @param _Relay Pointer to the Relay_t structure.
 *
 * @return Std_ReturnType Returns the status of the operation (E_OK if successful, E_NOT_OK if an error occurs).
 */
Std_ReturnType Relay_off(const Relay_t *_Relay)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _Relay)
    {
        ret = E_NOT_OK;
    } else
    {
        // Configure the pin for the relay
        pin_config_t pin_obj = {
            .direction = GPIO_OUTPUT,
            .logic = _Relay->Relay_state,
            .pin = _Relay->pin_index,
            .port = _Relay->port_index
        };

        // Set the GPIO pin logic to low to turn off the relay
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }

    return ret;
}
