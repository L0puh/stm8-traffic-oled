#include "oled.h"
#include "i2c.h"
#include "led.h"
#include "utils.h"


#include <stddef.h>
#include <stdint.h>

#define RED_TIME_MS    6
#define GREEN_TIME_MS  6
#define YELLOW_TIME_MS  4


void setup() 
{
   led_init();
   i2c_init();
   oled_init();
}


static void phase(uint8_t led, const char* name, uint8_t sec)
{
   led_on(led);
   oled_draw_string(28, 1, name);

   for (; sec > 0; sec --)
   {
      oled_draw_symbol(34, 4, '0' + sec);
      oled_draw_string(46, 4, " SEC");
      delay_ms(1000);
   }
}

int main(void) {
   setup();

   while (1) {
      phase(LED_RED, "RED ", RED_TIME_MS);
      phase(LED_YEL, "YELLOW ", YELLOW_TIME_MS);
      phase(LED_GRN, "GREEN ", GREEN_TIME_MS);
   }
}
