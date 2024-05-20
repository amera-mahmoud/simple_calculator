/* 
 * File:   application.c
 * Author: FiX-DEll
 *
 * Created on February 22, 2024, 8:04 PM
 */

#include "application.h"

uint8 key_value = 0;
uint8 exp[3] = {0};
uint8 counter = 0;
float res;
uint8 res_str[11];
uint8 error_flag = 0;


int main() {
    keypad_initialize(&keypad1);
    lcd_4bit_initialize(&lcd1);
    
    lcd_4bit_send_string(&lcd1, "Welcome");
    __delay_ms(1000);
    lcd_4bit_send_command(&lcd1, _LCD_CLEAR);
    
    while(1)
    {
        /*key_value is flag that guarantee to read the key pressed one time*/
        keypad_get_value(&keypad1, &key_value);
        if(key_value != 0)
        {
            /* # key to clear the lcd*/
            if('#' == key_value)
            {
                lcd_4bit_send_command(&lcd1, _LCD_CLEAR);
                counter = 0;
                error_flag = 0;
            }
            else
            {
                lcd_4bit_send_char_data_pos(&lcd1, 1, (2*counter)+1, key_value);
                exp[counter++] = key_value;
            }
            __delay_ms(250);
            key_value = 0;
        }
        
        if(3 == counter)
        {
            counter = 0;
             switch(exp[1])
            {
                case '+': res = (float)(exp[0]-'0') + (float)(exp[2]-'0'); break;
                case '-': res = (float)(exp[0]-'0') - (float)(exp[2]-'0'); break;
                case '*': res = (float)(exp[0]-'0') * (float)(exp[2]-'0'); break;
                case '/': res = (float)(exp[0]-'0') / (float)(exp[2]-'0'); break;
                /*error flag guarantees the expression is true*/
                default: lcd_4bit_send_string_pos(&lcd1,1,1,"ERROR");  error_flag = 1;
            }
             if(0 == error_flag)
             {
                 lcd_4bit_send_char_data_pos(&lcd1, 2, 1, '=');
                 convert_float_to_string(res, res_str);
                 lcd_4bit_send_string_pos(&lcd1, 2, 3, res_str);
             }   
        }
       
        
       
    }
    return (EXIT_SUCCESS);
}
