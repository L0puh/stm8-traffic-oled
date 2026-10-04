#ifndef I2C_H
#define I2C_H

#include "stm8_regs.h"
#include <stdint.h>

#define SCL_BIT     (1 << 4)            // PB4
#define SDA_BIT     (1 << 5)            // PB5

#define SCL_LOW()   (PB_DDR |=  SCL_BIT)   // SCL = 0: DDR=1, drive low
#define SCL_HIGH()  (PB_DDR &= ~SCL_BIT)   // SCL = 1: DDR=0, release
#define SDA_LOW()   (PB_DDR |=  SDA_BIT)   // SDA = 0: DDR=1, drive low
#define SDA_HIGH()  (PB_DDR &= ~SDA_BIT)   // SDA = 1: DDR=0, release


void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_write(uint8_t byte);

#endif 
