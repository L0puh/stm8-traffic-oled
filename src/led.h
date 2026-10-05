#ifndef LED_H
#define LED_H


// PINS:
#define LED_RED     (1 << 3)            // PC3
#define LED_YEL     (1 << 4)            // PC4
#define LED_GRN     (1 << 5)            // PC5
#define LED_MASK    (LED_RED | LED_YEL | LED_GRN)

#include "stm8_regs.h"

static inline void led_on(uint8_t led)
{
   PC_ODR = (PC_ODR & ~LED_MASK) | led;
}

static inline void led_init(void)
{
   PC_ODR &= ~LED_MASK;
   PC_DDR |= LED_MASK;
   PC_CR1 |= LED_MASK;
   PC_CR2 &= ~LED_MASK;

}

#endif 
