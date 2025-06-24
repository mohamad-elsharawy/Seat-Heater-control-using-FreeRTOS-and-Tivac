/*
 * Timer0.c
 *
 *  Created on: Jun 10, 2025
 *      Author: mohamed
 */
#include"Timer0.h"
#include"common_macros.h"



void Timer0_init(void)
{
    /* enable clock to timer 0 registers */
    SET_BIT(RCGCTIMER,R0_BIT);

    /* wait till timer registers are ready to be accessed */
    while(BIT_IS_CLEAR(PRTIMER,R0_BIT));

    /* Disable Timer A and B */
    CLEAR_BIT(GPTMCTL,TAEN_BIT);
    CLEAR_BIT(GPTMCTL,TBEN_BIT);

    /* configure timer to be 32 bits */
    WRITE_4_BITS(GPTMCFG,GPTMCFG_START_BIT,TIMER_32_BITS_CONF);

    /* configure timer to be periodic mode */
    GPTMTAMR = (GPTMCFG & TAMR_BITS_MASK) | ((~TAMR_BITS_MASK) &  TIMER_PERIODIC_MODE);

    /* count up mode */
    SET_BIT(GPTMTAMR,TACDIR_BIT);
}

uint32 GetTimer0Ticks(void)
{
    return GPTMTAR;
}
void Timer0Start(void)
{
    /* initialize Timer with zero */
    GPTMTAV = TIMER0_ZERO;

    /* Enable Timer A and B */
    SET_BIT(GPTMCTL,TAEN_BIT);
    SET_BIT(GPTMCTL,TBEN_BIT);

}
void Timer0Stop(void)
{

    /* Disable Timer A and B */
    SET_BIT(GPTMCTL,TAEN_BIT);
    SET_BIT(GPTMCTL,TBEN_BIT);

}

