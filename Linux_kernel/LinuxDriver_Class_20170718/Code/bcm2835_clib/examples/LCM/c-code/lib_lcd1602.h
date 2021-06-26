#include<stdint.h>
#include<unistd.h>
#include<bcm2835.h>

#ifndef __LIB_LCD1602_H
#define __LIB_LCD1602_H
//
// BCM Pin setup
// 
//#define LCD_D4    RPI_BPLUS_GPIO_J8_35 
//#define LCD_D5    RPI_BPLUS_GPIO_J8_33 
//#define LCD_D6    RPI_BPLUS_GPIO_J8_31 
//#define LCD_D7    RPI_BPLUS_GPIO_J8_29 
//#define LCD_RS    RPI_BPLUS_GPIO_J8_38 
//#define LCD_RW    RPI_BPLUS_GPIO_J8_40 
//#define LCD_E     RPI_BPLUS_GPIO_J8_37 
//
#define LCD_D4    RPI_BPLUS_GPIO_J8_31
#define LCD_D5    RPI_BPLUS_GPIO_J8_33 
#define LCD_D6    RPI_BPLUS_GPIO_J8_35 
#define LCD_D7    RPI_BPLUS_GPIO_J8_37 
#define LCD_RS    RPI_BPLUS_GPIO_J8_38 
#define LCD_RW    RPI_BPLUS_GPIO_J8_40 
#define LCD_E     RPI_BPLUS_GPIO_J8_29 

#define RW_ON     bcm2835_gpio_write(LCD_RW,HIGH)
#define RW_OFF    bcm2835_gpio_write(LCD_RW,LOW) 
#define RS_ON     bcm2835_gpio_write(LCD_RS,HIGH)
#define RS_OFF    bcm2835_gpio_write(LCD_RS,LOW) 
#define E_ON      bcm2835_gpio_write(LCD_E,HIGH) 
#define E_OFF     bcm2835_gpio_write(LCD_E,LOW)  

///////////////////////////
// FUNCTION DELCARATION
///////////////////////////
void    lcd_init();
// WRITE FUNCTION 
void    lcd_write_data(uint8_t _byte);
void    lcd_write_cmd(uint8_t _byte);
// READ FUNCTION
uint8_t lcd_read_data();
uint8_t lcd_read_busy_data();
uint8_t lcd_read_addr();
void    lcd_wait_busy();
// PRINT CHAR, STRING ABOUT FUNCTION
int     lcd_pos(   uint8_t line, uint8_t row);
void    lcd_putc( uint8_t ch);
void    lcd_putStr_at(uint8_t line, uint8_t row, char *str);
void    lcd_build_self_char(uint8_t _pos, uint8_t * _ptr);
// other
void    lcd_set_pin_output();
void    lcd_set_pin_input();





#endif
