/* 
 * File:   mcal_external_interrupt.h
 * Author: xcite
 *
 * Created on February 1, 2024, 8:26 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define MCAL_EXTERNAL_INTERRUPT_H

/*---------------- INCLUDES -------------------*/
#include "mcal_interrupt_cfg.h"

/*---------------- MACROS --------------------*/
typedef void (*Interrupt_Handler)(void);

/*-------------- EXTERNAL INTERRUPT MACROS --------------*/
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

// Macros for external interrupt 0
#define EXT_INT0_Interrupt_Disable()         (INTCONbits.INT0IE = 0)  // Disable external interrupt 0
#define EXT_INT0_Interrupt_Enable()          (INTCONbits.INT0IE = 1)  // Enable external interrupt 0
#define EXT_INT0_Interrupt_Flag_Clear()      (INTCONbits.INT0IF = 0)  // Clear external interrupt 0 flag
#define EXT_INT0_Interrupt_Flag_Set()        (INTCONbits.INT0IF = 1)  // Set external interrupt 0 flag
#define EXT_INT0_Interrupt_Rising_Edge_Set() (INTCON2bits.INTEDG0 = 1)  // Set external interrupt 0 for rising edge
#define EXT_INT0_Interrupt_Falling_Edge_Set() (INTCON2bits.INTEDG0 = 0)  // Set external interrupt 0 for falling edge

// Macros for external interrupt 1
#define EXT_INT1_Interrupt_Disable()         (INTCON3bits.INT1IE = 0)  // Disable external interrupt 1
#define EXT_INT1_Interrupt_Enable()          (INTCON3bits.INT1IE = 1)  // Enable external interrupt 1
#define EXT_INT1_Interrupt_Flag_Clear()      (INTCON3bits.INT1IF = 0)  // Clear external interrupt 1 flag
#define EXT_INT1_Interrupt_Flag_Set()        (INTCON3bits.INT1IF = 1)  // Set external interrupt 1 flag
#define EXT_INT1_Interrupt_Rising_Edge_Set() (INTCON2bits.INTEDG1 = 1)  // Set external interrupt 1 for rising edge
#define EXT_INT1_Interrupt_Falling_Edge_Set() (INTCON2bits.INTEDG1 = 0)  // Set external interrupt 1 for falling edge

// Macros for external interrupt 2
#define EXT_INT2_Interrupt_Disable()         (INTCON3bits.INT2IE = 0)  // Disable external interrupt 2
#define EXT_INT2_Interrupt_Enable()          (INTCON3bits.INT2IE = 1)  // Enable external interrupt 2
#define EXT_INT2_Interrupt_Flag_Clear()      (INTCON3bits.INT2IF = 0)  // Clear external interrupt 2 flag
#define EXT_INT2_Interrupt_Flag_Set()        (INTCON3bits.INT2IF = 1)  // Set external interrupt 2 flag
#define EXT_INT2_Interrupt_Rising_Edge_Set() (INTCON2bits.INTEDG2 = 1)  // Set external interrupt 2 for rising edge
#define EXT_INT2_Interrupt_Falling_Edge_Set() (INTCON2bits.INTEDG2 = 0)  // Set external interrupt 2 for falling edge

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE   
// Priority setting macros
#define EXT_INT1_High_Priority_Set() (INTCON3bits.INT1IP = 1)  // Set external interrupt 1 to high priority
#define EXT_INT1_Low_Priority_Set()  (INTCON3bits.INT1IP = 0)  // Set external interrupt 1 to low priority
#define EXT_INT2_High_Priority_Set() (INTCON3bits.INT2IP = 1)  // Set external interrupt 2 to high priority
#define EXT_INT2_Low_Priority_Set()  (INTCON3bits.INT2IP = 0)  // Set external interrupt 2 to low priority
#endif

#endif

/*-------------- EXTERNAL INTERRUPT OnChange MACROS --------------*/
#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EXT_RBx_Interrupt_Disable()     (INTCONbits.RBIE = 0)
#define EXT_RBx_Interrupt_Enable()      (INTCONbits.RBIE = 1)
#define EXT_RBx_Interrupt_Flag_Clear()  (INTCONbits.RBIF = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE   
#define EXT_RBx_Priority_High() (INTCON2bits.RBIP = 1)
#define EXT_RBx_Priority_Low()  (INTCON2bits.RBIP = 0)
#endif

#endif

/*------------ DATA_TYPES --------------------*/


typedef enum {
    INTERRUPT_RISING_EDGE = 0,
    INTERRUPT_FALLING_EDGE,
} interrupt_INTx_edge;

typedef enum {
    INTERRUPT_EXTERNAL_INT0 = 0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2
} interrupt_INTx_src;

typedef struct {
    void (*External_CallBack)(void);
    interrupt_INTx_edge Edge;
    interrupt_INTx_src Source;
    interrupt_priority_cfg Priority;
    pin_config_t mcu_pin;

} interrupt_INTx_t;

typedef struct {
    void (*External_CallBack_High)(void);
    void (*External_CallBack_Low)(void);
    interrupt_priority_cfg Priority;
    pin_config_t mcu_pin;

}  interrupt_RBx_t;

/*------------ FUNCTIONS DECLARATION ----------*/
/**
 * @brief Initializes external interrupt INTx.
 * @param obj: Pointer to the interrupt_INTx_t object.
 * @return Std_ReturnType: Status of the initialization.
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *obj);

/**
 * @brief Deinitializes external interrupt INTx.
 * @param obj: Pointer to the interrupt_INTx_t object.
 * @return Std_ReturnType: Status of the deinitialization.
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *obj);

/**
 * @brief Initializes external interrupt RBx.
 * @param obj: Pointer to the interrupt_RBx_t object.
 * @return Std_ReturnType: Status of the initialization.
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *obj);


#endif /* MCAL_EXTERNAL_INTERRUPT_H */
