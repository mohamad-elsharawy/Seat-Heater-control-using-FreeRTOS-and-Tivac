/*
 * Port.c
 *
 *  Created on: Mar 10, 2025
 *      Author: mohamed
 */
#include"Port.h"
#include"common_macros.h"
#include"NVIC.h"
/* array with size of number of ports of arrays with size of number of pins of pointers to functions */
void  (*Port_CallBack[NUM_OF_PORTS][PORT_NUM_OF_PINS])(uint8 Port,uint8 Pin);

static inline void Port_ISR(volatile uint32 * Port_BaseAddress, uint8 Port)
{
  volatile  uint32 Interrupt_Status;
      uint8 Pin=0;
      Interrupt_Status = (*((volatile uint32 *)((volatile uint8 *)Port_BaseAddress + GPIOMIS_REG_OFFSET))) &\
              PORT_INTERRUPT_STATUS_MASK;
     for(;Pin <= PORT_NUM_OF_PINS; Pin++)
      {
         if (Interrupt_Status & (1<<Pin))
         {
             if(Port_CallBack[Port][Pin] != Null)
             {
                 Port_CallBack[Port][Pin](Port,Pin);
                 SET_BIT((*((volatile uint32 *)((volatile uint8 *)Port_BaseAddress + GPIOICR_REG_OFFSET))),Pin);
             }
         }
      }

}

void PortA_ISR(void)
{

    Port_ISR(PORT_A_REGISTERS_BASE_ADDRESS,PORT_A_ID);


}
void PortB_ISR(void)
{
    Port_ISR(PORT_B_REGISTERS_BASE_ADDRESS,PORT_B_ID);
}
void PortC_ISR(void)
{

    Port_ISR(PORT_C_REGISTERS_BASE_ADDRESS,PORT_C_ID);
}
void PortD_ISR(void)
{
    Port_ISR(PORT_D_REGISTERS_BASE_ADDRESS,PORT_D_ID);
}
void PortE_ISR(void)
{
    Port_ISR(PORT_E_REGISTERS_BASE_ADDRESS,PORT_E_ID);
}
void PortF_ISR(void)
{
    Port_ISR(PORT_F_REGISTERS_BASE_ADDRESS,PORT_F_ID);
}
static inline volatile uint32* Get_Port_BaseAddress(
        uint8 Port
)
{ /* function to get the base address of the required   port */
    volatile uint32 * Port_BaseAddress = Null ;
    switch (Port)
    {
    case PORT_A_ID: Port_BaseAddress = PORT_A_REGISTERS_BASE_ADDRESS;
    break;
    case PORT_B_ID: Port_BaseAddress = PORT_B_REGISTERS_BASE_ADDRESS;
    break;
    case PORT_C_ID: Port_BaseAddress = PORT_C_REGISTERS_BASE_ADDRESS;
    break;
    case PORT_D_ID: Port_BaseAddress = PORT_D_REGISTERS_BASE_ADDRESS;
    break;
    case PORT_E_ID: Port_BaseAddress = PORT_E_REGISTERS_BASE_ADDRESS;
    break;
    case PORT_F_ID: Port_BaseAddress = PORT_F_REGISTERS_BASE_ADDRESS;
    }
    return Port_BaseAddress;
}

static inline NVIC_IRQType Port_GetPort_IRQ_num(uint8 Port)
{
    NVIC_IRQType Port_IRQ_num;
    switch(Port)
    {
    case PORT_A_ID: Port_IRQ_num = PORT_A_IRQ_NUM;
    break;
    case PORT_B_ID: Port_IRQ_num = PORT_B_IRQ_NUM;
    break;
    case PORT_C_ID: Port_IRQ_num = PORT_C_IRQ_NUM;
    break;
    case PORT_D_ID: Port_IRQ_num = PORT_D_IRQ_NUM;
    break;
    case PORT_E_ID: Port_IRQ_num = PORT_E_IRQ_NUM;
    break;
    case PORT_F_ID: Port_IRQ_num = PORT_F_IRQ_NUM;

    }
    return Port_IRQ_num;
}

void Port_Set_CallBack(uint8 Port,uint8 Pin, void(*Ptr)(uint8,uint8))
{
    Port_CallBack[Port][Pin] = Ptr;
}
void Port_init(void)
{
    /* variable to loop over Ports */
    uint8 Port_Count;
    /* variable to loop over Pins */
    uint8 Pin_Count;
    /* enable clock to all ports */
    RCGCGPIO = (RCGCGPIO & ENABLE_CLOCK_ALL_PORTS_CLEAR_MASK) | ENABLE_CLOCK_ALL_PORTS_BITS;
    while (!(PRGPIO & ENABLE_CLOCK_ALL_PORTS_BITS));
    for(Port_Count= PORT_ZERO;Port_Count < NUM_OF_PORTS; Port_Count++)
    {

        for(Pin_Count= PORT_ZERO;Pin_Count<PORT_NUM_OF_PINS;Pin_Count++)
        {
            Port_CallBack[Port_Count][Pin_Count] = Null;
        }
    }
}
void Port_SetPinMode(uint8 Port, uint8 Pin,uint8 Mode)
{
    volatile uint32* Port_BaseAddress = Null;
    /* check if Pin is not a JTAG pin */
    if( (Port == PORT_C_ID) && ((JTAG_CLOCK_PIN == Pin) || (JTAG_MODE_SELECT_PIN == Pin) || (JTAG_DATA_IN_PIN == Pin)\
            || (JTAG_DATA_OUT_PIN == Pin)));

    else
    {
        Port_BaseAddress = Get_Port_BaseAddress(Port);

        if( ((PORTD_LOCKED_PIN == Pin) && (Port == PORT_D_ID)) ||\
                ((PORTF_LOCKED_PIN == Pin) && (Port == PORT_F_ID)))
        {
            /* unlock and commit the required pin */
            PORT_PIN_ENABLE_COMMIT(Port_BaseAddress,Pin);
        }
        /* check the required pin mode and configure alternate function,digital enable,analog mode select  and write the required pin mode in CTL register */
        if(PORT_PIN_GPIO_MODE==Mode)
        {

            CLEAR_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOAFSEL_REG_OFFSET))),Pin);
            WRITE_4_BITS((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOPCTL_REG_OFFSET)))\
                         ,(Pin * PIN_GPIOCTL_BITS_NUM),FOUR_ZERO_BITS);
            SET_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIODEN_REG_OFFSET))),Pin);
            CLEAR_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOAMSEL_REG_OFFSET))),Pin);
        }
        else if(PORT_PIN_ADC_MODE==Mode)
        {
            CLEAR_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOAFSEL_REG_OFFSET))),Pin);
            WRITE_4_BITS((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOPCTL_REG_OFFSET)))\
                         ,(Pin * PIN_GPIOCTL_BITS_NUM),FOUR_ZERO_BITS);
            CLEAR_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIODEN_REG_OFFSET))),Pin);
            SET_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOAMSEL_REG_OFFSET))),Pin);
        }
        else
        {
            SET_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOAFSEL_REG_OFFSET))),Pin);
            WRITE_4_BITS((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOPCTL_REG_OFFSET)))\
                         ,(Pin * PIN_GPIOCTL_BITS_NUM),Mode);
            SET_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIODEN_REG_OFFSET))),Pin);
            CLEAR_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOAMSEL_REG_OFFSET))),Pin);
        }
        if( ((PORTD_LOCKED_PIN == Pin) && (Port == PORT_D_ID)) ||\
                ((PORTF_LOCKED_PIN == Pin) && (Port == PORT_F_ID)))
        {
            /* unlock and disable commit the required pin */
            PORT_PIN_DISABLE_COMMIT(Port_BaseAddress,Pin);
        }
    }
}

void Port_SetPinDirection(uint8 Port, uint8 Pin,uint8 Direction)
{
    volatile uint32* Port_BaseAddress = Null;
    /* check if Pin is not a JTAG pin */
    if( (Port == PORT_C_ID) && ((JTAG_CLOCK_PIN == Pin) || (JTAG_MODE_SELECT_PIN == Pin) || (JTAG_DATA_IN_PIN == Pin)\
            || (JTAG_DATA_OUT_PIN == Pin)));
    else
    {
        Port_BaseAddress = Get_Port_BaseAddress(Port);

        if( ((PORTD_LOCKED_PIN == Pin) && (Port == PORT_D_ID)) ||\
                ((PORTF_LOCKED_PIN == Pin) && (Port == PORT_F_ID)))
        {
            /* unlock and commit the required pin */
            PORT_PIN_ENABLE_COMMIT(Port_BaseAddress,Pin);
        }
        /* configuring pin direction */
        if (PORT_PIN_IN==Direction)
        {


            CLEAR_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress+GPIODIR_REG_OFFSET))),Pin);
        }
        else
        {
            SET_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress+GPIODIR_REG_OFFSET))),Pin);
        }
        if( ((PORTD_LOCKED_PIN == Pin) && (Port == PORT_D_ID)) ||\
                ((PORTF_LOCKED_PIN == Pin) && (Port == PORT_F_ID)))
        {
            /* unlock and disable commit the required pin */
            PORT_PIN_DISABLE_COMMIT(Port_BaseAddress,Pin);
        }
    }
}
void Port_Set_InternalResistance( uint8 Port, uint8 Pin, uint8 Resistance)
{
    volatile uint32* Port_BaseAddress = Null;
    /* check if Pin is not a JTAG pin */
    if( (Port == PORT_C_ID) && ((JTAG_CLOCK_PIN == Pin) || (JTAG_MODE_SELECT_PIN == Pin) || (JTAG_DATA_IN_PIN == Pin)\
            || (JTAG_DATA_OUT_PIN == Pin)));
    else
    {
        Port_BaseAddress = Get_Port_BaseAddress(Port);
        if( ((PORTD_LOCKED_PIN == Pin) && (Port == PORT_D_ID)) ||\
                ((PORTF_LOCKED_PIN == Pin) && (Port == PORT_F_ID)))
        {
            /* unlock and commit the required pin */
            PORT_PIN_ENABLE_COMMIT(Port_BaseAddress,Pin);
        }
        if(INTERNAL_RESISTANCE_OFF == Resistance)
        {

            CLEAR_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOPUR_REG_OFFSET))),Pin);
            CLEAR_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOPDR_REG_OFFSET))),Pin);
        }
        else if(PULL_UP_RESISTANCE == Resistance)
        {
            SET_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOPUR_REG_OFFSET))),Pin);
        }
        else
        {
            SET_BIT((*((volatile uint32*)((volatile uint8*)Port_BaseAddress + GPIOPDR_REG_OFFSET))),Pin);
        }
        if( ((PORTD_LOCKED_PIN == Pin) && (Port == PORT_D_ID)) ||\
                ((PORTF_LOCKED_PIN == Pin) && (Port == PORT_F_ID)))
        {
            /* unlock and disable commit the required pin */
            PORT_PIN_DISABLE_COMMIT(Port_BaseAddress,Pin);
        }
    }
}
void Port_EnablePin_Interrupt(uint8 Port,uint8 Pin,uint8 Trigger)
{
    volatile  uint32* Port_BaseAddress = Null;
    /* check if Pin is not a JTAG pin */
    if( (Port == PORT_C_ID) && ((JTAG_CLOCK_PIN == Pin) || (JTAG_MODE_SELECT_PIN == Pin) || (JTAG_DATA_IN_PIN == Pin)\
            || (JTAG_DATA_OUT_PIN == Pin)));
    else
    {
        /* get base address of the required port */
        Port_BaseAddress = Get_Port_BaseAddress(Port);

        if( ((PORTD_LOCKED_PIN == Pin) && (Port == PORT_D_ID)) ||\
                ((PORTF_LOCKED_PIN == Pin) && (Port == PORT_F_ID)))
        {
            /* unlock and commit the required pin */
            PORT_PIN_ENABLE_COMMIT(Port_BaseAddress,Pin);
        }
        /* check if interrupt is triggered according to an edge  */
        if(Trigger <= PORT_PIN_FALLING_EDGE_INTERRUPT)
        {
            /* interrupt sense edge */
            CLEAR_BIT((*((volatile uint32 *)((volatile uint8 *)Port_BaseAddress + GPIOIS_REG_OFFSET))),Pin);
        }
        /* condition if interrupt is triggered according to level */
        else
        {
            /* interrupt sense level */
            SET_BIT((*((volatile uint32 *)((volatile uint8 *)Port_BaseAddress + GPIOIS_REG_OFFSET))),Pin);
        }

        /* condition if interrupt occur according to both edges */
        if(Trigger == PORT_PIN_BOTH_EDGES_INTERRUPT)
        {
            /* interrupt is triggered on both edges */
            SET_BIT((*((volatile uint32 *)((volatile uint8 *)Port_BaseAddress + GPIOIBE_REG_OFFSET))),Pin);
        }
        /* condition if interrupt occur according to rising edge or high level */
        else  if((Trigger == PORT_PIN_RISING_EDGE_INTERRUPT) || (Trigger == PORT_PIN_HIGH_LEVEL_INTERRUPT))
        {
            /* interrupt is triggered on rising edge or high level according to GPIOIS register */
            SET_BIT((*((volatile uint32 *)((volatile uint8 *)Port_BaseAddress + GPIOIEV_REG_OFFSET))),Pin);
        }
        /* condition if interrupt occur according to rising edge or high level */
        else
        {
            /* interrupt is triggered on rising edge or high level according to GPIOIS register */
            CLEAR_BIT((*((volatile uint32 *)((volatile uint8 *)Port_BaseAddress + GPIOIEV_REG_OFFSET))),Pin);

        }

        /* the required bit generated interrupt will be sent to interrupt controller */
        SET_BIT((*((volatile uint32 *)((volatile uint8 *)Port_BaseAddress + GPIOIM_REG_OFFSET))),Pin);


        NVIC_SetPriorityIRQ(Port_GetPort_IRQ_num(Port),PORT_IRQ_PRIORITY);
        /* enable interrupt for pin port in interrupt controller */
        NVIC_EnableIRQ(Port_GetPort_IRQ_num(Port));

        if( ((PORTD_LOCKED_PIN == Pin) && (Port == PORT_D_ID)) ||\
                ((PORTF_LOCKED_PIN == Pin) && (Port == PORT_F_ID)))
        {
            /* unlock and disable commit the required pin */
            PORT_PIN_DISABLE_COMMIT(Port_BaseAddress,Pin);
        }
    }

}
void Port_Pin_Set_CallBack(uint8 Port,uint8 Pin, void (* ptr)(uint8,uint8))
{
    if((Port < NUM_OF_PORTS) && (Pin < PORT_NUM_OF_PINS))
    {
        Port_CallBack[Port][Pin] = ptr;
    }
}
