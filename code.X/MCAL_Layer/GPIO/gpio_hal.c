#include "gpio_hal.h"

/* Reference to tris registers */
 volatile uint8* tris_registers[] = { &TRISA, &TRISB, &TRISC, &TRISD, &TRISE };
/* Reference to port registers */
 volatile uint8* port_registers[] = { &PORTA, &PORTB, &PORTC, &PORTD, &PORTE };

std_ReturnType gpio_pin_initialize_direction(const pin_config_t* pin_config)
{
    std_ReturnType ret = E_NOT_OK;
    if((NULL == pin_config)||(pin_config->pin > PORT_PIN_MAX_NUM - 1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = E_OK;
        switch(pin_config->direction)
        {
            case GPIO_OUTPUT: 
                CLEAR_BIT(*tris_registers[pin_config->port], pin_config->pin);
                break;
            case GPIO_INPUT: 
                SET_BIT(*tris_registers[pin_config->port], pin_config->pin);
                break;
            default:
                ret = E_NOT_OK;
        }
    }
    return ret;
}
std_ReturnType gpio_pin_get_direction(const pin_config_t* pin_config, direction_t* direction)
{
    std_ReturnType ret = E_NOT_OK;
    if((NULL == pin_config)||(NULL == direction)||(pin_config->pin > PORT_PIN_MAX_NUM - 1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction = READ_BIT(*tris_registers[pin_config->port], pin_config->pin);
        ret = E_OK;
    }
    return ret;
}
std_ReturnType gpio_pin_write_logic(const pin_config_t* pin_config, logic_t logic)
{
    std_ReturnType ret = E_NOT_OK;
    if((NULL == pin_config)||(pin_config->pin > PORT_PIN_MAX_NUM - 1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = E_OK;
        switch(logic)
        {
            case GPIO_LOW:
                CLEAR_BIT(*port_registers[pin_config->port], pin_config->pin);
                break;
            case GPIO_HIGH:
                SET_BIT(*port_registers[pin_config->port], pin_config->pin);
                break;   
            default:
                ret = E_NOT_OK;
        }
    }
    return ret;
}
std_ReturnType gpio_pin_read_logic(const pin_config_t* pin_config, logic_t* logic)
{
    std_ReturnType ret = E_NOT_OK;
    if((NULL == pin_config)||(NULL == logic)||(pin_config->pin > PORT_PIN_MAX_NUM - 1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = READ_BIT(*port_registers[pin_config->port], pin_config->pin);
        ret = E_OK;
    }
    return ret;
}
std_ReturnType gpio_pin_toggle_logic(const pin_config_t* pin_config)
{
    std_ReturnType ret = E_NOT_OK;
    if((NULL == pin_config)||(pin_config->pin > PORT_PIN_MAX_NUM - 1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        TOGGLE_BIT(*port_registers[pin_config->port], pin_config->pin);
        ret = E_OK;
    }
    return ret;
}
std_ReturnType gpio_pin_initialize(const pin_config_t* pin_config)
{
    std_ReturnType ret = E_NOT_OK;
    if((NULL == pin_config)||(pin_config->pin > PORT_PIN_MAX_NUM - 1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = E_OK;
        ret &= gpio_pin_initialize_direction(pin_config);
        ret &= gpio_pin_write_logic(pin_config, pin_config->logic);
    }
    return ret;
}

std_ReturnType gpio_port_initialize_direction(const port_index_t port, uint8 direction)
{
    std_ReturnType ret = E_NOT_OK;
    if(port > PORT_MAX_NUM -1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *tris_registers[port] = direction;
        ret = E_OK;
    }
    return ret;
}
std_ReturnType gpio_port_get_direction(const port_index_t port, uint8* direction)
{
    std_ReturnType ret = E_NOT_OK;
    if((port > PORT_MAX_NUM -1)||(NULL == direction))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction = *tris_registers[port];
        ret = E_OK;
    }
    return ret;
}
std_ReturnType gpio_port_write_logic(const port_index_t port, uint8 logic)
{
    std_ReturnType ret = E_NOT_OK;
    if(port > PORT_MAX_NUM -1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *port_registers[port] = logic;
        ret = E_OK;
    }
    return ret;
}
std_ReturnType gpio_port_read_logic(const port_index_t port, uint8* logic)
{
    std_ReturnType ret = E_NOT_OK;
    if((port > PORT_MAX_NUM -1)||(NULL == logic))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = *port_registers[port];
         ret = E_OK;
    }
    return ret;
}
std_ReturnType gpio_port_toggle_logic(const port_index_t port)
{
    std_ReturnType ret = E_NOT_OK;
    if(port > PORT_MAX_NUM -1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *port_registers[port] ^= PORT_MASK;
        ret = E_OK;
    }
    return ret;
}