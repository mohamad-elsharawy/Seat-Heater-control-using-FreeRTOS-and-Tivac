/*
 * PushButton.cfg.h
 *
 *  Created on: May 2, 2025
 *      Author: moham
 */

#ifndef HAL_PUSHBUTTON_CFG_H_
#define HAL_PUSHBUTTON_CFG_H_

/*static Configurations */

/* defining seat buttons ID */
#define SEAT0_BUTTON1_ID (0U)
#define SEAT0_BUTTON2_ID (1U)
/* configure number of buttons */
#define NUMBER_OF_BUTTONS (2U)

/*configure either that all buttons have same callback function
 * noting that pushbutton driver pass button ID to callback function
 * or configure that each pin has separate call back
 * for single call back write GENERAL_CALLBACK
 * and for callback for each button write CALLBACK_PER_PIN
 */
#define PUSH_BUTTON_CALLBACK_CONFIG GENERAL_CALLBACK



#endif /* HAL_PUSHBUTTON_CFG_H_ */
