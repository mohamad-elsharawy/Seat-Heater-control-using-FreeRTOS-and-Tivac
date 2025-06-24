/*
 * Application_PBcfg.c
 *
 *  Created on: Jun 22, 2025
 *      Author: mohamed
 */
#include"Application.h"
#include"Led_cfg.h"
#include"PushButton.cfg.h"
#include"Temperature_Sensor_LM35.h"

/*array containing all seats seat_type */
Seat_type Seats[NUMBER_OF_SEATS] ={{.HeaterMode = Off,.LowIntensityLed_ID = SEAT0_LOW_INTENISTY_LED_ID, .MediumIntensityLed_ID = SEAT0_HIGH_INTENISTY_LED_ID, .HighIntensityLed_ID = SEAT0_MEDIUM_INTENISTY_LED_ID, .LM35TempSensor_ID = LM35_TEMPSENSOR_SEAT0_ID, .ButtonOne_ID = SEAT0_BUTTON1_ID ,.ButtonTwo_ID = SEAT0_BUTTON2_ID}};
