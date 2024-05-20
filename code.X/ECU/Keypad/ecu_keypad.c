#include "ecu_keypad.h"

static const uint8 keypad_btns[KEYPAD_ROWS_NUM][KEYPAD_COLUMNS_NUM] = { {'1', '2', '3', '/'},
                                                                        {'4', '5', '6', '*'},
                                                                        {'7', '8', '9', '-'},
                                                                        {'#', '0', '=', '+'} };

std_ReturnType keypad_initialize(keypad_t* keypad)
{
    std_ReturnType ret = E_NOT_OK;
    uint8 row_counter = 0;
    uint8 columns_counter = 0;
    if(NULL == keypad)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = E_OK;
        for(row_counter = 0; row_counter < KEYPAD_ROWS_NUM; row_counter++)
        {
            ret &= gpio_pin_initialize(&(keypad->keypad_row_pins[row_counter]));
        }
        for(columns_counter = 0; columns_counter < KEYPAD_COLUMNS_NUM; columns_counter++)
        {
            ret &= gpio_pin_initialize_direction(&(keypad->keypad_column_pins[columns_counter]));
        }
    }
    return ret;
}
std_ReturnType keypad_get_value(keypad_t* keypad, uint8* value)
{
    std_ReturnType ret = E_NOT_OK;
    uint8 row_counter = 0;
    uint8 columns_counter = 0;
    uint8 counter = 0;
    logic_t col_logic;
    if((NULL == keypad)||(NULL == value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = E_OK;
        for(row_counter = 0; row_counter < KEYPAD_ROWS_NUM; row_counter++)
        {
            for(counter = 0; counter < KEYPAD_ROWS_NUM; counter++)
               ret &= gpio_pin_write_logic(&(keypad->keypad_row_pins[counter]), GPIO_LOW); 
            
            ret &= gpio_pin_write_logic(&(keypad->keypad_row_pins[row_counter]), GPIO_HIGH); 
            
            for(columns_counter = 0; columns_counter < KEYPAD_COLUMNS_NUM; columns_counter++)
            {
                ret &= gpio_pin_read_logic(&(keypad->keypad_column_pins[columns_counter]), &col_logic);
                if(GPIO_HIGH == col_logic)
                {
                    *value = keypad_btns[row_counter][columns_counter];
                }
            }
        }
        
    }
    return ret;
}
