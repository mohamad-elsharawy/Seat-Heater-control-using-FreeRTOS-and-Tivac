/*
 * Application.h
 *
 *  Created on: Jun 22, 2025
 *      Author: moham
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_
/*******************************************************
 * includes
 *******************************************************/
#include"std_types.h"
#include"Application_cfg.h"
/********************************************************
 * Preprocessor Macros
 *********************************************************/


#define NUMBER_OF_TASKS (6U)


/* tasks tags */
#define LM35TEMPSENSOR_STARTCONVERSION_TASK_TAG     (1U)
#define UPDATESEATTEMP_TASK_TAG                     (2U)
#define UPDATESEATBUTTON_TASK_TAG                   (3U)
#define SEATCONTROL_TASK_TAG                        (4U)
#define DISPLAY_TASK_TAG                            (5U)

/* tasks priority */
#define LM35_TEMP_SENSOR_START_CONVERSION_TASK_PRIORITY     (3U)
#define UPDATE_SEAT_TEMP_TASK_PRIORITY                      (4U)
#define UPDATE_SEAT_BUTTON_TASK_PRIORITY                    (4U)
#define SEAT_CONTROL_TASK_PRIORITY                          (3U)
#define DISPLAY_TASK_PRIORITY                               (2U)
#define RUN_TIME_MEASURMENTS_TASK_PRIORITY                  (1U)

/* tasks stack size */
#define LM35_TEMP_SENSOR_START_CONVERSION_TASK_STACK_WORDS     (256U)
#define UPDATE_SEAT_TEMP_TASK_STACK_WORDS                      (256U)
#define UPDATE_SEAT_BUTTON_TASK_STACK_WORDS                    (256U)
#define SEAT_CONTROL_TASK_STACK_WORDS                          (256U)
#define DISPLAY_TASK_STACK_WORDS                               (256U)
#define RUN_TIME_MEASURMENTS_TASK_STACK_WORDS                  (256U)



/***************************************************
 * Data types
 ***************************************************/
typedef enum
{
    Off,Low,Medium,High
}SeatHeater_Modes;

/* seat structure that holds all seat info */
typedef struct
{
    uint32 Temp;
    SeatHeater_Modes HeaterMode;
    uint8 LowIntensityLed_ID;
    uint8 MediumIntensityLed_ID;
    uint8 HighIntensityLed_ID;
    uint8 LM35TempSensor_ID;
    uint8 ButtonOne_ID;
    uint8 ButtonTwo_ID;

}Seat_type;

/*****************************************************
 * Functions prototypes
 *****************************************************/
void Application_init(void);
void SeatControlTask(void * pvParameters);
void UpdateSeatButtonTask(void * pvParameters);
void UpdateSeatTempTask(void * pvParameters);
void LM35TempSensor_StartConversion_Task(void * pvParameters);
void DisplayTask(void * pvParameters);
void ButtonCallBack(uint8 Button_ID);
void TempSensor_Callback(uint8 TempSensor_ID);

#if(RUN_TIME_MEASURMENT_TASK_ENABLE == APPLICATION_TASK_ON)
void RunTimeMeasurmentsTask(void * pvParameters);
#endif

#endif /* APPLICATION_H_ */
