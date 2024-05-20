/* 
 * File:   gpio_hal.h
 * Author: FiX-DEll
 *
 * Created on February 20, 2024, 12:19 AM
 */

#ifndef GPIO_HAL_H
#define	GPIO_HAL_H

/*------------------------Include section-------------------------------*/
#include "pic16f877A.h"
#include "../device_config.h"
#include "../mcal_std_types.h"

/*------------------------Data Type Declaration section-----------------*/
typedef enum
{
    GPIO_LOW,
    GPIO_HIGH
}logic_t;

typedef enum
{
    GPIO_OUTPUT,
    GPIO_INPUT
}direction_t;

typedef enum
{
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
}pin_index_t;

typedef enum {
    PORTA_INDEX,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
}port_index_t;

typedef struct
{
    uint8 port      :3;
    uint8 pin       :3;
    uint8 direction :1;
    uint8 logic     :1;
}pin_config_t;

/*------------------------Macro Declaration section---------------------*/
#define _XTAL_FREQ 8000000

#define PIN_MASK  (uint8)0x01
#define PORT_MASK (uint8)0xFF

#define PORT_PIN_MAX_NUM  8
#define PORT_MAX_NUM      4

/*------------------------Macro Function Declaration section------------*/
#define SET_BIT(REG, BIT_POS)    (REG |=  (PIN_MASK << BIT_POS))
#define CLEAR_BIT(REG, BIT_POS)  (REG &= ~(PIN_MASK << BIT_POS))
#define TOGGLE_BIT(REG, BIT_POS) (REG ^=  (PIN_MASK << BIT_POS))
#define READ_BIT(REG, BIT_POS)   ((REG >> BIT_POS) & PIN_MASK)

/*------------------------Function Declaration section------------------*/
std_ReturnType gpio_pin_initialize_direction(const pin_config_t* pin_config);
std_ReturnType gpio_pin_get_direction(const pin_config_t* pin_config, direction_t* direction);
std_ReturnType gpio_pin_write_logic(const pin_config_t* pin_config, logic_t logic);
std_ReturnType gpio_pin_read_logic(const pin_config_t* pin_config, logic_t* logic);
std_ReturnType gpio_pin_toggle_logic(const pin_config_t* pin_config);
std_ReturnType gpio_pin_initialize(const pin_config_t* pin_config);

std_ReturnType gpio_port_initialize_direction(const port_index_t port, uint8 direction);
std_ReturnType gpio_port_get_direction(const port_index_t port, uint8* direction);
std_ReturnType gpio_port_write_logic(const port_index_t port, uint8 logic);
std_ReturnType gpio_port_read_logic(const port_index_t port, uint8* logic);
std_ReturnType gpio_port_toggle_logic(const port_index_t port);


#endif	/* GPIO_HAL_H */

