/*
 * Terminal_Display.c
 *
 *  Created on: May 25, 2025
 *      Author: mohamed
 */
#include "Terminal_Display.h"
#include"UART.h"
void TerminalDisplayNum(uint32 num)
{
    uint32 divisor = 1;
    /* Find the highest power of 10 less than or equal to num*/
    while((divisor * 10) <= num )
    {
        divisor *= 10;
    }
    /* Extract and send each digit from most significant to least */
    while(divisor > 0)
    {
        UART_SendByte((num / divisor) + '0');
        num %= divisor;
        divisor /= 10;

    }
}
void TerminalDisplayString(uint8* string_ptr)
{
    UART_SendString(string_ptr);
}
void TerminalDisplay_NewLine(void)
{
    UART_SendString("\r\n");
}
