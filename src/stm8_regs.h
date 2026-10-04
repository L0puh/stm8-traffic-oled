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

#endif
