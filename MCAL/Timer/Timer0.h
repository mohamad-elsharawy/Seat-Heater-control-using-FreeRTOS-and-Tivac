/*
 * Timer0.h
 *
 *  Created on: Jun 10, 2025
 *      Author: mohamed
 */

#ifndef TIMER0_H_
#define TIMER0_H_


/***********************************************************
 * Includes
 ************************************************************/
#include"std_types.h"
/************************************************************
 * Registers and Bits
 ************************************************************/
#define RCGCTIMER (*((volatile uint32 *) 0x400FE604))
#define R0_BIT (0U)
#define PRTIMER (*((volatile uint32 *) 0x400FEA04))
#define GPTMCTL (*((volatile uint32 *) 0x4003000C))
#define TAEN_BIT (0U)
#define TBEN_BIT (1U)
#define GPTMCFG (*((volatile uint32 *) 0x40030000))
#define GPTMCFG_START_BIT (0U)
#define GPTMTAMR (*((volatile uint32 *) 0x40030004))
#define TACDIR_BIT (4U)
#define TAMR_BITS_MASK ((uint32)(0xFFFFFFFC))
#define GPTMTAR (*((volatile uint32 *) 0x40030048))
#define GPTMTAV (*((volatile uint32 *) 0x40030050))
/*************************************************************
 * Preprocessor Macros
 *************************************************************/
#define TIMER_32_BITS_CONF (0U)
#define TIMER_PERIODIC_MODE (2U)
#define TIMER0_ZERO (0U)
#define TIMER0_TICKS_TO_MS(TICKS) ((TICKS) / (16000U))
/*************************************************************
 * Functions Prototypes
 *************************************************************/
void Timer0_init(void);
uint32 GetTimer0Ticks(void);
void Timer0Start(void);
void Timer0Stop(void);
#endif /* TIMER0_H_ */
