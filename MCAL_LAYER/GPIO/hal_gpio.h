/* 
 * File:   hal_gpio.h
 * Author: xcite
 *
 * Created on November 14, 2023, 8:16 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H



/*-----------------------------------------------------------------INCLUDES-------------------------------------------------------*/
#include <xc.h>
#include "../mcal_std_types.h"
#include "../decive_config.h"
#include "hal_pio_cnfg.h"
/*------------------------------------------------------------------MACROS-------------------------------------------------------*/
#define BIT_MASK    (uint8)1
#define PORT_MAX_PINS 8
#define PORT_MAX 5
#define ENABLE 0X01
#define DISABLE 0X00
#define PORT_MASK 0XFF
#define _XTAL_FREQ 8000000 // Replace with your oscillator frequency (e.g., 8MHz)
#define and &&
#define or  ||
#define not !

/*-------------------------------------------------------------MACROS_FUNCTIONS------------------------------------------------*/
#define HWREG8(_X)       (*((volatile uint8 *)(_X)))
#define SET_BIT(REG, BIT_POS)   (REG |= (BIT_MASK << BIT_POS))
#define CLR_BIT(REG, BIT_POS)   (REG &= ~(BIT_MASK << BIT_POS))
#define TOG_BIT(REG, BIT_POS)   (REG ^= (BIT_MASK << BIT_POS))
#define READ_BIT(REG, BIT_POS)  ((REG >> BIT_POS) & BIT_MASK)

/*-----------------------------------------------------------------DATA_TYPES------------------------------------------------------*/
typedef enum {
    GPIO_LOW = 0,
    GPIO_HIGH
} logic_t;

typedef enum {
    GPIO_OUTPUT = 0,
    GPIO_INPUT = 1,
} direction_t;

typedef enum {
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
} port_index_t;

typedef enum {
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
} pin_index_t;

typedef struct {
    uint8 port : 3; /* @ref port_index_t */
    uint8 pin : 3; /* @ref pin_index_t*/
    uint8 direction : 1; /*@ref direction_t*/
    uint8 logic : 1; /*@ref logic_t*/
} pin_config_t;



/*--------------------------------------------------FUNCTIONS_DECLARATION--------------------------------------------------*/
/**
 * @brief Initializes the direction of a GPIO pin.
 *
 * This function initializes the direction of a specified GPIO pin using the provided pin configuration.
 *
 * @param _pin_config Pointer to the pin configuration structure.
 * @return Standard return type indicating the success or failure of the operation.
 */
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t * _pin_config);

/**
 * @brief Gets the direction status of a GPIO pin.
 *
 * This function retrieves the current direction status of a specified GPIO pin.
 *
 * @param _pin_config Pointer to the pin configuration structure.
 * @param dic_status Pointer to the variable to store the direction status.
 * @return Standard return type indicating the success or failure of the operation.
 */
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t * _pin_config, direction_t *dic_status);

/**
 * @brief Writes logic to a GPIO pin.
 *
 * This function writes a specified logic level to a specified GPIO pin.
 *
 * @param _pin_config Pointer to the pin configuration structure.
 * @param logic Logic level to be written to the GPIO pin.
 * @return Standard return type indicating the success or failure of the operation.
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t * _pin_config, logic_t logic_);

/**
 * @brief Reads logic from a GPIO pin.
 *
 * This function reads the logic level from a specified GPIO pin.
 *
 * @param _pin_config Pointer to the pin configuration structure.
 * @param logic Pointer to the variable to store the read logic level.
 * @return Standard return type indicating the success or failure of the operation.
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t * _pin_config, logic_t *logic_);

/**
 * @brief Toggles the logic level of a GPIO pin.
 *
 * This function toggles the logic level of a specified GPIO pin.
 *
 * @param _pin_config Pointer to the pin configuration structure.
 * @return Standard return type indicating the success or failure of the operation.
 */
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * _pin_config);
/*
 * 
 * 
 * 
 * 
 * 
 * 
 */
Std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config);


/**
 * @brief Initializes the direction of a GPIO port.
 *
 * This function initializes the direction of a specified GPIO port using the provided port index.
 *
 * @param port Port index specifying the GPIO port to be initialized.
 * @return Standard return type indicating the success or failure of the operation.
 */
Std_ReturnType gpio_port_direction_intialize(port_index_t port, uint8 direction);

/**
 * @brief Gets the direction status of a GPIO port.
 *
 * This function retrieves the current direction status of a specified GPIO port.
 *
 * @param port Port index specifying the GPIO port to query.
 * @param dic_status Pointer to the variable to store the direction status.
 * @return Standard return type indicating the success or failure of the operation.
 */
Std_ReturnType gpio_port_get_direction_status(port_index_t port, direction_t *dic_status);

/**
 * @brief Writes logic to a GPIO port.
 *
 * This function writes a specified logic level to all pins of a specified GPIO port.
 *
 * @param port Port index specifying the GPIO port to write to.
 * @param logic Logic level to be written to the GPIO port.
 * @return Standard return type indicating the success or failure of the operation.
 */
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic);

/**
 * @brief Reads logic from a GPIO port.
 *
 * This function reads the logic level from all pins of a specified GPIO port.
 *
 * @param port Port index specifying the GPIO port to read from.
 * @param logic Pointer to the variable to store the read logic level.
 * @return Standard return type indicating the success or failure of the operation.
 */
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic);

/**
 * @brief Toggles the logic level of all pins in a GPIO port.
 *
 * This function toggles the logic level of all pins in a specified GPIO port.
 *
 * @param port Port index specifying the GPIO port to toggle.
 * @return Standard return type indicating the success or failure of the operation.
 */
Std_ReturnType gpio_port_toggle_logic(port_index_t port);





#endif	/* HAL_GPIO_H */