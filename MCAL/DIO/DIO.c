/*
 * DIO.c
 *
 *  Created on: May 17, 2025
 *      Author: mohamed
 */

#include"DIO.h"
#include"common_macros.h"
static inline volatile uint32* Get_Port_BaseAddress(
        uint8 Port
)
{ /* function to get the base address of the required   port */
    volatile uint32 * Port_BaseAddress = Null ;
    switch (Port)
    {
    case DIO_PORT_A_ID: Port_BaseAddress = DIO_PORT_A_REGISTERS_BASE_ADDRESS;
    break;
    case DIO_PORT_B_ID: Port_BaseAddress = DIO_PORT_B_REGISTERS_BASE_ADDRESS;
    break;
    case DIO_PORT_C_ID: Port_BaseAddress = DIO_PORT_C_REGISTERS_BASE_ADDRESS;
    break;
    case DIO_PORT_D_ID: Port_BaseAddress = DIO_PORT_D_REGISTERS_BASE_ADDRESS;
    break;
    case DIO_PORT_E_ID: Port_BaseAddress = DIO_PORT_E_REGISTERS_BASE_ADDRESS;
    break;
    case DIO_PORT_F_ID: Port_BaseAddress = DIO_PORT_F_REGISTERS_BASE_ADDRESS;
    }
    return Port_BaseAddress;
}
void Dio_Write_Channel(uint8 Port,uint8 Pin,uint8 Value)
{
    volatile uint32* Port_BaseAddress = Null;
    /* get port base address */
    Port_BaseAddress = Get_Port_BaseAddress(Port);

    /* check value */
    if(DIO_HIGH == Value )
    {
        SET_BIT((*((volatile uint32*)(((uint8 *)Port_BaseAddress) + DIO_GPIODATA_REG_OFFSET))),Pin);
    }
    else if(DIO_LOW == Value)
    {
        CLEAR_BIT((*((volatile uint32*)(((uint8 *)Port_BaseAddress) + DIO_GPIODATA_REG_OFFSET))),Pin);
    }
}
uint8 Dio_Read_Channel(uint8 Port,uint8 Pin)
{
    uint8 Value;
    volatile uint32* Port_BaseAddress = Null;

    /* get port base address */
    Port_BaseAddress = Get_Port_BaseAddress(Port);

    /* check bit state */
    if(BIT_IS_SET((*((volatile uint32*)((uint8 *)Port_BaseAddress) + DIO_GPIODATA_REG_OFFSET)),Pin))
    {
        Value = DIO_HIGH;
    }
    else
    {
        Value = DIO_LOW;
    }
    return Value;

}

