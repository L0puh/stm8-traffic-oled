#ifndef STM8_REGS_H
#define STM8_REGS_H

#include <stdint.h>

#define REG(a)  (*(volatile uint8_t *)(a))

// port A
#define PA_ODR  REG(0x5000)
#define PA_IDR  REG(0x5001)
#define PA_DDR  REG(0x5002)
#define PA_CR1  REG(0x5003)
#define PA_CR2  REG(0x5004)

// port B
#define PB_ODR  REG(0x5005)
#define PB_IDR  REG(0x5006)
#define PB_DDR  REG(0x5007)
#define PB_CR1  REG(0x5008)
#define PB_CR2  REG(0x5009)

// port C
#define PC_ODR  REG(0x500A)
#define PC_IDR  REG(0x500B)
#define PC_DDR  REG(0x500C)
#define PC_CR1  REG(0x500D)
#define PC_CR2  REG(0x500E)

// port D
#define PD_ODR  REG(0x500F)
#define PD_IDR  REG(0x5010)
#define PD_DDR  REG(0x5011)
#define PD_CR1  REG(0x5012)
#define PD_CR2  REG(0x5013)

#define CLK_CKDIVR  REG(0x50C6)
#define TIM4_CR1   REG(0x5340)
#define TIM4_IER   REG(0x5343)
#define TIM4_SR    REG(0x5344)
#define TIM4_EGR   REG(0x5345)
#define TIM4_CNTR  REG(0x5346)
#define TIM4_PSCR  REG(0x5347)
#define TIM4_ARR   REG(0x5348)

#define ADC_CSR     REG(0x5400)
#define ADC_CR1     REG(0x5401)
#define ADC_CR2     REG(0x5402)
#define ADC_CR3     REG(0x5403)
#define ADC_DRH     REG(0x5404)
#define ADC_DRL     REG(0x5405)
#endif
