/*
 * DIO.H
 *
 *  Created on: May 17, 2025
 *      Author: mohamed
 */

#ifndef DIO_H_
#define DIO_H_


/*****************************************************************
 * Includes
 *****************************************************************/
#include"std_types.h"

/******************************************************************
 * Registers
 ******************************************************************/
#define DIO_PORT_A_REGISTERS_BASE_ADDRESS ((volatile uint32*)0x40004000)
#define DIO_PORT_B_REGISTERS_BASE_ADDRESS ((volatile uint32*)0x40005000)
#define DIO_PORT_C_REGISTERS_BASE_ADDRESS ((volatile uint32*)0x40006000)
#define DIO_PORT_D_REGISTERS_BASE_ADDRESS ((volatile uint32*)0x40007000)
#define DIO_PORT_E_REGISTERS_BASE_ADDRESS ((volatile uint32*)0x40024000)
#define DIO_PORT_F_REGISTERS_BASE_ADDRESS ((volatile uint32*)0x40025000)
#define DIO_GPIODATA_REG_OFFSET 0x3FC
/*****************************************************************
 * Function prototypes
 *****************************************************************/
void Dio_Write_Channel(uint8 Port,uint8 Pin,uint8 Value);
uint8 Dio_Read_Channel(uint8 Port,uint8 Pin);

/******************************************************************
 * Preprocessor Macros
 *****************************************************************/
#define DIO_HIGH (uint8)1
#define DIO_LOW (uint8)0
#define DIO_PORT_A_ID (0U)
#define DIO_PORT_B_ID (1U)
#define DIO_PORT_C_ID (2U)
#define DIO_PORT_D_ID (3U)
#define DIO_PORT_E_ID (4U)
#define DIO_PORT_F_ID (5U)
#endif /* DIO_H_ */
