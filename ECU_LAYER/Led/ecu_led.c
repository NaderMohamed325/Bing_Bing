#include "ecu_led.h"
#include "ecu_led_cfg.h"

/**
 * @brief Initializes the LED.
 * 
 * This function initializes the LED specified by the provided Led_t structure.
 * 
 * @param Led Pointer to the Led_t structure representing the LED.
 * @return Std_ReturnType E_OK if initialization is successful, E_NOT_OK if the input pointer is NULL.
 */
Std_ReturnType led_intialize(const Led_t *Led) {
    Std_ReturnType ret = E_OK;
    if (NULL == Led) {
        ret = E_NOT_OK;
    } else {
        // Configure GPIO pin for the LED
        pin_config_t pin_obj = {
            .direction = GPIO_OUTPUT,
            .logic = Led->led_status,
            .pin = Led->pin_index,
            .port = Led->port_index,
        };
        gpio_pin_initialize(&pin_obj);
    }
    return ret;
}

/**
 * @brief Turns on the LED.
 * 
 * This function turns on the LED specified by the provided Led_t structure.
 * 
 * @param Led Pointer to the Led_t structure representing the LED.
 * @return Std_ReturnType E_OK if turning on is successful, E_NOT_OK if the input pointer is NULL.
 */
Std_ReturnType led_turn_on(const Led_t *Led) {
    Std_ReturnType ret = E_OK;
    if (NULL == Led) {
        ret = E_NOT_OK;
    } else {
        // Set GPIO pin to HIGH to turn on the LED
        pin_config_t pin_obj = {
            .direction = GPIO_OUTPUT,
            .logic = Led->led_status,
            .pin = Led->pin_index,
            .port = Led->port_index,
        };
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return ret;
}

/**
 * @brief Turns off the LED.
 * 
 * This function turns off the LED specified by the provided Led_t structure.
 * 
 * @param Led Pointer to the Led_t structure representing the LED.
 * @return Std_ReturnType E_OK if turning off is successful, E_NOT_OK if the input pointer is NULL.
 */
Std_ReturnType led_turn_off(const Led_t *Led) {
    Std_ReturnType ret = E_OK;
    if (NULL == Led) {
        ret = E_NOT_OK;
    } else {
        // Set GPIO pin to LOW to turn off the LED
        pin_config_t pin_obj = {
            .direction = GPIO_OUTPUT,
            .logic = Led->led_status,
            .pin = Led->pin_index,
            .port = Led->port_index,
        };
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    return ret;
}

/**
 * @brief Toggles the status of the LED.
 * 
 * This function toggles the status (on to off or off to on) of the LED specified by the provided Led_t structure.
 * 
 * @param Led Pointer to the Led_t structure representing the LED.
 * @return Std_ReturnType E_OK if toggling is successful, E_NOT_OK if the input pointer is NULL.
 */
Std_ReturnType led_toggle_status(const Led_t *Led) {
    Std_ReturnType ret = E_OK;
    if (NULL == Led) {
        ret = E_NOT_OK;
    } else {
        // Toggle the logic state of the GPIO pin for the LED
        pin_config_t pin_obj = {
            .direction = GPIO_OUTPUT,
            .logic = Led->led_status,
            .pin = Led->pin_index,
            .port = Led->port_index,
        };
        gpio_pin_toggle_logic(&pin_obj);
    }
    return ret;
}
