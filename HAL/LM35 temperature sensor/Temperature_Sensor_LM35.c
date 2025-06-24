/*
 * Temperature_Sensor_LM35.c
 *
 *  Created on: May 17, 2025
 *      Author: mohamed
 */

#include <ADC.h>
#include <Temperature_Sensor_LM35.h>

void LM35TempSensor_init(void)
{


}
void LM35TempSensor_Start(uint8 Channel)
{
    ADC_StartConversion(Channel);
}
uint32 Get_LM35TempSensor_Value(void)
{
    uint32 result;
   /* convert ADC value to Celsius */
    result = (ADC_GetResult() * (ADC_VREF_MILIVOLT/LM35_SENSOR_SENSITIVITY_MV_PER_C))/ADC_RESULOTION;
    return result;
}
void Set_LM35TempSensor_CallBack(void (*ptr)(uint8))
{
    ADC_SetCallBack(ptr);
}
