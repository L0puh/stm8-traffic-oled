#include "adc.h"
#include "button.h"
#include "oled.h"
#include "i2c.h"
#include "led.h"
#include "utils.h"
#include "cycle.h"
#include "timer.h"
#include "traffic.h"


#include <stddef.h>
#include <stdint.h>

#define RED_TIME_MS    6
#define GREEN_TIME_MS  6
#define YELLOW_TIME_MS  4


void setup() 
{
   CLK_CKDIVR = 0x00;
   led_init();
   i2c_init();
   oled_init();
   adc_init();
   timer_init();
}


int main(void) {
   setup();

   uint8_t sec = 3;
   uint8_t mode = 1;
   oled_draw_string(28, 1, "MODE 1");

   while (sec > 0) {
      oled_draw_symbol(34, 4, '0' + sec);

      for (uint8_t i = 0; i < 20; i++)
      {
         if (button_debounce()){
            mode = (mode == 1) ? 2: 1;

            oled_clear();
            if (mode == 1) oled_draw_string(28, 1, "MODE 1");
            else oled_draw_string(28, 1, "MODE 2");

            sec = 3;
            break;
         }
         delay_ms(50);
      }

      sec--;
   }
   oled_clear();

   if (mode == 1) {
      run_cycle(8);
   } else {
      run_traffic();
   }
}
