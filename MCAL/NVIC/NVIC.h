/*
 * nvic.h
 *
 *  Created on: Nov 29, 2024
 *      Author: mohamed
 */

#ifndef NVIC_H_
#define NVIC_H_
/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include"std_types.h"
/*******************************************************************************
 *                           Preprocessor Definitions                          *
 *******************************************************************************/
#define EN0_address 0xE000E100
#define DIS0_address 0xE000E180
#define PRI0_address 0xE000E400
#define SYSPRI1_address 0xE000ED18
#define EN_per_reg 32
#define PRI_per_reg 4
#define mask_first_3_bits 0x07
#define clear_first_3_bits_mask 0x00000008
#define ones_32_bits 0xFFFFFFFF
#define bytes_num_per_reg 4
#define first_programmable_sys_exception_num 4
#define pri_reserved_bits_num 5
#define num_of_pri_bits 3
#define MEM_FAULT_PRIORITY_MASK              0x000000E0
#define MEM_FAULT_PRIORITY_BITS_POS          5

#define BUS_FAULT_PRIORITY_MASK              0x0000E000
#define BUS_FAULT_PRIORITY_BITS_POS          13

#define USAGE_FAULT_PRIORITY_MASK            0x00E00000
#define USAGE_FAULT_PRIORITY_BITS_POS        21

#define SVC_PRIORITY_MASK                    0xE0000000
#define SVC_PRIORITY_BITS_POS                29

#define DEBUG_MONITOR_PRIORITY_MASK          0x000000E0
#define DEBUG_MONITOR_PRIORITY_BITS_POS      5

#define PENDSV_PRIORITY_MASK                 0x00E00000
#define PENDSV_PRIORITY_BITS_POS             21

#define SYSTICK_PRIORITY_MASK                0xE0000000
#define SYSTICK_PRIORITY_BITS_POS            29

#define MEM_FAULT_ENABLE_MASK                0x00010000
#define BUS_FAULT_ENABLE_MASK                0x00020000
#define USAGE_FAULT_ENABLE_MASK              0x00040000

#define MEM_FAULT_EXCEPTION_NUM                4
#define BUS_FAULT_EXCEPTION_NUM                5
#define USAGE_FAULT_EXCEPTION_NUM              6

#define SYSHNDCTRL (*((volatile uint32 *)(0xE000E000+0xD24)))
/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmable Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm(" CPSIE I ")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmable Systems Exceptions and Faults by setting the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm(" CPSID I ")

/* Enable Faults ... This Macro enable Faults by clearing the F-bit in the FAULTMASK */
#define Enable_Faults()        __asm(" CPSIE F ")

/* Disable Faults ... This Macro disable Faults by setting the F-bit in the FAULTMASK */
#define Disable_Faults()       __asm(" CPSID F ")

/*******************************************************************************
 *                           Data Types Declarations                           *
 *******************************************************************************/
typedef uint8 NVIC_IRQType;

typedef uint8 NVIC_IRQPriorityType;

typedef enum
{
    EXCEPTION_RESET_TYPE=1,
    EXCEPTION_NMI_TYPE,
    EXCEPTION_HARD_FAULT_TYPE,
    EXCEPTION_MEM_FAULT_TYPE,
    EXCEPTION_BUS_FAULT_TYPE,
    EXCEPTION_USAGE_FAULT_TYPE,
    EXCEPTION_SVC_TYPE=11,
    EXCEPTION_DEBUG_MONITOR_TYPE,
    EXCEPTION_PEND_SV_TYPE=14,
    EXCEPTION_SYSTICK_TYPE
}NVIC_ExceptionType;

typedef uint8 NVIC_ExceptionPriorityType;
/************************************************************************************
 *  Functions prototypes
 ************************************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num);
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num);
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority);
void NVIC_EnableException(NVIC_ExceptionType Exception_Num);
void NVIC_DisableException(NVIC_ExceptionType Exception_Num);
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority);
/************************************************************************************
 *                                 End of File                                      *
 ************************************************************************************/
#endif /* NVIC_H_ */
