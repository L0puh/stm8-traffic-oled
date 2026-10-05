
#include "timer.h"
#include "stm8_regs.h"

static volatile uint32_t ms_counter = 0;

void tim4_isr(void) __interrupt(23)
{
    TIM4_SR &= ~0x01;
    ms_counter++;
}

void timer_init(void)
{
    TIM4_PSCR = 0x07;    // prescaler 128 -> 125 kHz
    TIM4_ARR  = 124;     // 125 kHz / 125 = 1 kHz -> 1 ms
    TIM4_CNTR = 0;
    TIM4_EGR  = 0x01;    // UG bit: load PSCR and ARR
    TIM4_SR   = 0x00;    // clear flags
    TIM4_IER  = 0x01;    // enable update interrupt
    TIM4_CR1  = 0x01;    // enable timer
    __asm__("rim");
}

uint32_t millis(void)
{
    uint32_t m;
    __asm__("sim");
    m = ms_counter;
    __asm__("rim");
    return m;
}
