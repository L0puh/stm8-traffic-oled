#ifndef UTILS_H
#define UTILS_H

#define DELAY_VALUE  1600 // 16MHz 

#include <stdint.h>

inline void delay_ms(uint16_t ms)
{
   while (ms--){
      for (uint16_t i = 0; i < DELAY_VALUE; i++){
         __asm__("nop");
      }
   }
}


#endif 
