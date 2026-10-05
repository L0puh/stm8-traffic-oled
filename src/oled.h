#ifndef OLED_H
#define OLED_H


#include <stdint.h>

// 7-bit addr for SSD1306
#define OLED_ADDR (0x3C << 1)


static const uint8_t oled_init_seq[] = {
   0xAE, // display OFF
   0xD5, 0x80, // set display clock divide ration / osci freq. 105Hz 
   0xA8, 0x3F, // set multiplex ration, number of lines - height (64)
   0xD3, 0x00, // no display offset 
   0x40, // set display start line - 0 
   0x8D, 0x14, // enable charge pump setting (generate ~7.5V from 3.3V)
   0x20, 0x02, // set memory addressing mode - page (after 8 lines)
   0xA1, // set segment re-map (mirror X)
   0xC8, // set COM output scan direction (mirror Y)
   0xDA, 0x12, // set COM pins hardware config
   0x81, 0xCF, // set contrast control 
   0xD9, 0xF1, // set pre-charge period 
   0xDB, 0x40, // set VCOMH deselect level 
   0xA4, // entire display resume to RAM content 
   0xA6, // set normal display (not inverse)
   0xAF, // display ON
};

void oled_init(void);
void oled_set_pos(uint8_t x, uint8_t y);
void oled_clear(void);
void oled_cmd(uint8_t cmd);
void oled_data_begin(void);
void oled_draw_symbol(uint8_t x, uint8_t y, char c);
void oled_draw_string(uint8_t x, uint8_t y, const char* str);
void oled_data_stop(void);

#endif 
