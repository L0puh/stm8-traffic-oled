#include "traffic.h"
#include "adc.h"
#include "button.h"
#include "led.h"
#include "oled.h"
#include "timer.h"
#include "utils.h"

#define SPEED 5

static uint8_t hour(void)
{
   return (uint8_t)((adc_read() * 24) / 1024);
}

static uint8_t score(uint8_t h)
{
   if (h >= 7  && h < 11) return 9;
   if (h >= 11 && h < 17) return 5;
   if (h >= 17 && h < 21) return 9;
   return 3;
}

static void show_info(uint8_t h)
{
   oled_draw_symbol(0,  6, '0' + h / 10);
   oled_draw_symbol(12, 6, '0' + h % 10);
   oled_draw_symbol(36, 6, 'T');
   oled_draw_symbol(48, 6, '0' + score(h));
}

static void show_sec(uint8_t n)
{
   oled_draw_symbol(34, 4, '0' + n / 10);
   oled_draw_symbol(46, 4, '0' + n % 10);
}

static uint8_t phase(uint8_t led, const char *name, uint8_t sec)
{
   uint32_t start = millis(), total = sec * 1000UL / SPEED;
   uint8_t last = 255, last_h = 255, left, h;

   oled_clear();
   oled_draw_string(28, 1, name);
   led_on(led);

   while (millis() - start < total) {
      left = ((total - (millis() - start)) * SPEED + 999UL) / 1000UL;
      if (left != last) { last = left; show_sec(left); }

      h = hour();
      if (h != last_h) {
         last_h = h;
         show_info(h);
         if (score(h) == 3) return 1;
      }
   }
   return 0;
}

static void day(void)
{
   uint8_t s;
   while (1) {
      s = score(hour());
      if (phase(LED_RED, "RED", s == 9 ? 25 : 20)) return;

      s = score(hour());
      if (phase(LED_GRN, "GREEN", s == 9 ? 35 : 25)) return;

      if (phase(LED_YEL, "YELLOW", 3)) return;
   }
}

static void night(void)
{
   uint8_t ped = 0, on = 0;
   uint32_t last = millis();

   oled_clear();
   oled_draw_string(28, 1, "NIGHT");

   while (score(hour()) == 3) {
      if (button_debounce() && ped < 2) {
         ped++;
         led_on(LED_YEL);
         delay_ms(3000 / SPEED);
         led_on(LED_RED);
         oled_clear();
         oled_draw_string(28, 1, "WALK");
         delay_ms(10000 / SPEED);
         oled_clear();
         oled_draw_string(28, 1, "NIGHT");
         last = millis();
      }

      if (millis() - last >= 1000) {
         last = millis();
         on = !on;
         led_on(on ? LED_YEL : 0);
      }
   }
   led_on(0);
}

void run_traffic(void)
{
   while (1) {
      if (score(hour()) == 3) night();
      else day();
   }
}
