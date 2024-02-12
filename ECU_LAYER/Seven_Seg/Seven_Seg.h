/**
 * @file Seven_Seg.h
 * @brief Header file for Seven-Segment Display module.
 * @author xcite
 * @date December 24, 2023, 10:38 PM
 */

#ifndef SEVEN_SEG_H
#define SEVEN_SEG_H

/* Includes */
#include "Seven_Seg_cfg.h"
#include "../../MCAL_LAYER/GPIO/hal_gpio.h"

/* Macros */

/* Data Types */
typedef enum {
    SEVEN_SEG_TYPE_ANODE = 0,
    SEVEN_SEG_TYPE_CATHOD = 1,
} Seven_seg_type_t;

typedef enum {
    SEGMENT_PIN0 = 0,
    SEGMENT_PIN1,
    SEGMENT_PIN2,
    SEGMENT_PIN3
} SEG_PIN;

typedef struct {
    pin_config_t segment_pins[4];
    Seven_seg_type_t Seg_Type;
} Seven_Segment_t;

/* Function Declarations */
/**
 * @brief Initializes the Seven-Segment display.
 * @param _Seven_Seg Pointer to a Seven_Segment_t structure.
 * @return Standard return type indicating success or failure.
 */
Std_ReturnType Seven_Segm_initailize(Seven_Segment_t * _Seven_Seg);

/**
 * @brief Displays a number on the Seven-Segment display.
 * @param _Seven_Seg Pointer to a Seven_Segment_t structure.
 * @return Standard return type indicating success or failure.
 */
Std_ReturnType Seven_Segm_Display_Number(Seven_Segment_t * _Seven_Seg,uint8 number);

#endif /* SEVEN_SEG_H */
