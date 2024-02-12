/* 
 * File:   mcal_external_interrupt.c
 * Author: xcite
 *
 * Created on February 1, 2024, 8:26 PM
 */

#include "mcal_external_interrupt.h"

// Static function declarations

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *obj);

static Std_ReturnType INT0_Set_Interrupt_Handler(void (*Interrupt_Handler)(void));
static Std_ReturnType INT1_Set_Interrupt_Handler(void (*Interrupt_Handler)(void));
static Std_ReturnType INT2_Set_Interrupt_Handler(void (*Interrupt_Handler)(void));
static Std_ReturnType Interrupt_Set_Interrupt_Handler(const interrupt_INTx_t *obj);

// Static variables for interrupt handlers
static Interrupt_Handler INT0_Interrupt_Handler = NULL;
static Interrupt_Handler INT1_Interrupt_Handler = NULL;
static Interrupt_Handler INT2_Interrupt_Handler = NULL;

static Interrupt_Handler RB4_Interrupt_Handler_High = NULL;
static Interrupt_Handler RB4_Interrupt_Handler_Low = NULL;
static Interrupt_Handler RB5_Interrupt_Handler_High = NULL;
static Interrupt_Handler RB5_Interrupt_Handler_Low = NULL;
static Interrupt_Handler RB6_Interrupt_Handler_High = NULL;
static Interrupt_Handler RB6_Interrupt_Handler_Low = NULL;
static Interrupt_Handler RB7_Interrupt_Handler_High = NULL;
static Interrupt_Handler RB7_Interrupt_Handler_Low = NULL;

/**
 * @brief Initializes external interrupt INTx.
 *
 * @param obj: Pointer to the interrupt_INTx_t object.
 * @return Std_ReturnType: Status of the initialization.
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == obj) {
        ret = E_NOT_OK;
    } else {
        // Disable the interrupt, set edge, and clear flag
        ret |= Interrupt_INTx_Disable(obj);
        ret |= Interrupt_INTx_Edge_Init(obj);

        // Initialize priority if enabled
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        ret |= Interrupt_INTx_Priority_Init(obj);
#endif

        // Initialize pin and set interrupt handler
        ret |= Interrupt_INTx_Pin_Init(obj);
        ret |= Interrupt_Set_Interrupt_Handler(obj);

        // Enable the interrupt
        ret |= Interrupt_INTx_Enable(obj);
    }
    return ret;
}

/**
 * @brief Deinitializes external interrupt INTx.
 *
 * @param obj: Pointer to the interrupt_INTx_t object.
 * @return Std_ReturnType: Status of the deinitialization.
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == obj) {
        ret = E_NOT_OK;
    } else {
        // Disable the interrupt
        ret = Interrupt_INTx_Disable(obj);
    }
    return ret;
}

/**
 * @brief Initializes external interrupt RBx.
 *
 * @param obj: Pointer to the interrupt_RBx_t object.
 * @return Std_ReturnType: Status of the initialization.
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == obj) {
        ret = E_NOT_OK;
    } else {
        // Disable, clear flag, enable priority if enabled
        EXT_RBx_Interrupt_Disable();
        EXT_RBx_Interrupt_Flag_Clear();

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_Pirority_Level_Enable();
        if (INTERRUPT_LOW_PRIORITY == obj->Priority) {
            INTERRUPT_Global_Interrupt_Low_Enable();
            EXT_RBx_Priority_Low();
        } else if (INTERRUPT_HIGH_PRIORITY == obj->Priority) {
            INTERRUPT_Global_Interrupt_High_Enable();
            EXT_RBx_Priority_High();
        } else {
            // Nothing
        }
#else
        // Enable global and peripheral interrupts
        INTERRUPT_Global_Interrupt_Enable();
        INTERRUPT_Peripheral_Interrupt_Enable();
#endif

        // Initialize GPIO pin direction
        ret = gpio_pin_direction_intialize(&(obj->mcu_pin));

        // Set callbacks based on pin
        switch (obj->mcu_pin.pin) {
            case PIN4:
                RB4_Interrupt_Handler_High = obj->External_CallBack_High;
                RB4_Interrupt_Handler_Low = obj->External_CallBack_Low;
                break;
            case PIN5:
                RB5_Interrupt_Handler_High = obj->External_CallBack_High;
                RB5_Interrupt_Handler_Low = obj->External_CallBack_Low;
                break;
            case PIN6:
                RB6_Interrupt_Handler_High = obj->External_CallBack_High;
                RB6_Interrupt_Handler_Low = obj->External_CallBack_Low;
                break;
            case PIN7:
                RB7_Interrupt_Handler_High = obj->External_CallBack_High;
                RB7_Interrupt_Handler_Low = obj->External_CallBack_Low;
                break;
            default:
                ret = E_NOT_OK;
                break;
        }

        // Enable the interrupt
        EXT_RBx_Interrupt_Enable();
    }
    return ret;
}



// Implementation of static functions

/**
 * @brief Enables external interrupt INTx.
 *
 * @param obj: Pointer to the interrupt_INTx_t object.
 * @return Std_ReturnType: Status of the enabling operation.
 */
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == obj) {
        ret = E_NOT_OK;
    } else {
        switch (obj->Source) {
            case (INTERRUPT_EXTERNAL_INT0):
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_Global_Interrupt_High_Enable();
#else
                INTERRUPT_Global_Interrupt_Enable();
                INTERRUPT_Peripheral_Interrupt_Enable();
#endif
                EXT_INT0_Interrupt_Enable();
                break;
            case (INTERRUPT_EXTERNAL_INT1):
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_Pirority_Level_Enable();
                if (obj->Priority == INTERRUPT_HIGH_PRIORITY)
                    INTERRUPT_Global_Interrupt_High_Enable();
                else
                    INTERRUPT_Global_Interrupt_Low_Enable();
#else
                INTERRUPT_Global_Interrupt_Enable();
                INTERRUPT_Peripheral_Interrupt_Enable();
#endif
                EXT_INT1_Interrupt_Enable();
                break;
            case (INTERRUPT_EXTERNAL_INT2):
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_Pirority_Level_Enable();
                if (obj->Priority == INTERRUPT_HIGH_PRIORITY)
                    INTERRUPT_Global_Interrupt_High_Enable();
                else
                    INTERRUPT_Global_Interrupt_Low_Enable();
#else
                INTERRUPT_Global_Interrupt_Enable();
                INTERRUPT_Peripheral_Interrupt_Enable();
#endif
                EXT_INT2_Interrupt_Enable();
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

/**
 * @brief Disables external interrupt INTx.
 *
 * @param obj: Pointer to the interrupt_INTx_t object.
 * @return Std_ReturnType: Status of the disabling operation.
 */
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == obj) {
        ret = E_NOT_OK;
    } else {
        switch (obj->Source) {
            case (INTERRUPT_EXTERNAL_INT0):
                EXT_INT0_Interrupt_Disable();
                break;
            case (INTERRUPT_EXTERNAL_INT1):
                EXT_INT1_Interrupt_Disable();
                break;
            case (INTERRUPT_EXTERNAL_INT2):
                EXT_INT2_Interrupt_Disable();
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

/**
 * @brief Initializes priority for external interrupt INTx.
 *
 * @param obj: Pointer to the interrupt_INTx_t object.
 * @return Std_ReturnType: Status of the priority initialization.
 */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/**
 * @brief Initializes the priority for external interrupt INTx based on the provided configuration.
 *
 * @param obj: Pointer to the interrupt_INTx_t object.
 * @return Std_ReturnType: Status of the priority initialization.
 */
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *obj) {
    Std_ReturnType ret = E_OK;
    // Check if the input object pointer is valid
    if (NULL == obj) {
        ret = E_NOT_OK;
    } else {
        // Determine the priority level and set it accordingly
        switch (obj->Priority) {
            case INTERRUPT_HIGH_PRIORITY:
                // Check the interrupt source and set the high priority
                if (obj->Source == INTERRUPT_EXTERNAL_INT1) {
                    EXT_INT1_High_Priority_Set();
                } else {
                    EXT_INT2_High_Priority_Set();
                }
                break;
            case INTERRUPT_LOW_PRIORITY:
                // Check the interrupt source and set the low priority
                if (obj->Source == INTERRUPT_EXTERNAL_INT1) {
                    EXT_INT1_Low_Priority_Set();
                } else {
                    EXT_INT2_Low_Priority_Set();
                }
                break;
            default:
                // Invalid priority level, set the return status to E_NOT_OK
                ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif

/**
 * @brief Initializes edge detection for external interrupt INTx.
 *
 * @param obj: Pointer to the interrupt_INTx_t object.
 * @return Std_ReturnType: Status of the edge initialization.
 */
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == obj) {
        ret = E_NOT_OK;
    } else {
        switch (obj->Source) {
            case (INTERRUPT_EXTERNAL_INT0):
                if (obj->Edge == INTERRUPT_FALLING_EDGE) {
                    EXT_INT0_Interrupt_Falling_Edge_Set();
                } else if (obj->Edge == INTERRUPT_RISING_EDGE) {
                    EXT_INT0_Interrupt_Rising_Edge_Set();
                }
                break;
            case (INTERRUPT_EXTERNAL_INT1):
                if (obj->Edge == INTERRUPT_FALLING_EDGE) {
                    EXT_INT1_Interrupt_Falling_Edge_Set();
                } else if (obj->Edge == INTERRUPT_RISING_EDGE) {
                    EXT_INT1_Interrupt_Rising_Edge_Set();
                }
                break;
            case (INTERRUPT_EXTERNAL_INT2):
                if (obj->Edge == INTERRUPT_FALLING_EDGE) {
                    EXT_INT2_Interrupt_Falling_Edge_Set();
                } else if (obj->Edge == INTERRUPT_RISING_EDGE) {
                    EXT_INT2_Interrupt_Rising_Edge_Set();
                }
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

/**
 * @brief Initializes pin configuration for external interrupt INTx.
 *
 * @param obj: Pointer to the interrupt_INTx_t object.
 * @return Std_ReturnType: Status of the pin initialization.
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == obj) {
        ret = E_NOT_OK;
    } else {
        // Initialize GPIO pin
        ret = gpio_pin_initialize(&(obj->mcu_pin));
    }
    return ret;
}

/**
 * @brief Clears the interrupt flag for external interrupt INTx.
 *
 * @param obj: Pointer to the interrupt_INTx_t object.
 * @return Std_ReturnType: Status of the flag clearing operation.
 */
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == obj) {
        ret = E_NOT_OK;
    } else {
        switch (obj->Source) {
            case (INTERRUPT_EXTERNAL_INT0):
                EXT_INT0_Interrupt_Flag_Clear();
                break;
            case (INTERRUPT_EXTERNAL_INT1):
                EXT_INT1_Interrupt_Flag_Clear();
                break;
            case (INTERRUPT_EXTERNAL_INT2):
                EXT_INT2_Interrupt_Flag_Clear();
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

/**
 * @brief Sets the interrupt handler for external interrupt INT0.
 *
 * @param Interrupt_Handler: Pointer to the interrupt handler function.
 * @return Std_ReturnType: Status of the handler setting operation.
 */
static Std_ReturnType INT0_Set_Interrupt_Handler(void(*Interrupt_Handler)(void)) {
    Std_ReturnType ret = E_OK;
    if (NULL == Interrupt_Handler) {
        ret = E_NOT_OK;
    } else {
        // Set INT0 interrupt handler
        INT0_Interrupt_Handler = Interrupt_Handler;
    }
    return ret;
}

/**
 * @brief Sets the interrupt handler for external interrupt INT1.
 *
 * @param Interrupt_Handler: Pointer to the interrupt handler function.
 * @return Std_ReturnType: Status of the handler setting operation.
 */
static Std_ReturnType INT1_Set_Interrupt_Handler(void(*Interrupt_Handler)(void)) {
    Std_ReturnType ret = E_OK;
    if (NULL == Interrupt_Handler) {
        ret = E_NOT_OK;
    } else {
        // Set INT1 interrupt handler
        INT1_Interrupt_Handler = Interrupt_Handler;
    }
    return ret;
}

/**
 * @brief Sets the interrupt handler for external interrupt INT2.
 *
 * @param Interrupt_Handler: Pointer to the interrupt handler function.
 * @return Std_ReturnType: Status of the handler setting operation.
 */
static Std_ReturnType INT2_Set_Interrupt_Handler(void(*Interrupt_Handler)(void)) {
    Std_ReturnType ret = E_OK;
    if (NULL == Interrupt_Handler) {
        ret = E_NOT_OK;
    } else {
        // Set INT2 interrupt handler
        INT2_Interrupt_Handler = Interrupt_Handler;
    }
    return ret;
}

/**
 * @brief Sets the interrupt handler based on the provided object.
 *
 * @param obj: Pointer to the interrupt_INTx_t object.
 * @return Std_ReturnType: Status of the handler setting operation.
 */
static Std_ReturnType Interrupt_Set_Interrupt_Handler(const interrupt_INTx_t *obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == obj) {
        ret = E_NOT_OK;
    } else {
        // Set the interrupt handler based on the interrupt source
        switch (obj->Source) {
            case (INTERRUPT_EXTERNAL_INT0):
                ret = INT0_Set_Interrupt_Handler(obj->External_CallBack);
                break;
            case (INTERRUPT_EXTERNAL_INT1):
                ret = INT1_Set_Interrupt_Handler(obj->External_CallBack);
                break;
            case (INTERRUPT_EXTERNAL_INT2):
                ret = INT2_Set_Interrupt_Handler(obj->External_CallBack);
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

// Interrupt service routines (ISRs)

void INT0_ISR(void) {
    EXT_INT0_Interrupt_Flag_Clear();
    if (INT0_Interrupt_Handler)
        INT0_Interrupt_Handler();
}

void INT1_ISR(void) {
    EXT_INT1_Interrupt_Flag_Clear();
    if (INT1_Interrupt_Handler)
        INT1_Interrupt_Handler();
}

void INT2_ISR(void) {
    EXT_INT2_Interrupt_Flag_Clear();
    if (INT2_Interrupt_Handler)
        INT2_Interrupt_Handler();
}

void RB4_ISR(uint8 source) {
    EXT_RBx_Interrupt_Flag_Clear();

    if (0 == source) {
        if (RB4_Interrupt_Handler_High) {
            RB4_Interrupt_Handler_High();
        }
    } else if (1 == source) {
        if (RB4_Interrupt_Handler_Low) {
            RB4_Interrupt_Handler_Low();
        }
    }
}

void RB5_ISR(uint8 source) {
    EXT_RBx_Interrupt_Flag_Clear();

    if (0 == source) {
        if (RB5_Interrupt_Handler_High) {
            RB5_Interrupt_Handler_High();
        }
    } else if (1 == source) {
        if (RB5_Interrupt_Handler_Low) {
            RB5_Interrupt_Handler_Low();
        }
    }
}

void RB6_ISR(uint8 source) {
    EXT_RBx_Interrupt_Flag_Clear();

    if (0 == source) {
        if (RB6_Interrupt_Handler_High) {
            RB6_Interrupt_Handler_High();
        }
    } else if (1 == source) {
        if (RB6_Interrupt_Handler_Low) {
            RB6_Interrupt_Handler_Low();
        }
    }
}

void RB7_ISR(uint8 source) {
    EXT_RBx_Interrupt_Flag_Clear();

    if (0 == source) {
        if (RB7_Interrupt_Handler_High) {
            RB7_Interrupt_Handler_High();
        }
    } else if (1 == source) {
        if (RB7_Interrupt_Handler_Low) {
            RB7_Interrupt_Handler_Low();
        }
    }
}
