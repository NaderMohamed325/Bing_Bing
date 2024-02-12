/* 
 * File:   hal_gpio.c
 * Author: xcite
 *
 * Created on November 14, 2023, 8:16 PM
 */



#include "hal_gpio.h"
volatile uint8 *tris_registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};

volatile uint8 *lat_registers [] = {&LATA, &LATB, &LATC, &LATD, &LATE};

volatile uint8 *port_registers [] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};
/*------------------------------------------------------------PINS------------------------------------------------------*/
#if GPIO_PORT_PIN_CONFIG == ENABLE

Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config) {
    Std_ReturnType ret = E_OK;

    if (NULL == _pin_config || (_pin_config->pin > PORT_MAX_PINS - 1)) {
        ret = E_NOT_OK;
    } else {
        switch (_pin_config->direction) {

            case GPIO_OUTPUT:
                CLR_BIT(*tris_registers[_pin_config->port], _pin_config->pin);

                break;

            case GPIO_INPUT:
                SET_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
                break;

            default:ret = E_NOT_OK;

        }

    }
    return ret;
}

Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *dic_status) {
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config || NULL == dic_status || (_pin_config->pin > PORT_MAX_PINS - 1)) {
        ret = E_NOT_OK;
    } else {
        *(dic_status) = READ_BIT(*tris_registers[_pin_config->port], _pin_config->pin);

    }
    return ret;
}

Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic_) {
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config || _pin_config->pin > PORT_MAX_PINS - 1) {
        ret = E_NOT_OK;
    } else {
        switch (logic_) {
            case GPIO_HIGH:

                SET_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
                break;

            case GPIO_LOW:
                CLR_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
                break;

            default:
                ret = E_NOT_OK;
                break;
        }

    }

    return ret;
}

Std_ReturnType gpio_pin_read_logic(const pin_config_t * _pin_config, logic_t *logic_) {
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config || NULL == logic_ || _pin_config->pin > PORT_MAX_PINS - 1) {
        ret = E_NOT_OK;
    } else {
        *(logic_) = READ_BIT(*port_registers[_pin_config->port], _pin_config->pin);

    }
    return ret;
}

Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * _pin_config) {
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config || _pin_config->pin > PORT_MAX_PINS - 1) {
        ret = E_NOT_OK;
    } else {
        TOG_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
    }
    return ret;
}

Std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config) {
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config || _pin_config->pin > PORT_MAX_PINS - 1) {
        ret = E_NOT_OK;
    } else {
        gpio_pin_direction_intialize(_pin_config);
        gpio_pin_write_logic(_pin_config, _pin_config->logic);
    }

    return ret;
}

#endif
/*----------------------------------------------------------PORTS-------------------------------------------------------*/
#if GPIO_PORT_CONFIG ==ENABLE

Std_ReturnType gpio_port_direction_intialize(port_index_t port, uint8 direction) {
    Std_ReturnType ret = E_OK;
    if (port > PORT_MAX - 1) {
        ret = E_NOT_OK;
    } else {
        *tris_registers[port] = direction;
    }
    return ret;


}

Std_ReturnType gpio_port_get_direction_status(port_index_t port, direction_t *dic_status) {
    Std_ReturnType ret = E_OK;
    if (NULL == dic_status || port > PORT_MAX - 1) {
        ret = E_NOT_OK;
    } else {
        *(dic_status) = *tris_registers[port];
    }

    return ret;
}

Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic) {
    Std_ReturnType ret = E_OK;
    if (port > PORT_MAX - 1) {
        ret = E_NOT_OK;
    } else {
        *lat_registers[port] = logic;
    }
    return ret;
}

Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic_) {
    Std_ReturnType ret = E_OK;
    if (NULL == logic_ || port > PORT_MAX - 1) {
        ret = E_NOT_OK;
    } else {
        *logic_ = *lat_registers[port];
    }

    return ret;
}

Std_ReturnType gpio_port_toggle_logic(port_index_t port) {
    Std_ReturnType ret = E_OK;
    if (port > PORT_MAX - 1) {
        ret = E_NOT_OK;
    } else {
        *lat_registers[port] ^= PORT_MASK;
    }

    return ret;
}


#endif 