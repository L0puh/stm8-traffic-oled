#ifndef ADC_H
#define ADC_H

#include "stm8_regs.h"
#include "utils.h"

static uint16_t adc_read_ch(uint8_t ch)
{
    uint8_t h, l, n;

    for (n = 0; n < 2; n++) {
        ADC_CSR = ch & 0x0F;
        ADC_CR1 |= 0x01;
        while (!(ADC_CSR & 0x80));
        h = ADC_DRH;
        l = ADC_DRL;
        ADC_CSR &= ~0x80;
    }
    return ((uint16_t)h << 2) | (l & 0x03);
}


static void adc_init(void)
{

    PD_DDR &= ~((1 << 2) | (1 << 3) | (1 << 6));
    PD_CR1 &= ~((1 << 2) | (1 << 3) | (1 << 6));
    PD_CR2 &= ~((1 << 2) | (1 << 3) | (1 << 6));

    ADC_CR1 = 0x00;
    ADC_CR2 = 0x00;
    ADC_CR3 = 0x00;
    ADC_CSR = 0x06;

    ADC_CR1 = 0x01;
    delay_ms(1);
    ADC_CR1 |= 0x01;
}

static uint16_t adc_read(void)
{
    return adc_read_ch(6);
}



#endif 
