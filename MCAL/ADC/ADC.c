/*
 * ADC.c
 *
 *  Created on: Mar 4, 2025
 *      Author: mohamed
 */
#include <ADC.h>
#include"common_macros.h"
#include"NVIC.h"
/* variable that holds the function that will be called in the ISR */
static void ( *ADC_CallBack)(uint8)=Null;
static uint8 Active_Channel;
void ADC_ISR(void)
{
    /* clear IN3 bit (interrupt flag) */
    SET_BIT(ADCISC,IN3_BIT);

    /* check that callback function is initialized */
    if( ADC_CallBack != Null )
    {
        /* call the call back function */
        ADC_CallBack(Active_Channel);
    }
}

void ADC_init(void)
{
    /* enable and provide clock to ADC0 module */
    SET_BIT(RCGCADC,ADC0_CLOCK_ENABLE_BIT);

    /* wait till module is enabled */
    while(BIT_IS_CLEAR(PRADC,ADC0_MODULE_PERIPHERAL_READY_BIT));

    /* disable seqeuncer 3 before initialization */
    CLEAR_BIT(ADCACTSS,ASEN3_bit);

    /* select software trigger for seqeuncer 3 */
    WRITE_4_BITS(ADCEMUX,SS3_TRIGGER_SELECT_START_BIT,SEQEUNCER_SOFTWARE_TRIGGER);

    /* set sample seqeuncer 3 to be non differential , interrupt enabled and using channels */
    WRITE_4_BITS(ADCSSCTL3,ADCSSCTL3_START_BIT,ADCSSCTL3_VALUE);

    /*conversion value to be stored in FIFO */
    CLEAR_BIT(ADCSSOP3,S0DCOP_BIT);

    /* use PIOSC as clock source */
    WRITE_4_BITS(ADCCC,ADC_CLOCK_SOURCE_START_BIT,ADC_PIOSC);

    /* enable interrupt for sample seqeuncer 3 */
    SET_BIT(ADCIM,MASK3_BIT);

    /* enable seqeuncer 3  */
    SET_BIT(ADCACTSS,ASEN3_bit);


    NVIC_SetPriorityIRQ(ADC0_SS3_IRQ_NUM,ADC0_SS3_IRQ_PRIORITY);
    /* enable SS3 interrupt from NVIC */
    NVIC_EnableIRQ(ADC0_SS3_IRQ_NUM);


}

Std_ReturnType ADC_StartConversion(uint8 channel_ID)
{
    /* check if ADC is busy */
    if(BIT_IS_CLEAR(ADCACTSS,ADC_BUSY_BIT))
    {
        /* writing the required channel in sample seqeuncer 3 MUX  */
        WRITE_4_BITS(ADCSSMUX3,ADCSSMUX3_START_BIT,channel_ID);

        /* starting conversion */
        SET_BIT(ADCPSSI,SS3_INIT_BIT);
        Active_Channel = channel_ID;
        return E_OK;
    }
    else
    {
        return E_NOT_OK;
    }
}
uint32 ADC_GetResult(void)
{
    /* check if FIFO is not empty */
if (BIT_IS_CLEAR(ADCSSFSTAT3,ADC_EMPTY_FIFO_BIT))
{
    return (ADCSSFIFO3 & ADC_SIGNAL_MASK);
}
else
{
    return ADC_EMPTY_FIFO;
}
}
void ADC_SetCallBack(void (*CallBack_ptr)(uint8))
{
    /* assigning ADC_CallBack variable with the required callback function address */
    ADC_CallBack = CallBack_ptr;
}

