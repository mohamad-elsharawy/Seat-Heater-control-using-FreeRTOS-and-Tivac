/*
 * Terminal_Display.h
 *
 *  Created on: May 26, 2025
 *      Author: moham
 */

#ifndef HAL_TERMINAL_DISPLAY_H_
#define HAL_TERMINAL_DISPLAY_H_
/*******************************************************
 * includes
 *******************************************************/
#include"std_types.h"
/******************************************************
 * Functions Prototypes
 ****************************************************/
void TerminalDisplayNum(uint32 num);
void TerminalDisplayString(uint8* string_ptr);
void TerminalDisplay_NewLine(void);
#endif /* HAL_TERMINAL_DISPLAY_H_ */
