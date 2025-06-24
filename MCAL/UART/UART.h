/*
 * UART.h
 *
 *  Created on: Mar 6, 2025
 *      Author: mohamed
 */

#ifndef UART_H_
#define UART_H_
#include"std_types.h"

/****************************************************
 * UART registers and bits
 ****************************************************/
#define RCGCUART (*((volatile uint32*)(0x400FE618)))
#define UART0_CLOCK_ENABLE_BIT (0U)
#define PRUART (*((volatile uint32*)(0x400FEA18)))
#define UART0_MODULE_PERIPHERAL_READY_BIT (0U)
#define UARTDR (*((volatile uint32*)(0x4000C000)))
#define UARTCTL (*((volatile uint32*)(0x4000C030)))
#define UARTEN_BIT   (0U)
#define SIREN_BIT    (1U)
#define SIRLP_BIT    (2U)
#define SMART_BIT    (3U)
#define EOT_BIT      (4U)
#define HSE_BIT      (5U)
#define LBE_BIT      (7U)
#define TXE_BIT      (8U)
#define RXE_BIT      (9U)
#define RTS_BIT      (11U)
#define RTSEN_BIT    (14U)
#define CTSEN_BIT    (15U)
#define UARTLCRH (*((volatile uint32*)(0x4000C02C)))
#define UARTIBRD (*((volatile uint32*)(0x4000C024)))
#define UARTFBRD (*((volatile uint32*)(0x4000C028)))
#define UARTFR (*((volatile uint32*)(0x4000C018)))
#define UART_BUSY_BIT (3U)
#define UARTCC (*((volatile uint32*)(0x4000CFC8)))
/****************************************************
 * Preprocessor Macros
 ****************************************************/
                                              /* SPS WLEN FEN STP2 EPS PEN BRK */
#define UARTLCRH_8_BITS_CONFIGURATION (0x60) /*   0  1  1   0  0   0   0   0 */
#define UARTLCRH_8_BITS_CONFIGURATION_MASK (0x000000FF)
#define UARTLCRH_8_BITS_CONFIGURATION_CLEAR_MASK (0xFFFFFF00)
#define BAUDRATE9600_BRDI_VALUE (104U)
#define BAUDRATE9600_BRDF_VALUE (11U)
#define BRDI_VALUE_MASK (0x0000FFFF)
#define BRDF_VALUE_MASK (0x0000003F)
#define UART_ZERO (0U)
/****************************************************
 * Functions prototypes
 ***************************************************/
void UART_init(void);
void UART_SendByte(uint8 Byte);
uint8 UART_ReceiveByte(void);
void UART_SendString(uint8* string_ptr);
void UART_ReceiveString(uint8* string_ptr);
#endif /* UART_H_ */
