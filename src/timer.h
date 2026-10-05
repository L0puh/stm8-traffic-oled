#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void timer_init(void);
uint32_t millis(void);
void tim4_isr(void) __interrupt(23); 

#endif
