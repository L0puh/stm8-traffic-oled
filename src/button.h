#ifndef BUTTOH_H
#define BUTTOH_H


#include "stm8_regs.h"
#include "utils.h"

#define BTN_BIT  (1 << 4)   // PD4

static void button_init(void)
{
    PD_DDR &= ~BTN_BIT;   // input 
    PD_CR1 |=  BTN_BIT;   // inner pull-up
    PD_CR2 &= ~BTN_BIT;   // non interrupt 
}

static uint8_t button_pressed(void)
{
    return (PD_IDR & BTN_BIT) == 0;   
}

static uint8_t button_debounce(void)
{
    static uint8_t last = 0;
    uint8_t now = button_pressed();

    if (now && !last) {
        delay_ms(50);       
        if (button_pressed()) {
            last = 1;
            return 1;      
        }
    }
    if (!now) last = 0;
    return 0;
}
#endif 
