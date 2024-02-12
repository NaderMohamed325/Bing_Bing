/* 
 * File:   mcal_interrupt_manager.c
 * Author: xcite
 *
 * Created on February 1, 2024, 8:28 PM
 */

#include "mcal_interrupt_manager.h"
static volatile uint8 RB4_f = 1, RB5_f = 1, RB6_f = 1, RB7_f = 1;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

// High-priority interrupt service routine
void __interrupt() Interrupt_Manager_High(void) {
    // Check and call INT0 ISR if enabled and flag is set
    if ((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == INTERRUPT_OCCUR)) {
        INT0_ISR();
    }
    // Check and call INT1 ISR if enabled and flag is set
    if ((INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF == INTERRUPT_OCCUR)) {
        INT1_ISR();
    }
}

// Low-priority interrupt service routine
void __interrupt(low_priority) Interrupt_Manager_Low(void) {
    // Check and call INT2 ISR if enabled and flag is set
    if ((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == INTERRUPT_OCCUR)) {
        INT2_ISR();
    }
}

#else

// Single interrupt service routine for all interrupts in non-priority mode
void __interrupt() Interrupt_Manager_High(void) {
    // Check and call INT0 ISR if enabled and flag is set
    if ((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == INTERRUPT_OCCUR)) {
        INT0_ISR();
    }
    // Check and call INT1 ISR if enabled and flag is set
    if ((INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF == INTERRUPT_OCCUR)) {
        INT1_ISR();
    }
    // Check and call INT2 ISR if enabled and flag is set
    if ((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == INTERRUPT_OCCUR)) {
        INT2_ISR();
    }

    // Check and call RBx ISRs for pin change interrupts
    if ((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR)) {
        // Check each RBx pin individually and call the corresponding ISR
        // Update the corresponding flag to track the pin state
        // RB4
        if ((PORTBbits.RB4 == GPIO_HIGH) && RB4_f == 1) {
            RB4_f = 0;
            RB4_ISR(0);
        }
        if ((PORTBbits.RB4 == GPIO_LOW) && RB4_f == 0) {
            RB4_f = 1;
            RB4_ISR(1);
        }
        // RB5
        if ((PORTBbits.RB5 == GPIO_HIGH) && RB5_f == 1) {
            RB5_f = 0;
            RB5_ISR(0);
        }
        if ((PORTBbits.RB5 == GPIO_LOW) && RB5_f == 0) {
            RB5_f = 1;
            RB5_ISR(1);
        }
        // RB6
        if ((PORTBbits.RB6 == GPIO_HIGH) && RB6_f == 1) {
            RB6_f = 0;
            RB6_ISR(0);
        }
        if ((PORTBbits.RB6 == GPIO_LOW) && RB6_f == 0) {
            RB6_f = 1;
            RB6_ISR(1);
        }
        // RB7
        if ((PORTBbits.RB7 == GPIO_HIGH) && RB7_f == 1) {
            RB7_f = 0;
            RB7_ISR(0);
        }
        if ((PORTBbits.RB7 == GPIO_LOW) && RB7_f == 0) {
            RB7_f = 1;
            RB7_ISR(1);
        }
    }
}

#endif
