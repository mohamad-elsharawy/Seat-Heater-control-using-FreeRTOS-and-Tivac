/*
 * Temperature_Sensor_LM35.h
 *
 *  Created on: May 17, 2025
 *      Author: moham
 */

#ifndef HAL_TEMPERATURE_SENSOR_LM35_H_
#define HAL_TEMPERATURE_SENSOR_LM35_H_

/*********************************************************************
 * Includes
 *********************************************************************/
#include"std_types.h"

/*********************************************************************
 * Preprocessor Macros
 *********************************************************************/
#define LM35_TEMPSENSOR_SEAT0_ID (0U)
#define LM35_SENSOR_SENSITIVITY_MV_PER_C (10U)
/***********************************************************************
 * Functions prototypes
 ***********************************************************************/
void LM35TempSensor_init(void);
void LM35TempSensor_Start(uint8 Channel);
uint32 Get_LM35TempSensor_Value(void);
void Set_LM35TempSensor_CallBack(void (*ptr)(uint8));
#endif /* HAL_TEMPERATURE_SENSOR_LM35_H_ */
