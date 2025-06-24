/*
 * UART.c
 *
 *  Created on: Mar 6, 2025
 *      Author: mohamed
 */
#include"UART.h"
#include"common_macros.h"
void UART_init(void)
{
 /* enable and provide clock to ADC0 module */
    SET_BIT(RCGCUART,UART0_CLOCK_ENABLE_BIT);

    /* wait till module is enabled */
    while(BIT_IS_CLEAR(PRUART,UART0_MODULE_PERIPHERAL_READY_BIT));

    /* disable UART0 before initialization */
    CLEAR_BIT(UARTCTL,UARTEN_BIT);

    /* configure UART clock to be system clock */
    WRITE_4_BITS(UARTCC,UART_ZERO,UART_ZERO);

    /* enable UART Transmit and Receive */
    SET_BIT(UARTCTL,TXE_BIT);
    SET_BIT(UARTCTL,RXE_BIT);

    /* configure baudrate to be 9600 */
    UARTIBRD = (uint32)BAUDRATE9600_BRDI_VALUE & BRDI_VALUE_MASK;
    UARTFBRD = (uint32)BAUDRATE9600_BRDF_VALUE & BRDF_VALUE_MASK;

    /* configure UART no parity bits , one stop bit , disable FIFO , 8 bits */
    UARTLCRH = (UARTLCRH & UARTLCRH_8_BITS_CONFIGURATION_CLEAR_MASK) |\
               ( (uint32)UARTLCRH_8_BITS_CONFIGURATION & UARTLCRH_8_BITS_CONFIGURATION_MASK);

    /* enable UART0 */
       SET_BIT(UARTCTL,UARTEN_BIT);

}
void UART_SendByte(uint8 Byte)
{
   while(BIT_IS_SET(UARTFR,UART_BUSY_BIT));

    UARTDR =(uint32) Byte;

}
/*
uint8 UART_ReceiveByte(void)
{

}
*/
void UART_SendString(uint8* string_ptr)
{
    uint8 count=0;
while(string_ptr[count] != '\0')
{
    UART_SendByte(string_ptr[count]);
    count++;
}
}
/*
void UART_ReceiveString(uint8* string_ptr)
{

}
*/
