/*
 * Led.c
 *
 *  Created on: May 17, 2025
 *      Author: mohamed elsharawy
 */
#include <Led.h>
#include"Port.h"
#include"DIO.h"

extern LedType Leds[];
/*
 * the init function loops over all leds and configure the led pin Mode,no internal resistance and direction
 */
void Led_init(void)
{
    uint8 Led_ID;
    for(Led_ID = 0; Led_ID < NUMBER_OF_LEDS; Led_ID ++)
    {
        Port_SetPinMode(Leds[Led_ID].LedPort,Leds[Led_ID].LedPin,PORT_PIN_GPIO_MODE);
        Port_Set_InternalResistance(Leds[Led_ID].LedPort,Leds[Led_ID].LedPin,INTERNAL_RESISTANCE_OFF);
        Port_SetPinDirection(Leds[Led_ID].LedPort,Leds[Led_ID].LedPin,PORT_PIN_OUT);
    }

}
void Led_on(uint8 LedChannel)
{
    Dio_Write_Channel(Leds[LedChannel].LedPort,Leds[LedChannel].LedPin,DIO_HIGH);
}
void Led_off(uint8 LedChannel)
{
    Dio_Write_Channel(Leds[LedChannel].LedPort,Leds[LedChannel].LedPin,DIO_LOW);
}
