/*
 * File:   ecu_chr_lcd.c
 * Author: xcite
 *
 * Created on January 16, 2024, 3:01 PM
 */

#include "ecu_chr_lcd.h"

/**
 * @brief   Sends a 4-bit command to the LCD.
 * @param   Lcd: Pointer to the lcd_4bit_mode structure.
 * @param   data_command: The 4-bit command to be sent to the LCD.
 * @return  Returns E_OK if the command is sent successfully, otherwise E_NOT_OK.
 */
Std_ReturnType static lcd_4bits_command(lcd_4bit_mode const *Lcd, uint8 data_command);

/**
 * @brief   Sends an enable pulse to the LCD in 4-bit mode.
 * @param   Lcd: Pointer to the lcd_4bit_mode structure.
 * @return  Returns E_OK if the enable pulse is sent successfully, otherwise E_NOT_OK.
 */
Std_ReturnType static lcd_4bits_send_enable(lcd_4bit_mode const *Lcd);

/**
 * @brief   Sends an enable pulse to the LCD in 8-bit mode.
 * @param   Lcd: Pointer to the lcd_8bit_mode structure.
 * @return  Returns E_OK if the enable pulse is sent successfully, otherwise E_NOT_OK.
 */
Std_ReturnType static lcd_8bits_send_enable(lcd_8bit_mode const *Lcd);

/**
 * @brief   Sets the cursor position for a 4-bit LCD.
 * @param   Lcd: Pointer to the lcd_4bit_mode structure.
 * @param   row: The row number (starting from 0).
 * @param   column: The column number (starting from 0).
 * @return  Returns E_OK if the cursor position is set successfully, otherwise E_NOT_OK.
 */
Std_ReturnType static lcd_4bit_set_cursor(lcd_4bit_mode const *Lcd, uint8 row, uint8 column);

/**
 * @brief   Sets the cursor position for an 8-bit LCD.
 * @param   Lcd: Pointer to the lcd_8bit_mode structure.
 * @param   row: The row number (starting from 0).
 * @param   column: The column number (starting from 0).
 * @return  Returns E_OK if the cursor position is set successfully, otherwise E_NOT_OK.
 */
Std_ReturnType static lcd_8bit_set_cursor(lcd_8bit_mode const *Lcd, uint8 row, uint8 column);

/**
 * @brief   Initializes the LCD in 4-bit mode.
 * @details Initializes the control pins and data pins of the LCD in 4-bit mode.
 * @param   Lcd: Pointer to the lcd_4bit_mode structure.
 * @return  Returns E_OK if initialization is successful, otherwise E_NOT_OK.
 */
Std_ReturnType lcd_4bit_initailize(lcd_4bit_mode const *Lcd) {
    Std_ReturnType ret = E_OK;
    if (NULL == Lcd) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_initialize(&(Lcd->lcd_en));
        ret = gpio_pin_initialize(&(Lcd->lcd_rs));
        for (uint8 i = 0; i < 4; i++) {
            ret = gpio_pin_initialize(&(Lcd->lcd_data[i]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(Lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(Lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(Lcd, _LCD_8BIT_MODE_2_LINE);

        ret = lcd_4bit_send_command(Lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_command(Lcd, _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(Lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_4bit_send_command(Lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_4bit_send_command(Lcd, _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(Lcd, 0x80);
    }
    return ret;
}

/**
 * @brief   Sends a command to the LCD in 4-bit mode.
 * @param   Lcd: Pointer to the lcd_4bit_mode structure.
 * @param   command: The command to be sent to the LCD.
 * @return  Returns E_OK if the command is sent successfully, otherwise E_NOT_OK.
 */
Std_ReturnType lcd_4bit_send_command(lcd_4bit_mode const *Lcd, uint8 command) {
    Std_ReturnType ret = E_OK;
    if (NULL == Lcd) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_write_logic(&(Lcd->lcd_rs), GPIO_LOW);
        ret = lcd_4bits_command(Lcd, command >> 4);
        ret = lcd_4bits_send_enable(Lcd);
        ret = lcd_4bits_command(Lcd, command);
        ret = lcd_4bits_send_enable(Lcd);
    }
    return ret;
}

/**
 * @brief   Sends character data to the LCD in 4-bit mode.
 * @param   Lcd: Pointer to the lcd_4bit_mode structure.
 * @param   data: The character data to be sent to the LCD.
 * @return  Returns E_OK if the data is sent successfully, otherwise E_NOT_OK.
 */
Std_ReturnType lcd_4bit_send_char_data(lcd_4bit_mode const *Lcd, uint8 data) {
    Std_ReturnType ret = E_OK;
    if (NULL == Lcd) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_write_logic(&(Lcd->lcd_rs), GPIO_HIGH);
        ret = lcd_4bits_command(Lcd, data >> 4);
        ret = lcd_4bits_send_enable(Lcd);
        ret = lcd_4bits_command(Lcd, data);
        ret = lcd_4bits_send_enable(Lcd);
    }
    return ret;
}

/**
 * @brief   Sends character data to the specified position on the LCD in 4-bit mode.
 * @param   Lcd: Pointer to the lcd_4bit_mode structure.
 * @param   row: The row number (starting from 0).
 * @param   column: The column number (starting from 0).
 * @param   data: The character data to be sent to the LCD.
 * @return  Returns E_OK if the data is sent successfully, otherwise E_NOT_OK.
 */
Std_ReturnType lcd_4bit_send_char_data_pos(lcd_4bit_mode const *Lcd, uint8 row, uint8 column, uint8 data) {
    Std_ReturnType ret = E_OK;
    if (NULL == Lcd) {
        ret = E_NOT_OK;
    } else {
        ret = lcd_4bit_set_cursor(Lcd, row, column);
        ret = lcd_4bit_send_char_data(Lcd, data);
    }
    return ret;
}

/**
 * @brief   Sends a string to the LCD in 4-bit mode.
 * @param   Lcd: Pointer to the lcd_4bit_mode structure.
 * @param   str: Pointer to the string to be sent to the LCD.
 * @return  Returns E_OK if the string is sent successfully, otherwise E_NOT_OK.
 */
Std_ReturnType lcd_4bit_send_string(lcd_4bit_mode const *Lcd, uint8 *str) {
    Std_ReturnType ret = E_OK;
    if (NULL == Lcd) {
        ret = E_NOT_OK;
    } else {
        while (*str) {
            ret = lcd_4bit_send_char_data(Lcd, *str++);
        }
    }
    return ret;
}

/**
 * @brief   Sends a string to the specified position on the LCD in 4-bit mode.
 * @param   Lcd: Pointer to the lcd_4bit_mode structure.
 * @param   row: The row number (starting from 0).
 * @param   column: The column number (starting from 0).
 * @param   str: Pointer to the string to be sent to the LCD.
 * @return  Returns E_OK if the string is sent successfully, otherwise E_NOT_OK.
 */
Std_ReturnType lcd_4bit_send_string_pos(lcd_4bit_mode const *Lcd, uint8 row, uint8 column, uint8 *str) {
    Std_ReturnType ret = E_OK;
    if (NULL == Lcd) {
        ret = E_NOT_OK;
    } else {
        ret = lcd_4bit_set_cursor(Lcd, row, column);
        ret = lcd_4bit_send_string(Lcd, str);
    }
    return ret;
}

/**
 * @brief   Sends a custom character to the specified position on the LCD in 4-bit mode.
 * @param   Lcd: Pointer to the lcd_4bit_mode structure.
 * @param   row: The row number (starting from 0).
 * @param   column: The column number (starting from 0).
 * @param   _char: Array containing the custom character data.
 * @param   mem_pos: Memory position for the custom character (0 to 7).
 * @return  Returns E_OK if the custom character is sent successfully, otherwise E_NOT_OK.
 */
Std_ReturnType lcd_4bit_send_custom_ch(lcd_4bit_mode const *Lcd, uint8 row, uint8 column, uint8 const _char[], uint8 mem_pos) {
    Std_ReturnType ret = E_OK;
    if (NULL == Lcd) {
        ret = E_NOT_OK;
    } else {
        ret = lcd_4bit_send_command(Lcd, _LCD_CGRAM_START + 8 * mem_pos);
        for (uint8 i = 0; i < 8; i++) {
            ret = lcd_4bit_send_char_data(Lcd, _char[i]);
        }
        ret = lcd_4bit_send_char_data_pos(Lcd, row, column, mem_pos);


    }
    return ret;
}

/**
 * @brief   Initializes the LCD in 8-bit mode.
 * @details Initializes the control pins and data pins of the LCD in 8-bit mode.
 * @param   Lcd: Pointer to the lcd_8bit_mode structure.
 * @return  Returns E_OK if initialization is successful, otherwise E_NOT_OK.
 */
Std_ReturnType lcd_8bit_initailize(lcd_8bit_mode const *Lcd) {
    Std_ReturnType ret = E_OK;
    if (NULL == Lcd) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_initialize(&(Lcd->lcd_en));
        ret = gpio_pin_initialize(&(Lcd->lcd_rs));
        for (uint8 i = 0; i < 8; i++) {
            ret = gpio_pin_initialize(&(Lcd->lcd_data[i]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(Lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(Lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(Lcd, _LCD_8BIT_MODE_2_LINE);

        ret = lcd_8bit_send_command(Lcd, _LCD_CLEAR);
        ret = lcd_8bit_send_command(Lcd, _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(Lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_8bit_send_command(Lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_8bit_send_command(Lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(Lcd, 0x80);
    }
    return ret;
}

/**
 * @brief   Sends a command to the LCD in 8-bit mode.
 * @param   Lcd: Pointer to the lcd_8bit_mode structure.
 * @param   command: The command to be sent to the LCD.
 * @return  Returns E_OK if the command is sent successfully, otherwise E_NOT_OK.
 */
Std_ReturnType lcd_8bit_send_command(lcd_8bit_mode const *Lcd, uint8 command) {
    Std_ReturnType ret = E_OK;
    if (NULL == Lcd) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_write_logic(&(Lcd->lcd_rs), GPIO_LOW);
        for (uint8 i = 0; i < 8; i++) {
            ret = gpio_pin_write_logic(&(Lcd->lcd_data[i]), ((command) >> i) & BIT_MASK);
        }
        ret = lcd_8bits_send_enable(Lcd);
    }
    return ret;
}

/**
 * @brief   Sends character data to the LCD in 8-bit mode.
 * @param   Lcd: Pointer to the lcd_8bit_mode structure.
 * @param   data: The character data to be sent to the LCD.
 * @return  Returns E_OK if the data is sent successfully, otherwise E_NOT_OK.
 */
Std_ReturnType lcd_8bit_send_char_data(lcd_8bit_mode const *Lcd, uint8 data) {
    Std_ReturnType ret = E_OK;
    if (NULL == Lcd) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_write_logic(&(Lcd->lcd_rs), GPIO_HIGH);
        for (uint8 i = 0; i < 8; i++) {
            ret = gpio_pin_write_logic(&(Lcd->lcd_data[i]), ((data) >> i) & BIT_MASK);
        }
        ret = lcd_8bits_send_enable(Lcd);
    }
    return ret;
}

/**
 * @brief   Sends character data to the specified position on the LCD in 8-bit mode.
 * @param   Lcd: Pointer to the lcd_8bit_mode structure.
 * @param   row: The row number (starting from 0).
 * @param   column: The column number (starting from 0).
 * @param   data: The character data to be sent to the LCD.
 * @return  Returns E_OK if the data is sent successfully, otherwise E_NOT_OK.
 */
Std_ReturnType lcd_8bit_send_char_data_pos(lcd_8bit_mode const *Lcd, uint8 row, uint8 column, uint8 data) {
    Std_ReturnType ret = E_OK;
    if (NULL == Lcd) {
        ret = E_NOT_OK;
    } else {
        ret = lcd_8bit_set_cursor(Lcd, row, column);
        ret = lcd_8bit_send_char_data(Lcd, data);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_string(lcd_8bit_mode const *Lcd, uint8 *str) {
    Std_ReturnType ret = E_OK;
    if (NULL == Lcd) {
        ret = E_NOT_OK;
    } else {
        while (*str) {
            ret = lcd_8bit_send_char_data(Lcd, *str++);
        }
    }

    return ret;
}

Std_ReturnType lcd_8bit_send_string_pos(lcd_8bit_mode const *Lcd, uint8 row, uint8 column, uint8 *str) {
    Std_ReturnType ret = E_OK;
    if (NULL == Lcd) {
        ret = E_NOT_OK;
    } else {
        ret = lcd_8bit_set_cursor(Lcd, row, column);
        ret = lcd_8bit_send_string(Lcd, str);
    }

    return ret;
}

Std_ReturnType lcd_8bit_send_custom_ch(lcd_8bit_mode const *Lcd, uint8 row, uint8 column, uint8 const _char[], uint8 mem_pos) {
    Std_ReturnType ret = E_OK;
    if (NULL == Lcd) {
        ret = E_NOT_OK;
    } else {
        ret = lcd_8bit_send_command(Lcd, _LCD_CGRAM_START + 8 * mem_pos);
        for (uint8 i = 0; i < 8; i++) {
            ret = lcd_8bit_send_char_data(Lcd, _char[i]);
        }
        ret = lcd_8bit_send_char_data_pos(Lcd, row, column, mem_pos);



    }

    return ret;
}

Std_ReturnType static lcd_8bits_send_enable(lcd_8bit_mode const *Lcd) {
    Std_ReturnType ret = E_OK;
    if (NULL == Lcd) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_write_logic(&(Lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(Lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

Std_ReturnType static lcd_8bit_set_cursor(lcd_8bit_mode const *Lcd, uint8 row, uint8 column) {
    Std_ReturnType ret = E_OK;
    if (NULL == Lcd) {
        ret = E_NOT_OK;
    } else {
        column--;
        switch (row) {
            case ROW1:
                ret = lcd_8bit_send_command(Lcd, (0X80 + column));
                break;
            case ROW2:
                ret = lcd_8bit_send_command(Lcd, (0x0c + column));
                break;
            case ROW3:
                ret = lcd_8bit_send_command(Lcd, (0X94 + column));
                break;
            case ROW4:
                ret = lcd_8bit_send_command(Lcd, (0XD4 + column));
                break;
            default:;
        }
    }
    return ret;
}

Std_ReturnType convert_byte_to_string(uint8 value, char *str) {
    Std_ReturnType ret = E_OK;
    if (NULL == str) {
        ret = E_NOT_OK;
    } else {
        memset(str, '0', 4);
        sprintf(str, "%i", value);
    }

    return ret;
}

Std_ReturnType convert_short_to_string(uint16 value, char *str) {
    Std_ReturnType ret = E_OK;
    if (NULL == str) {
        ret = E_NOT_OK;
    } else {
        memset(str, '\0', 6);
        sprintf(str, "%i", value);
    }

    return ret;
}

Std_ReturnType convert_int_to_string(uint32 value, char *str) {
    Std_ReturnType ret = E_OK;
    if (NULL == str) {
        ret = E_NOT_OK;
    } else {
        memset(str, '\0', 11);
        sprintf(str, "%i", value);
    }

    return ret;
}

Std_ReturnType static lcd_4bits_send_enable(lcd_4bit_mode const *Lcd) {
    Std_ReturnType ret = E_OK;
    if (NULL == Lcd) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_write_logic(&(Lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(Lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

Std_ReturnType static lcd_4bits_command(lcd_4bit_mode const *Lcd, uint8 data_command) {
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(Lcd->lcd_data[0]), (data_command >> 0) & (uint8) 0x01);
    ret = gpio_pin_write_logic(&(Lcd->lcd_data[1]), (data_command >> 1) & (uint8) 0x01);
    ret = gpio_pin_write_logic(&(Lcd->lcd_data[2]), (data_command >> 2) & (uint8) 0x01);
    ret = gpio_pin_write_logic(&(Lcd->lcd_data[3]), (data_command >> 3) & (uint8) 0x01);
    return ret;
}

Std_ReturnType static lcd_4bit_set_cursor(lcd_4bit_mode const *Lcd, uint8 row, uint8 column) {
    Std_ReturnType ret = E_OK;
    column--;
    switch (row) {
        case ROW1: ret = lcd_4bit_send_command(Lcd, (0x80 + column));
            break;
        case ROW2: ret = lcd_4bit_send_command(Lcd, (0xc0 + column));
            break;
        case ROW3: ret = lcd_4bit_send_command(Lcd, (0x94 + column));
            break;
        case ROW4: ret = lcd_4bit_send_command(Lcd, (0xd4 + column));
            break;
        default:;
    }
    return ret;
}