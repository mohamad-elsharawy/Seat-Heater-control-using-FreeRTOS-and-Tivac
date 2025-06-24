/*
 * Led.h
 *
 *  Created on: May 17, 2025
 *      Author: mohamed
 */

#ifndef HAL_LED_H_
#define HAL_LED_H_

/**************************************************
 * Includes
 ***************************************************/
#include <Led_cfg.h>
#include"std_types.h"

/****************************************************
 * Data types
 ****************************************************/
typedef struct
{
    uint8 LedPort;
    uint8 LedPin;
}LedType;

/*****************************************************************
 * Functions Prototypes
 *****************************************************************/
void Led_init(void);
void Led_on(uint8 LedChannel);
void Led_off(uint8 LedChannel);
#endif /* HAL_LED_H_ */
