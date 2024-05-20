#include "ecu_led.h"

std_ReturnType led_intialize(const led_t *led)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK; 
    }
    else
    {
        pin_config_t pin_obj = { .port = led->port, .pin = led->pin, .direction = GPIO_OUTPUT,
                                 .logic = led->logic };
        ret = E_OK;
        ret &= gpio_pin_initialize(&pin_obj);
    }
    return ret;
}
std_ReturnType led_turn_off(const led_t *led)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = { .port = led->port, .pin = led->pin, .direction = GPIO_OUTPUT,
                                 .logic = led->logic };
        ret = E_OK;
        ret &= gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    return ret;
}
std_ReturnType led_turn_on(const led_t *led)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = { .port = led->port, .pin = led->pin, .direction = GPIO_OUTPUT,
                                 .logic = led->logic };
        ret = E_OK;
        ret &= gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return ret;
}
std_ReturnType led_turn_toggle(const led_t *led)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
       pin_config_t pin_obj = { .port = led->port, .pin = led->pin, .direction = GPIO_OUTPUT,
                                 .logic = led->logic };
        ret = E_OK;
        ret &= gpio_pin_toggle_logic(&pin_obj);
    }
    return ret;
}
