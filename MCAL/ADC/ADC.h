/*
 * ADC.h
 *
 *  Created on: Mar 4, 2025
 *      Author: mohamed
 */

#ifndef ADC_H_
#define ADC_H_

#include"std_types.h"
/********************************************************************
 *  ADC registers and bits
 ********************************************************************/
#define RCGCADC  (*((volatile uint32*)0x400FE638))
#define ADC0_CLOCK_ENABLE_BIT (0U)
#define ADC0_BASE (0x40038000)
#define PRADC (*((volatile uint32*)0x400FEA38))
#define ADC0_MODULE_PERIPHERAL_READY_BIT (0U)
#define ADCACTSS (*((volatile uint32*)0x40038000))
#define ADC_BUSY_BIT (16U)
#define ASEN3_bit (3U)
#define ADCEMUX (*((volatile uint32*)0x40038014))
#define ADCSSCTL3 (*((volatile uint32*)0x400380A4))
#define ADCIM (*((volatile uint32*)0x40038008))
#define MASK3_BIT (3U)
#define ADCSSMUX3 (*((volatile uint32*)0x400380A0))
#define ADCPSSI (*((volatile uint32*)0x40038028))
#define SS3_INIT_BIT (3U)
#define ADCISC (*((volatile uint32*)0x4003800C))
#define IN3_BIT (3U)
#define ADCSSFIFO3 (*((volatile uint32*)0x400380A8))
#define ADCSSFSTAT3 (*((volatile uint32*)0x400380AC))
#define ADC_EMPTY_FIFO_BIT (8U)
#define ADCSSOP3 (*((volatile uint32*)0x400380B0))
#define S0DCOP_BIT (0U)
#define ADCCC (*((volatile uint32*)0x40038FC8))
#define ADC_CLOCK_SOURCE_START_BIT (0U)
/*********************************************************************
 * preprocessor Macros
 *********************************************************************/
#define ADC0_SS3_IRQ_PRIORITY 5
#define ADC_ZERO (0U)
#define SEQEUNCER_SOFTWARE_TRIGGER (0x0)
#define SS3_TRIGGER_SELECT_START_BIT (12U)
#define ADCSSCTL3_VALUE (0x6)
#define ADCSSCTL3_START_BIT (0U)
#define ADCSSMUX3_START_BIT (0U)
#define AIN0 (0U)
#define AIN1 (1U)
#define AIN2 (2U)
#define AIN3 (3U)
#define AIN4 (4U)
#define AIN5 (5U)
#define AIN6 (6U)
#define AIN7 (7U)
#define AIN8 (8U)
#define ADC_SIGNAL_MASK (0x00000FFF)
#define ADC_EMPTY_FIFO (0x80000000)
#define ADC_PIOSC (0x1)
#define ADC0_SS3_IRQ_NUM (17U)
#define ADC_RESULOTION (4096U)
#define ADC_VREF_MILIVOLT (3300U)
/********************************************************************
 * Functions prototypes
 ********************************************************************/

void ADC_init(void);

Std_ReturnType ADC_StartConversion(uint8 channel_ID);

uint32 ADC_GetResult(void);

void ADC_SetCallBack(void (*CallBack_ptr)(uint8));

#endif /* ADC_H_ */
