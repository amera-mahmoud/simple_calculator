/* 
 * File:   ecu_keypad.h
 * Author: FiX-DEll
 *
 * Created on February 21, 2024, 2:50 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/*------------------------Include section-------------------------------*/
#include "../../MCAL_Layer/GPIO/gpio_hal.h"


/*------------------------Macro Declaration section---------------------*/
#define KEYPAD_ROWS_NUM    4
#define KEYPAD_COLUMNS_NUM 4

/*------------------------Data Type Declaration section-----------------*/
typedef struct 
{
    pin_config_t keypad_row_pins[KEYPAD_ROWS_NUM];
    pin_config_t keypad_column_pins[KEYPAD_COLUMNS_NUM];
}keypad_t;
/*------------------------Macro Function Declaration section------------*/
/*------------------------Function Declaration section------------------*/
std_ReturnType keypad_initialize(keypad_t* keypad);
std_ReturnType keypad_get_value(keypad_t* keypad, uint8* value);

#endif	/* ECU_KEYPAD_H */

