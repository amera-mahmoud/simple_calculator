#include "ecu_chr_lcd.h"

static std_ReturnType lcd_send_4bit(const chr_lcd_4bit_t* lcd, uint8 _data_command);
static std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t* lcd);
static std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t* lcd);
static std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t* lcd, uint8 row, uint8 column);
static std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t* lcd, uint8 row, uint8 column);

std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t* lcd)
{
   std_ReturnType ret = E_NOT_OK;
   uint8 data_pins_counter = 0;
   if(NULL == lcd)
   {
       ret = E_NOT_OK;
   }
   else
   {
       ret  = gpio_pin_initialize(&(lcd->lcd_rs));   
       ret &= gpio_pin_initialize(&(lcd->lcd_en)); 
       for(data_pins_counter = 0; data_pins_counter<4; data_pins_counter++)
           ret &= gpio_pin_initialize(&(lcd->lcd_data[data_pins_counter]));
       
        __delay_ms(20);
       ret &= lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE_8_DOT_MATRIX);
       __delay_ms(5);
       ret &= lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE_8_DOT_MATRIX);
       __delay_us(150);
       ret &= lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE_8_DOT_MATRIX);
       
       ret &= lcd_4bit_send_command(lcd, _LCD_CLEAR);
       ret &= lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
       ret &= lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
       ret &= lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
       ret &= lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE_8_DOT_MATRIX);
       ret &= lcd_4bit_send_command(lcd, _LCD_DDRAM_START);  // by default
   }
   return ret;
}

std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t* lcd, uint8 command)
{
   std_ReturnType ret = E_NOT_OK;   
   if(NULL == lcd)
   {
       ret = E_NOT_OK;
   }
   else
   {
       ret  = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
       ret &= lcd_send_4bit(lcd, (command >> 4));
       ret &= lcd_4bit_send_enable_signal(lcd);
       ret &= lcd_send_4bit(lcd, command);
       ret &= lcd_4bit_send_enable_signal(lcd);
   }
   return ret;
}

std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t* lcd, uint8 data)
{
   std_ReturnType ret = E_NOT_OK;   
   if(NULL == lcd)
   {
       ret = E_NOT_OK;
   }
   else
   {
       ret  = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
       ret &= lcd_send_4bit(lcd, (data >> 4));
       ret &= lcd_4bit_send_enable_signal(lcd);
       ret &= lcd_send_4bit(lcd, data);
       ret &= lcd_4bit_send_enable_signal(lcd);
   }
   return ret;   
}

std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t* lcd, uint8 row, uint8 column,
                                            uint8 data)
{
   std_ReturnType ret = E_NOT_OK;   
   if(NULL == lcd)
   {
       ret = E_NOT_OK;
   }
   else
   {
       ret  = lcd_4bit_set_cursor(lcd, row, column);
       ret  = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
       ret &= lcd_send_4bit(lcd, (data >> 4));
       ret &= lcd_4bit_send_enable_signal(lcd);
       ret &= lcd_send_4bit(lcd, data);
       ret &= lcd_4bit_send_enable_signal(lcd);
   }
   return ret;  
}

std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t* lcd,  uint8* str)
{
   std_ReturnType ret = E_NOT_OK; 
   uint8* str_temp = str;
   if((NULL == lcd)||(NULL == str))
   {
       ret = E_NOT_OK;
   }
   else
   {
       while(*str_temp)
       {
           ret = lcd_4bit_send_char_data(lcd, *str_temp++);
       }
   }
   return ret;  
}

std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t* lcd, uint8 row, uint8 column,
                                          uint8* str)
{
   std_ReturnType ret = E_NOT_OK; 
   uint8* str_temp = str;
   if((NULL == lcd)||(NULL == str))
   {
       ret = E_NOT_OK;
   }
   else
   {
       ret = lcd_4bit_set_cursor(lcd, row, column);
       while(*str_temp)
       {
           ret = lcd_4bit_send_char_data(lcd, *str_temp++);
       }
   }
   return ret;  
}


std_ReturnType lcd_4bit_send_costume_char(const chr_lcd_4bit_t* lcd, uint8 row, uint8 column,
                                           const uint8 chr[], uint8 mem_pos)
{
   std_ReturnType ret = E_NOT_OK;   
   if(NULL == lcd)
   {
       ret = E_NOT_OK;
   }
   else
   {
       
   }
   return ret;  
}


std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t* lcd)
{
   std_ReturnType ret = E_NOT_OK;
   uint8 data_pins_counter = 0;
   if(NULL == lcd)
   {
       ret = E_NOT_OK;
   }
   else
   {
       ret  = gpio_pin_initialize(&(lcd->lcd_rs));   
       ret &= gpio_pin_initialize(&(lcd->lcd_en)); 
       for(data_pins_counter = 0; data_pins_counter<8; data_pins_counter++)
           ret &= gpio_pin_initialize(&(lcd->lcd_data[data_pins_counter]));
       __delay_ms(20);
       ret &= lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE_8_DOT_MATRIX);
       __delay_ms(5);
       ret &= lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE_8_DOT_MATRIX);
       __delay_us(100);
       ret &= lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE_8_DOT_MATRIX);
       
       ret &= lcd_8bit_send_command(lcd, _LCD_CLEAR);
       ret &= lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
       ret &= lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
       ret &= lcd_8bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
       ret &= lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE_8_DOT_MATRIX);
       ret &= lcd_8bit_send_command(lcd, _LCD_DDRAM_START);  // by default
   }
   return ret;
}

std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t* lcd, uint8 command)
{
   std_ReturnType ret = E_NOT_OK; 
   uint8 pin_counter = 0;
   if(NULL == lcd)
   {
       ret = E_NOT_OK;
   }
   else
   {
       ret  = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
       for(pin_counter = 0; pin_counter<8; pin_counter++)
           ret &= gpio_pin_write_logic(&(lcd->lcd_data[pin_counter]), (command>>pin_counter)&(uint8)0x01);
       
          ret &= lcd_8bit_send_enable_signal(lcd);
   }
   return ret;   
}

std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t* lcd, uint8 data)
{
   std_ReturnType ret = E_NOT_OK; 
   uint8 pin_counter = 0;
   if(NULL == lcd)
   {
       ret = E_NOT_OK;
   }
   else
   {
       ret  = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
       for(pin_counter = 0; pin_counter<8; pin_counter++)
          ret &= gpio_pin_write_logic(&(lcd->lcd_data[pin_counter]), (data>>pin_counter)&(uint8)0x01);
       
          ret &= lcd_8bit_send_enable_signal(lcd);
   }
   return ret;  
}

std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t* lcd, uint8 row, uint8 column,
                                            uint8 data)
{
   std_ReturnType ret = E_NOT_OK;   
   if(NULL == lcd)
   {
       ret = E_NOT_OK;
   }
   else
   {
       ret  = lcd_8bit_set_cursor(lcd, row, column);
       ret &= lcd_8bit_send_char_data(lcd, data);
   }
   return ret;  
}

std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t* lcd,  uint8* str)
{
   std_ReturnType ret = E_NOT_OK; 
   uint8* str_temp = str;
   if((NULL == lcd)||(NULL == str))
   {
       ret = E_NOT_OK;
   }
   else
   {
       while(*str_temp)
       {
           ret = lcd_8bit_send_char_data(lcd, *str_temp++);
       }
   }
   return ret;  
}

std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t* lcd, uint8 row, uint8 column,
                                         uint8* str)
{
   std_ReturnType ret = E_NOT_OK;
   uint8* str_temp = str;   
   if((NULL == lcd)||(NULL == str))
   {
       ret = E_NOT_OK;
   }
   else
   {
       ret  = lcd_8bit_set_cursor(lcd, row, column);
       while(*str_temp)
       {
           ret &= lcd_8bit_send_char_data(lcd, *str_temp++);
       }
   }
   return ret;  
}

std_ReturnType lcd_8bit_send_costume_char(const chr_lcd_8bit_t* lcd, uint8 row, uint8 column,
                                           const uint8 chr[], uint8 mem_pos)
{
   std_ReturnType ret = E_NOT_OK; 
   uint8 counter = 0;
   if(NULL == lcd)
   {
       ret = E_NOT_OK;
   }
   else
   {
       ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos*8)));
       for(counter = 0; counter<8; counter++)
       {
           ret &= lcd_8bit_send_char_data(lcd, chr[counter]);
       }
       ret &= lcd_8bit_send_char_data_pos(lcd, row, column, mem_pos);
   }
   return ret;  
}


std_ReturnType convert_byte_to_string(uint8 value, char* str)
{
   std_ReturnType ret = E_NOT_OK;   
   if(NULL == str)
   {
       ret = E_NOT_OK;
   }
   else
   {
      
   }
   return ret;  
}

std_ReturnType convert_short_to_string(uint16 value, char* str)
{
   std_ReturnType ret = E_NOT_OK;   
   if(NULL == str)
   {
       ret = E_NOT_OK;
   }
   else
   {
       
   }
   return ret;  
}

std_ReturnType convert_int_to_string(sint32 num, uint8* str)
{
   std_ReturnType ret = E_NOT_OK;   
   if(NULL == str)
   {
       ret = E_NOT_OK;
   }
   else
   {
        uint32  integer_part, temp;
        uint8 index = 0, ch, findone = 0;
    if(num < 0)
    {
       str[index++] = '-';
       num = -1 * num;
    }
 
        integer_part = (uint32) num;
            temp = 10000;
            findone = 0;
            while (temp)
            {
                ch = (uint8)(integer_part / temp);
                integer_part = integer_part % temp;
                if (ch > 0)
                {
                    findone = 1;
                    str[index++] = ch + '0';
                }
                else if(findone)
                {
                    str[index++] = ch + '0';
                }
                
                temp /= 10;
            }

    
    str[index] = '\0';
   
   }
   return ret;  
}
std_ReturnType convert_float_to_string(float num, uint8* str)
{
   std_ReturnType ret = E_NOT_OK;   
   if(NULL == str)
   {
       ret = E_NOT_OK;
   }
   else
   {
       uint8 index = 0, integer_part, temp, ch, findone = 0;
    float fractional_part;
    if(num < 0)
    {
       str[index++] = '-';
       num = -1 * num;
    }
    if(num < 1)
    {
        str[index++] = '0';
    }
    else
    {
        integer_part = (uint8) num;
            temp = 100;
            findone = 0;
            while (temp)
            {
                ch = integer_part / temp;
                integer_part = integer_part % temp;
                if (ch > 0)
                {
                    findone = 1;
                    str[index++] = ch + '0';
                }
                else if(findone)
                {
                    str[index++] = ch + '0';
                }
                
                temp /= 10;
            }
    }
    
    str[index++] = '.';
    fractional_part = num - (uint8)num;
    for(uint8 i = 0; i<5; i++)
    {
        fractional_part *= 10;
        ch = (uint8)fractional_part;
        fractional_part = fractional_part - ch;
        str[index++] = ch + '0';
    }
    str[index] = '\0';
   }
   return ret; 
}

static std_ReturnType lcd_send_4bit(const chr_lcd_4bit_t* lcd, uint8 _data_command)
{
   std_ReturnType ret = E_NOT_OK;   
   if(NULL == lcd)
   {
       ret = E_NOT_OK;
   }
   else
   {
       ret  = gpio_pin_write_logic(&(lcd->lcd_data[0]), (_data_command >> 0) & (uint8)0x01);
       ret &= gpio_pin_write_logic(&(lcd->lcd_data[1]), (_data_command >> 1) & (uint8)0x01);
       ret &= gpio_pin_write_logic(&(lcd->lcd_data[2]), (_data_command >> 2) & (uint8)0x01);
       ret &= gpio_pin_write_logic(&(lcd->lcd_data[3]), (_data_command >> 3) & (uint8)0x01);
   }
   return ret;   
}
static std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t* lcd)
{
    std_ReturnType ret = E_NOT_OK;   
   if(NULL == lcd)
   {
       ret = E_NOT_OK;
   }
   else
   {
       ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
       __delay_us(5);
       ret &= gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
   }
   return ret;   
}

static std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t* lcd)
{
    std_ReturnType ret = E_NOT_OK;   
   if(NULL == lcd)
   {
       ret = E_NOT_OK;
   }
   else
   {
       ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
       __delay_us(5);
       ret &= gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
   }
   return ret;   
}

static std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t* lcd, uint8 row, uint8 column)
{
   std_ReturnType ret = E_NOT_OK;   
   if(NULL == lcd)
   {
       ret = E_NOT_OK;
   }
   else
   {
       column--;
       switch(row)
       {
           case ROW1 : ret = lcd_8bit_send_command(lcd, (0x80 + column)); break;
           case ROW2 : ret = lcd_8bit_send_command(lcd, (0xC0 + column)); break;

           default: break;
       }
   }
   return ret;  
}

static std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t* lcd, uint8 row, uint8 column)
{
   std_ReturnType ret = E_NOT_OK;   
   if(NULL == lcd)
   {
       ret = E_NOT_OK;
   }
   else
   {
       column--;
       switch(row)
       {
           case ROW1 : ret = lcd_4bit_send_command(lcd, (0x80 + column)); break;
           case ROW2 : ret = lcd_4bit_send_command(lcd, (0xC0 + column)); break;
           default: break;
       }
   }
   return ret;  
}



