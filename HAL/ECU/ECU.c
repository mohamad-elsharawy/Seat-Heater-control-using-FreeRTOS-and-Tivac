/*
 * ECU.c
 *
 *  Created on: may 22, 2025
 *      Author: mohamed
 */
#include"MCU.h"
#include"ECU.h"
#include"Led.h"
#include"Temperature_Sensor_LM35.h"
#include"PushButton.h"
#include"Terminal_Display.h"

void ECU_init(void)
{
    MCU_init();
    LM35TempSensor_init();
    PushButton_init();
    Led_init();
}

