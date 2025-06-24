/*
 * Pushbutton.h
 *
 *  Created on: Apr 23, 2025
 *      Author: moham
 */

#ifndef HAL_PUSHBUTTON_H_
#define HAL_PUSHBUTTON_H_
#include"std_types.h"

#define CALLBACK_PER_PIN (0U)
#define GENERAL_CALLBACK (1U)

#include<PushButton.cfg.h>

/* Functions prototypes */
void PushButton_init(void);
void Set_PushButton_CallBack(void (* ptr)(uint8 Button_ID),uint8 Button_ID);
void PushButton_Press_Handle(uint8 Port,uint8 Pin);
#endif /* HAL_PUSHBUTTON_H_ */
