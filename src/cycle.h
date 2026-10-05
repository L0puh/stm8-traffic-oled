#ifndef CYCLE_H
#define CYCLE_H

#include "led.h"
#include "oled.h"
#include "utils.h"


static void run_cycle(uint32_t cycle)
{

   uint8_t i = 0;
   const uint8_t leds[3] = {LED_RED, LED_YEL, LED_GRN};
   const char* names[3] = {"RED", "YELLOW", "GREEN"};

   while(cycle--)
   {
      for (i = 0; i < 3; i++){
         led_on(leds[i]);
         oled_clear();
         oled_draw_string(28, 4, names[i]);
         delay_ms(1000);
      }
      oled_clear();
      oled_draw_string(28, 1, "CYCLE: ");
      oled_draw_symbol(28, 4, '0' + cycle);
      delay_ms(1000);

   }
}

#endif 
