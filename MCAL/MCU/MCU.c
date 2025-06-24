/*
 * MCU.c
 *
 *  Created on: may 22, 2025
 *      Author: mohamed
 */
#include "Port.h"
#include"UART.h"
#include"ADC.h"
#include"Timer0.h"

void MCU_init(void)
{
    Port_init();

    ADC_init();
    UART_init();
    Timer0_init();

    /* configure UART pin */
    Port_SetPinMode(PORT_A_ID ,PORT_PIN1,PORT_PIN_ALT1);
    Port_SetPinDirection(PORT_A_ID,PORT_PIN1,PORT_PIN_OUT);

    /* configure ADC pin */
    Port_SetPinMode(PORT_E_ID,PORT_PIN3,PORT_PIN_ADC_MODE);
    Port_SetPinDirection(PORT_E_ID,PORT_PIN3,PORT_PIN_IN);

    /* start timer to count */
    Timer0Start();
}

