/*
 * Port.h
 *
 *  Created on: Mar 10, 2025
 *      Author: mohamed
 */

#ifndef PORT_H_
#define PORT_H_
#include"std_types.h"
/******************************************************
 * Port Registers and Pins
 ******************************************************/
#define RCGCGPIO (*((volatile uint32*)0x400FE608))
#define PRGPIO (*((volatile uint32*)0x400FEA08))
#define PORT_A_REGISTERS_BASE_ADDRESS ((volatile uint32*)0x40004000)
#define PORT_B_REGISTERS_BASE_ADDRESS ((volatile uint32*)0x40005000)
#define PORT_C_REGISTERS_BASE_ADDRESS ((volatile uint32*)0x40006000)
#define PORT_D_REGISTERS_BASE_ADDRESS ((volatile uint32*)0x40007000)
#define PORT_E_REGISTERS_BASE_ADDRESS ((volatile uint32*)0x40024000)
#define PORT_F_REGISTERS_BASE_ADDRESS ((volatile uint32*)0x40025000)
#define GPIODIR_REG_OFFSET 0x400
#define GPIOAFSEL_REG_OFFSET 0x420
#define GPIOPUR_REG_OFFSET 0x510
#define GPIOPDR_REG_OFFSET 0x514
#define GPIODEN_REG_OFFSET 0x51C
#define GPIOLOCK_REG_OFFSET 0x520
#define GPIOCR_REG_OFFSET 0x524
#define GPIOAMSEL_REG_OFFSET 0x528
#define GPIOPCTL_REG_OFFSET 0x52C
#define GPIOIS_REG_OFFSET 0x404
#define GPIOIBE_REG_OFFSET 0x408
#define GPIOIEV_REG_OFFSET 0x40C
#define GPIOIM_REG_OFFSET 0x410
#define GPIORIS_REG_OFFSET 0x414
#define GPIOMIS_REG_OFFSET 0x418
#define GPIOICR_REG_OFFSET 0x41C

/******************************************************
 * Preprocessor Macros
 *****************************************************/
#define PORT_IRQ_PRIORITY 5
#define ENABLE_CLOCK_ALL_PORTS_BITS (0x0000003F)
#define ENABLE_CLOCK_ALL_PORTS_CLEAR_MASK (0xFFFFFFC0)
#define PORT_A_ID (0U)
#define PORT_B_ID (1U)
#define PORT_C_ID (2U)
#define PORT_D_ID (3U)
#define PORT_E_ID (4U)
#define PORT_F_ID (5U)
#define PORT_PIN0 (0U)
#define PORT_PIN1 (1U)
#define PORT_PIN2 (2U)
#define PORT_PIN3 (3U)
#define PORT_PIN4 (4U)
#define PORT_PIN5 (5U)
#define PORT_PIN6 (6U)
#define PORT_PIN7 (7U)
#define INTERNAL_RESISTANCE_OFF (0U)
#define PULL_UP_RESISTANCE (1U)
#define PULL_DOWN_RESISTANCE (2U)
#define PORT_PIN_IN (0U)
#define PORT_PIN_OUT (1U)
#define PORT_PIN_ADC_MODE (0U)
#define PORT_PIN_ALT1 (1U)
#define PORT_PIN_ALT2 (2U)
#define PORT_PIN_ALT3 (3U)
#define PORT_PIN_ALT4 (4U)
#define PORT_PIN_ALT5 (5U)
#define PORT_PIN_ALT6 (6U)
#define PORT_PIN_ALT7 (7U)
#define PORT_PIN_ALT8 (8U)
#define PORT_PIN_ALT9 (9U)
#define PORT_PIN_ALT14 (14U)
#define PORT_PIN_GPIO_MODE (15U)
#define PORT_PIN_BOTH_EDGES_INTERRUPT (0U)
#define PORT_PIN_RISING_EDGE_INTERRUPT (1U)
#define PORT_PIN_FALLING_EDGE_INTERRUPT (2U)
#define PORT_PIN_HIGH_LEVEL_INTERRUPT (3U)
#define PORT_PIN_LOW_LEVEL_INTERRUPT (4U)
#define JTAG_CLOCK_PIN (16U)
#define JTAG_MODE_SELECT_PIN (17U)
#define JTAG_DATA_IN_PIN (18U)
#define JTAG_DATA_OUT_PIN (19U)
#define PORTD_LOCKED_PIN (7U)
#define PORTF_LOCKED_PIN (0U)
#define GPIO_UNLOCK_VALUE  ((uint32)0x4C4F434B)
#define BITS_ALL_SET_8 (0xFF)
#define BITS_ALL_SET_32 (0xFFFFFFFF)
#define BITS_ALL_CLEAR_32 (0x00000000)
#define FOUR_ZERO_BITS (0x0000)
#define PIN_GPIOCTL_BITS_NUM (4U)
#define PORT_NUM_OF_PINS (8U)
#define NUM_OF_PORTS (6U)
#define PORT_INTERRUPT_STATUS_MASK (0x000000FF)
#define PORT_ZERO (0U)
#define PORT_ONE (1U)
#define PORT_A_IRQ_NUM (0U)
#define PORT_B_IRQ_NUM (1U)
#define PORT_C_IRQ_NUM (2U)
#define PORT_D_IRQ_NUM (3U)
#define PORT_E_IRQ_NUM (4U)
#define PORT_F_IRQ_NUM (30U)
/******************************************************
 * Function like Macros
 *****************************************************/
/* function like macro to unlock and enable commit of pin */
#define PORT_PIN_ENABLE_COMMIT(PORT_BASE_ADDRESS,PIN) {\
        *((volatile uint32*)((volatile uint8*)PORT_BASE_ADDRESS + GPIOLOCK_REG_OFFSET)) = GPIO_UNLOCK_VALUE;\
        (*(volatile uint32*)((volatile uint8*)PORT_BASE_ADDRESS + GPIOCR_REG_OFFSET)) |= (1 << PIN);\
}

/* function like macro to unlock and disable commit of pin */
#define PORT_PIN_DISABLE_COMMIT(PORT_BASE_ADDRESS,PIN) {\
        *((volatile uint32*)((volatile uint8*)PORT_BASE_ADDRESS + GPIOLOCK_REG_OFFSET)) = GPIO_UNLOCK_VALUE;\
        (*(volatile uint32*)((volatile uint8*)PORT_BASE_ADDRESS + GPIOCR_REG_OFFSET)) &= ~(1 << PIN);\
}
/*****************************************************
 * Functions Prototypes
 ****************************************************/
void Port_init(void);
void Port_SetPinMode(uint8 Port, uint8 Pin,uint8 Mode);
void Port_SetPinDirection(uint8 Port, uint8 Pin,uint8 Direction);
void Port_EnablePin_Interrupt(uint8 Port,uint8 Pin,uint8 Trigger);
void Port_Set_InternalResistance( uint8 Port, uint8 Pin, uint8 Resistance);
void Port_Pin_Set_CallBack(uint8 Port,uint8 Pin , void (* ptr)(uint8,uint8));
#endif /* PORT_H_ */
