/*
 * PushButton_internal.h
 *
 *  Created on: Apr 30, 2025
 *      Author: mohamed
 */

#ifndef HAL_PUSHBUTTON_INTERNAL_H_
#define HAL_PUSHBUTTON_INTERNAL_H_
/* includes */
#include <Pushbutton.h>
#include"Port.h"

/* preprocesor definitions */

#define BUTTON_UNPRESSED (0U)
#define BUTTON_PRESSED (1U)
#define BUTTON_ZERO (0U)
/* types */
typedef struct{
 uint8 port;
 uint8 pin;
 uint8 status;
#if (PUSH_BUTTON_CALLBACK_CONFIG == CALLBACK_PER_PIN)
 void (* Callback_ptr)(uint8 Button_ID);
#endif
}Button_type;

/* variables extern */
extern Button_type buttons[NUMBER_OF_BUTTONS];


#endif /* HAL_PUSHBUTTON_INTERNAL_H_ */
