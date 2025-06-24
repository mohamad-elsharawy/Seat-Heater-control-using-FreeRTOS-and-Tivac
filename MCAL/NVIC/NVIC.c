/*
 * nvic.c
 *
 *  Created on: Nov 29, 2024
 *      Author: mohamed
 */
#include <NVIC.h>
/*********************************************************************
 * Service Name: NVIC_EnableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: non reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{
    uint8 bit_num=0;
    uint8 EN_offset=0;
    /* the reminder of IRQ_Num divided by the number of enables per register
    *enable produce the number of bit of that    IRQ_Num
    */
    bit_num=IRQ_Num % EN_per_reg;
    /* IRQ_Num divided by how many IRQ enable are per register produce the number
     * of enable register for that IRQ_Num ,the output value is multiplied by 4
     * since the register size is 4 bytes to produce the offset of address from enable reg 0
     */
    EN_offset=((IRQ_Num/32)*bytes_num_per_reg);
    /*
     * set the the required bit in the required register to enable the IRQ
     */
    (*(volatile uint32 *)(EN0_address+EN_offset)) |=(1<<bit_num);

}
/*********************************************************************
 * Service Name: NVIC_DisableIRQ
 * Sync/Async: Synchronous
 * Reentrancy:non reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{
    uint8 bit_num=0;
    uint8 DIS_offset=0;
    /* the reminder of IRQ_Num divided by the number of enables per register
     * produce the number of bit of that  IRQ_Num
     */
    bit_num=IRQ_Num%EN_per_reg;
   /* IRQ_Num divided by how many IRQ disable are per register produce the number
    * of enable register for that IRQ_Num ,the output value is multiplied by 4
    * since the register size is 4 bytes to produce the offset of address from disable reg 0
    */
    DIS_offset=((IRQ_Num/EN_per_reg)*bytes_num_per_reg);
    /*
     * clear the the required bit in the required register to disable the IRQ
     */
    (*(volatile uint32 *)(DIS0_address+DIS_offset)) &=(~(1<<bit_num));

}
/*********************************************************************
 * Service Name: NVIC_SetPriorityIRQ
 * Sync/Async: Synchronous
 * Reentrancy:non reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table ,IRQ_Priority -the required priority
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: function to set priority of IRQ
**********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority)
{
    uint8 bit_num=0;
    uint8 PRI_offset=0;
    /*
     * mask the first 3 bits in the input IRQ_priority to make sure it is in the range
     * required and doesn't corrupt any other bit value
     */
    IRQ_Priority=(IRQ_Priority & mask_first_3_bits);
    /* the reminder of IRQ_Num divided by the number of priorities per register
     * produce the number interrupt in priority register of that IRQ_Num
     */
    bit_num=IRQ_Num%PRI_per_reg;
    /*
     *  bit num + 1 *5 to not write in the reserved bits / bit num *3 to skip the previous priority bits
     */
    bit_num=((bit_num+1)*pri_reserved_bits_num)+(bit_num*num_of_pri_bits);
    /* IRQ_Num divided by how many IRQ priority are per register produce the number
      * of priority register for that IRQ_Num ,the output value is multiplied by 4
      * since the register size is 4 bytes to produce the offset of address from priority reg 0
      */
    PRI_offset=((IRQ_Num/PRI_per_reg)*bytes_num_per_reg);
    /*
     * clear the priority bits
     */
    (*(volatile uint32 *)(PRI0_address+PRI_offset))=(*(volatile uint32 *)(PRI0_address+PRI_offset))&(ones_32_bits&(clear_first_3_bits_mask<<bit_num));
     /*
      * write the required priority bits
      */
    (*(volatile uint32 *)(PRI0_address+PRI_offset)) =(*(volatile uint32 *)(PRI0_address+PRI_offset))|(IRQ_Priority<<bit_num);
}
/*********************************************************************
 * Service Name: NVIC_EnableException
 * Sync/Async: Synchronous
 * Reentrancy:non reentrant
 * Parameters (in): Exception_Num - Number of the Exception from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable Interrupt request for specific Exceptions
**********************************************************************/
void NVIC_EnableException(NVIC_ExceptionType Exception_Num)
{
    switch(Exception_Num)
    {
    case MEM_FAULT_EXCEPTION_NUM:SYSHNDCTRL|=MEM_FAULT_ENABLE_MASK;
    break;
    case BUS_FAULT_EXCEPTION_NUM:SYSHNDCTRL|=BUS_FAULT_ENABLE_MASK;
    break;
    case USAGE_FAULT_EXCEPTION_NUM:SYSHNDCTRL|=USAGE_FAULT_ENABLE_MASK;

    }
}
/*********************************************************************
 * Service Name: NVIC_DisableException
 * Sync/Async: Synchronous
 * Reentrancy:non reentrant
 * Parameters (in): Exception_Num - Number of the Exception from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable Interrupt request for specific Exception
**********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{
    switch(Exception_Num)
       {
       case MEM_FAULT_EXCEPTION_NUM:SYSHNDCTRL&=~MEM_FAULT_ENABLE_MASK;
       break;
       case BUS_FAULT_EXCEPTION_NUM:SYSHNDCTRL&=~BUS_FAULT_ENABLE_MASK;
       break;
       case USAGE_FAULT_EXCEPTION_NUM:SYSHNDCTRL&=~USAGE_FAULT_ENABLE_MASK;

       }
}
/*********************************************************************
 * Service Name: NVIC_SetPriorityException
 * Sync/Async: Synchronous
 * Reentrancy:non reentrant
 * Parameters (in): Exception_Num - Number of the Exception from the target vector table Exception_Priority - the required priority
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set Exception_Priority
**********************************************************************/
void NVIC_SetPriorityException(uint8 Exception_Num,uint8 Exception_Priority)
{
    uint8 bit_num=0;
    uint8 PRI_offset=0;
    /*
     * mask the first 3 bits in the input Exception_priority to make sure it is in the range
     * required and doesn't corrupt any other bit value
     */
    Exception_Priority=(Exception_Priority & mask_first_3_bits);
    /*
     * subtract the nums of non programmable exceptions since priorities are sorted
     * in register from the first programmable register
     */
    Exception_Num=Exception_Num-first_programmable_sys_exception_num;
    /* the reminder of Exception_Num divided by the number of priorities per register
     * produce the number Exception in priority register of that Exception_Num
     */
    bit_num=Exception_Num%PRI_per_reg;
    /*
     *  bit num + 1 *5 to not write in the reserved bits / bit num *3 to skip the previous exceptions bits
     */
    bit_num=((bit_num+1)*pri_reserved_bits_num)+(bit_num*num_of_pri_bits);
      /* Exception_Num divided by how many Exception priority are per register produce the number
       * of priority register for that Exception_Num ,the output value is multiplied by 4
       * since the register size is 4 bytes to produce the offset of address from priority reg 0
       */
    PRI_offset=((Exception_Num/PRI_per_reg)*bytes_num_per_reg);
    /*
     * clear the priority bits
     */
    (*(volatile uint32 *)(SYSPRI1_address+PRI_offset))=(*(volatile uint32 *)(SYSPRI1_address+PRI_offset))&(ones_32_bits&(clear_first_3_bits_mask<<bit_num));
    /*
     * write the required priority bits
     */
    (*(volatile uint32 *)(SYSPRI1_address+PRI_offset)) =(*(volatile uint32 *)(SYSPRI1_address+PRI_offset))|(Exception_Priority<<bit_num);
}

