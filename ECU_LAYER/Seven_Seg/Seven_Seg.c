/**
 * @file Seven_Seg.c
 * @brief Implementation of Seven-Segment Display functions.
 * @author xcite
 * @date December 24, 2023, 10:38 PM
 */

#include "Seven_Seg.h"

/**
 * @brief Initializes the Seven-Segment display.
 *
 * This function initializes the GPIO pins associated with the segments of the Seven-Segment display.
 *
 * @param _Seven_Seg Pointer to a Seven_Segment_t structure.
 * 
 * @return 
 * - ::E_OK: Initialization successful.
 * - ::E_NOT_OK: Invalid pointer (_Seven_Seg is NULL).
 */
Std_ReturnType Seven_Segm_initailize(Seven_Segment_t * _Seven_Seg) {
    Std_ReturnType ret = E_OK;

    if (NULL == _Seven_Seg) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_initialize(&_Seven_Seg->segment_pins[SEGMENT_PIN0]);
        ret = gpio_pin_initialize(&_Seven_Seg->segment_pins[SEGMENT_PIN1]);
        ret = gpio_pin_initialize(&_Seven_Seg->segment_pins[SEGMENT_PIN2]);
        ret = gpio_pin_initialize(&_Seven_Seg->segment_pins[SEGMENT_PIN3]);
    }

    return ret;
}

/**
 * @brief Displays a decimal number on the Seven-Segment display.
 *
 * This function takes a decimal number (0-9) and displays it on the Seven-Segment display using GPIO logic.
 * Each segment corresponds to a specific digit of the provided number.
 *
 * @param _Seven_Seg Pointer to a Seven_Segment_t structure.
 * @param number Decimal number to be displayed (0-9).
 * 
 * @return 
 * - ::E_OK: Display successful.
 * - ::E_NOT_OK: 
 *   - Invalid pointer (_Seven_Seg is NULL).
 *   - Invalid number (not in the range 0-9).
 */
Std_ReturnType Seven_Segm_Display_Number(Seven_Segment_t * _Seven_Seg, uint8 number) {
    Std_ReturnType ret = E_OK;

    if (NULL == _Seven_Seg || (number < 0 || number > 9)) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_write_logic(&_Seven_Seg->segment_pins[SEGMENT_PIN0], (number >> 0) & BIT_MASK);
        ret = gpio_pin_write_logic(&_Seven_Seg->segment_pins[SEGMENT_PIN1], (number >> 1) & BIT_MASK);
        ret = gpio_pin_write_logic(&_Seven_Seg->segment_pins[SEGMENT_PIN2], (number >> 2) & BIT_MASK);
        ret = gpio_pin_write_logic(&_Seven_Seg->segment_pins[SEGMENT_PIN3], (number >> 3) & BIT_MASK);
    }

    return ret;
}
