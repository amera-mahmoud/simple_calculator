/* 
 * File:   ecu_led.h
 * Author: FiX-DEll
 *
 * Created on February 20, 2024, 6:44 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/*------------------------Include section-------------------------------*/
#include "../../MCAL_Layer/GPIO/gpio_hal.h"


/*------------------------Data Type Declaration section-----------------*/
typedef struct
{
    uint8 port     :3;
    uint8 pin      :3;
    uint8 logic    :1;
    uint8 reserved :1;
}led_t;

/*------------------------Macro Declaration section---------------------*/
#define LED_OFF 0x00
#define LED_ON  0x01

/*------------------------Macro Function Declaration section------------*/
/*------------------------Function Declaration section------------------*/
std_ReturnType led_intialize(const led_t *led);
std_ReturnType led_turn_off(const led_t *led);
std_ReturnType led_turn_on(const led_t *led);
std_ReturnType led_turn_toggle(const led_t *led);
#endif	/* ECU_LED_H */

