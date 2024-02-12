/* 
 * File:   ecu_led.h
 * Author: xcite
 *
 * Created on November 14, 2023, 8:31 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/*----------------INCLUDES-------------------*/
#include "../../MCAL_LAYER/GPIO/hal_gpio.h" // Include the GPIO hardware abstraction layer

/*-----------------MACROS--------------------*/

/*--------------MACROS_FUNCTIONS-----------*/

/*------------DATA_TYPES-------------------*/
typedef enum {
    LED_OFF = 0, // Enumeration for LED off state
    LED_ON,      // Enumeration for LED on state
} Led_status;

typedef struct {
    uint8 port_index : 3; // Port index for the LED (3 bits)
    uint8 pin_index : 3;  // Pin index for the LED (3 bits)
    uint8 led_status : 1; // LED status (on/off) represented by 1 bit
} Led_t;

/*------------FUNCTIONS_DECLARATION--------*/

/**
 * @brief Initializes the LED.
 * 
 * This function initializes the LED specified by the provided Led_t structure.
 * 
 * @param Led Pointer to the Led_t structure representing the LED.
 * @return Std_ReturnType E_OK if initialization is successful, E_NOT_OK if the input pointer is NULL.
 */
Std_ReturnType led_intialize(const Led_t *Led);

/**
 * @brief Turns on the LED.
 * 
 * This function turns on the LED specified by the provided Led_t structure.
 * 
 * @param Led Pointer to the Led_t structure representing the LED.
 * @return Std_ReturnType E_OK if turning on is successful, E_NOT_OK if the input pointer is NULL.
 */
Std_ReturnType led_turn_on(const Led_t *Led);

/**
 * @brief Turns off the LED.
 * 
 * This function turns off the LED specified by the provided Led_t structure.
 * 
 * @param Led Pointer to the Led_t structure representing the LED.
 * @return Std_ReturnType E_OK if turning off is successful, E_NOT_OK if the input pointer is NULL.
 */
Std_ReturnType led_turn_off(const Led_t *Led);

/**
 * @brief Toggles the status of the LED.
 * 
 * This function toggles the status (on to off or off to on) of the LED specified by the provided Led_t structure.
 * 
 * @param Led Pointer to the Led_t structure representing the LED.
 * @return Std_ReturnType E_OK if toggling is successful, E_NOT_OK if the input pointer is NULL.
 */
Std_ReturnType led_toggle_status(const Led_t *Led);

#endif	/* ECU_LED_H */
