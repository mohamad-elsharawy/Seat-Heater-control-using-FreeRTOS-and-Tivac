/*
 * Led_Lcfg.c
 *
 *  Created on: May 23, 2025
 *      Author: mohamed
 */

#include "Led.h"
#include"Port.h"
LedType Leds[NUMBER_OF_LEDS] ={\
        {PORT_F_ID,PORT_PIN1},\
        {PORT_F_ID,PORT_PIN2},\
        {PORT_F_ID,PORT_PIN3}};


