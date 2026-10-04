#include "i2c.h"
#include <stdint.h>


void i2c_init(void)
{
   /// reset registers 
   PB_ODR &= ~(SCL_BIT | SDA_BIT);
   PB_DDR &= ~(SCL_BIT | SDA_BIT); 
   PB_CR1 &= ~(SCL_BIT | SDA_BIT);
   PB_CR2 &= ~(SCL_BIT | SDA_BIT);
}



// the requirements of start
// SDA from 1 to 0 while SCL = 1
void i2c_start(void)
{
   SDA_HIGH();
   SCL_HIGH();
   SDA_LOW();
   SCL_LOW();
}


// the requirements of stop
// SDA from 0 to 1 while SCL = 1
void i2c_stop(void)
{
   SDA_LOW();
   SCL_HIGH();
   SDA_HIGH();
}


// put bit on SDA
// SCL = 1 -> slave reads bit
// SCL = 0 -> ready to next bit 
void i2c_write(uint8_t byte)
{
   uint8_t i;

   for (i = 0; i < 8; i++)
   {
      if (byte & 0x80) SDA_HIGH(); // check current bit
      else SDA_LOW();

      // SCL: for the slave
      SCL_HIGH();
      SCL_LOW();
      byte <<= 1;
   }

   SDA_HIGH();
   SCL_HIGH();
   SCL_LOW();
}
