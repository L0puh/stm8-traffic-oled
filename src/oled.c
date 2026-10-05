#include "oled.h"
#include "i2c.h"
#include "utils.h"
#include "font.h"

void oled_init(void)
{
   // OLED init 
   delay_ms(100);
   for (uint8_t i = 0; i < sizeof(oled_init_seq); i++){
      oled_cmd(oled_init_seq[i]);
   }
   oled_clear();
}

static uint8_t get_symbol_index(char c)
{

   if (c >= '0' && c <= '9' ) return c - '0' + 2; 
   if (c >= 'A' && c <= 'Z' ) return c - 'A' + 12; 
   if (c == ':') return 1;
   return 0; // space
}

static uint8_t scale_vertically(uint8_t n)
{
   //double bits
   uint8_t r = 0, i;
   for (i = 0; i < 4; i++)
      if (n & (1 << i))
         r |= 3 << (2 * i);
   return r;
}

// send cmd: start -> addr -> control bit -> cmd -> stop
void oled_cmd(uint8_t cmd)
{
    i2c_start();
    i2c_write(OLED_ADDR);
    i2c_write(0x00);
    i2c_write(cmd);
    i2c_stop();
}

void oled_draw_symbol(uint8_t x, uint8_t y, char c)
{
   uint8_t idx, half, i, b;
   
   idx = get_symbol_index(c);

   // draw up and down part
   for (half = 0; half < 2; half++)
   {
      oled_set_pos(x, y+half);
      oled_data_begin();

      for (i = 0; i < 5; i++)
      {
         b = font[idx][i];
         b = scale_vertically(half ? (b >> 4) : (b & 0x0F));
         i2c_write(b);
         i2c_write(b);
      }

      i2c_write(0x00);
      i2c_write(0x00);
      oled_data_stop();
   }
}


void oled_draw_string(uint8_t x, uint8_t y, const char* str)
{
   while (*str)
   {
      oled_draw_symbol(x, y, *str++);
      x += 12;
   }
}


void oled_clear(void)
{
   uint8_t pos, i;
   for (pos = 0; pos < 8; pos ++)
   {
      oled_set_pos(0, pos);
      oled_data_begin();
      for (i = 0; i < 128; i++)
         i2c_write(0x00);
      oled_data_stop();
   }
}

void oled_data_stop(void)
{
   i2c_stop();
}

void oled_data_begin(void)
{
   i2c_start();
   i2c_write(OLED_ADDR);
   i2c_write(0x40);
}

void oled_set_pos(uint8_t x, uint8_t y)
{
   oled_cmd(0xB0 | y);        // page number  
   oled_cmd(x & 0x0F);        // lower 4 bits
   oled_cmd(0x10 | (x >> 4)); // highest 4 bits 

}

