/*
 * Application.c
 *
 *  Created on: Jun 22, 2025
 *      Author: mohamed
 */
#include"Application.h"
#include"Led.h"
#include"Temperature_Sensor_LM35.h"
#include"PushButton.h"
#include"Terminal_Display.h"
#include"FreeRTOS.h"
#include"task.h"
#include"queue.h"
#include"semphr.h"

/* defining handles of Semaphores,Mutex,Queues and tasks */
xSemaphoreHandle ADC_Semaphore;
xSemaphoreHandle UART_Mutex;
QueueHandle_t ButtonQueue;
QueueHandle_t TempSensorQueue;
QueueHandle_t ReevaluateQueue;
TaskHandle_t xLM35TempSensor_StartConversion_TaskHandle;
TaskHandle_t xUpdateSeatTempTaskHandle;
TaskHandle_t xUpdateSeatButtonTaskHandle;
TaskHandle_t xSeatControlTaskHandle;
TaskHandle_t xDisplayTaskHandle;

/* variables to hold values of task in and out time stamps */
#if(RUN_TIME_MEASURMENT_TASK_ENABLE == APPLICATION_TASK_ON)
uint32 TotalTasksTicks = 0;
uint32 TaskInTimeStamp[NUMBER_OF_TASKS];
uint32 TaskOutTimeStamp[NUMBER_OF_TASKS];
uint32 TaskExcutionTicksNum[NUMBER_OF_TASKS];
#endif
/* external variables*/
extern Seat_type Seats[];

/***********************************************************
 * Function that initialize application and create FreeRTOS objects
 *************************************************************/
void Application_init(void)
{
    /* set callback */
    Set_PushButton_CallBack(ButtonCallBack,GENERAL_CALLBACK);
    Set_LM35TempSensor_CallBack(TempSensor_Callback);
    /* Tasks creation */
    xTaskCreate(LM35TempSensor_StartConversion_Task,Null,LM35_TEMP_SENSOR_START_CONVERSION_TASK_STACK_WORDS,Null,LM35_TEMP_SENSOR_START_CONVERSION_TASK_PRIORITY,&xLM35TempSensor_StartConversion_TaskHandle);
    xTaskCreate(UpdateSeatTempTask,Null,UPDATE_SEAT_TEMP_TASK_STACK_WORDS,Null,UPDATE_SEAT_TEMP_TASK_PRIORITY,&xUpdateSeatTempTaskHandle);
    xTaskCreate(UpdateSeatButtonTask,Null,UPDATE_SEAT_BUTTON_TASK_STACK_WORDS,Null,UPDATE_SEAT_BUTTON_TASK_PRIORITY,&xUpdateSeatButtonTaskHandle);
    xTaskCreate(SeatControlTask,Null,SEAT_CONTROL_TASK_STACK_WORDS,Null,SEAT_CONTROL_TASK_PRIORITY,&xSeatControlTaskHandle);
    xTaskCreate(DisplayTask,Null,DISPLAY_TASK_STACK_WORDS,Null,DISPLAY_TASK_PRIORITY,&xDisplayTaskHandle);
#if(RUN_TIME_MEASURMENT_TASK_ENABLE == APPLICATION_TASK_ON)
    xTaskCreate(RunTimeMeasurmentsTask,Null,RUN_TIME_MEASURMENTS_TASK_STACK_WORDS,Null,RUN_TIME_MEASURMENTS_TASK_PRIORITY,Null);
#endif
    /* attaching Tags to Tasks to differentiate tasks when trace hook macros are used*/
    vTaskSetApplicationTaskTag(xLM35TempSensor_StartConversion_TaskHandle,( TaskHookFunction_t )LM35TEMPSENSOR_STARTCONVERSION_TASK_TAG);
    vTaskSetApplicationTaskTag(xUpdateSeatTempTaskHandle,( TaskHookFunction_t )UPDATESEATTEMP_TASK_TAG);
    vTaskSetApplicationTaskTag(xUpdateSeatButtonTaskHandle,( TaskHookFunction_t )UPDATESEATBUTTON_TASK_TAG);
    vTaskSetApplicationTaskTag(xSeatControlTaskHandle,( TaskHookFunction_t )SEATCONTROL_TASK_TAG);
    vTaskSetApplicationTaskTag(xDisplayTaskHandle,( TaskHookFunction_t )DISPLAY_TASK_TAG);

    /* creating semaphores and mutex */
    UART_Mutex = xSemaphoreCreateMutex();
    ADC_Semaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(ADC_Semaphore);

    /* creating queues */
    ButtonQueue = xQueueCreate(8,sizeof(uint8));
    TempSensorQueue = xQueueCreate(2,sizeof(uint8));
    ReevaluateQueue = xQueueCreate(8,sizeof(uint8));

}


/*****************************************************************************************
 * Task that woken when either seat temp or heater mode is update to update heater intensity
 ******************************************************************************************/
void SeatControlTask(void * pvParameters)
{
    uint8 Seat_ID;
    uint32 Required_temp;
    uint32 Temp_difference;
    for(;;)
    {
        xQueueReceive(ReevaluateQueue,&Seat_ID,portMAX_DELAY);

        /* setting required temperature based on heater mode */
        switch(Seats[Seat_ID].HeaterMode)
        {
        case Low: Required_temp = SEAT_HEATER_LOW_TEMP;
        break;
        case Medium: Required_temp = SEAT_HEATER_MEDIUM_TEMP;
        break;
        case High: Required_temp = SEAT_HEATER_HIGH_TEMP;
        }

        /* check if mode is off or seat has higher temperature than required to  turn heaters off */
        if((Off == Seats[Seat_ID].HeaterMode) || (Seats[Seat_ID].Temp >= Required_temp))
        {
            Led_off(Seats[Seat_ID].HighIntensityLed_ID);
            Led_off(Seats[Seat_ID].MediumIntensityLed_ID);
            Led_off(Seats[Seat_ID].LowIntensityLed_ID);
        }
        else
        {
            /* if temp in range calculate temp difference between current temp and required and turn on the required heater level */
            Temp_difference = Required_temp - Seats[Seat_ID].Temp;
            if(SEAT_HEATER_HIGH_INTENSITY_TEMP_MARGIN <= Temp_difference)
            {
                Led_on(Seats[Seat_ID].HighIntensityLed_ID);
                Led_off(Seats[Seat_ID].MediumIntensityLed_ID);
                Led_off(Seats[Seat_ID].LowIntensityLed_ID);
            }
            else if((SEAT_HEATER_MEDIUM_INTENSITY_TEMP_MARGIN <= Temp_difference) && (Temp_difference < SEAT_HEATER_HIGH_INTENSITY_TEMP_MARGIN) )
            {
                Led_off(Seats[Seat_ID].HighIntensityLed_ID);
                Led_on(Seats[Seat_ID].MediumIntensityLed_ID);
                Led_off(Seats[Seat_ID].LowIntensityLed_ID);
            }
            else if((SEAT_HEATER_LOW_INTENSITY_TEMP_MARGIN <= Temp_difference) && (Temp_difference < SEAT_HEATER_MEDIUM_INTENSITY_TEMP_MARGIN))
            {
                Led_off(Seats[Seat_ID].HighIntensityLed_ID);
                Led_off(Seats[Seat_ID].MediumIntensityLed_ID);
                Led_on(Seats[Seat_ID].LowIntensityLed_ID);
            }
            else
            {
                Led_off(Seats[Seat_ID].HighIntensityLed_ID);
                Led_off(Seats[Seat_ID].MediumIntensityLed_ID);
                Led_off(Seats[Seat_ID].LowIntensityLed_ID);

            }
        }

    }
}





/********************************************************************************************************
 *  Task that is woken when a pressed button ID is sent by queue and updates the equivalent seat heater mode
 *   and send seat ID to seat control task by queue
 ********************************************************************************************************/
void UpdateSeatButtonTask(void * pvParameters)
{
    uint8 Button_ID;
    uint8 Seat_ID;
    for(;;)
    {
        /* receive the ID of pressed button */
        xQueueReceive(ButtonQueue,&Button_ID,portMAX_DELAY);

        /* search for the seat that the pressed button belong to */
        for(Seat_ID = SEAT_ONE_ID;Seat_ID < NUMBER_OF_SEATS; Seat_ID++)
        {
            /* update mode based on button press */
            if((Button_ID == Seats[Seat_ID].ButtonOne_ID) || (Button_ID == Seats[Seat_ID].ButtonTwo_ID))
            {
                if(High == Seats[Seat_ID].HeaterMode )
                {
                    Seats[Seat_ID].HeaterMode = Off;
                }
                else
                {
                    Seats[Seat_ID].HeaterMode++;
                }
                xQueueSend(ReevaluateQueue,&Seat_ID,portMAX_DELAY);
            }


        }
    }
}

/********************************************************************************************************
 *  Task that is woken when there is a ready sensor ID sent by queue and updates the equivalent seat temp
 *  and send seat ID to seat control task by queue
 ********************************************************************************************************/
void UpdateSeatTempTask(void * pvParameters)
{
    uint8 Seat_ID;
    uint8 TempSensor_ID;
    for(;;)
    {
        /* receive The ID of the ready lm35 sensor */
        xQueueReceive(TempSensorQueue,&TempSensor_ID,portMAX_DELAY);

        /* loop to search the seat that the lm35 sensor belong to */
        for(Seat_ID = SEAT_ONE_ID;Seat_ID < NUMBER_OF_SEATS; Seat_ID++)
        {
            if(TempSensor_ID == Seats[Seat_ID].LM35TempSensor_ID)
            {
                /* update seat temp */
                Seats[Seat_ID].Temp = Get_LM35TempSensor_Value();
                xSemaphoreGive(ADC_Semaphore);
                xQueueSend(ReevaluateQueue,&Seat_ID,portMAX_DELAY);

            }
        }

    }
}

/*********************************************************
 * periodic task to start lm35 conversion
 *******************************************************/
void LM35TempSensor_StartConversion_Task(void * pvParameters)
{
    uint8 Seat_ID;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
        /* loops for all seats that heater mode is on and start lm35 sensor */
        for(Seat_ID = SEAT_ONE_ID;Seat_ID < NUMBER_OF_SEATS; Seat_ID++)
        {
            if(Off != Seats[Seat_ID].HeaterMode)
            {
                xSemaphoreTake(ADC_Semaphore,portMAX_DELAY);
                LM35TempSensor_Start(Seats[Seat_ID].LM35TempSensor_ID);
            }
            /* delay */
            vTaskDelayUntil(&xLastWakeTime,pdMS_TO_TICKS(LM35TEMP_SENSOR_START_CONVERSION_TASK_DELAY_MS));
        }



    }
}

/************************************************************
 * Task to display Seat Mode and temperature through terminal
 ************************************************************/
void DisplayTask(void * pvParameters)
{
    uint8 Seat_ID;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {


        xSemaphoreTake(UART_Mutex,portMAX_DELAY);

        /* loop that loops over all seats and display its statues*/
        for(Seat_ID = SEAT_ONE_ID;Seat_ID < NUMBER_OF_SEATS; Seat_ID++)
        {

            TerminalDisplayString("Seat:");
            TerminalDisplayNum((uint32)Seat_ID);
            TerminalDisplay_NewLine();

            TerminalDisplayString("Heater mode:");
            switch (Seats[Seat_ID].HeaterMode)
            {
            case Off:TerminalDisplayString("Off");
            break;
            case Low:TerminalDisplayString("Low");
            break;
            case Medium:TerminalDisplayString("Medium");
            break;
            case High:TerminalDisplayString("High");
            }
            TerminalDisplay_NewLine();
            /* if seat is on display its temperature sensor reading */
            if(Off != Seats[Seat_ID].HeaterMode)
            {
                TerminalDisplayString("Temperature:");
                TerminalDisplayNum(Seats[Seat_ID].Temp);
                TerminalDisplay_NewLine();
            }





        }
        xSemaphoreGive(UART_Mutex);

        /* Task is delayed*/

        vTaskDelayUntil(&xLastWakeTime,pdMS_TO_TICKS(DELAY_TASK_DELAY_MS));

    }

}



/*******************************************
 * Task to calculate and print CPU load
 ******************************************/
#if(RUN_TIME_MEASURMENT_TASK_ENABLE == APPLICATION_TASK_ON)
void RunTimeMeasurmentsTask(void * pvParameters)
{
    /* variable updated by FreeRtos to track the time the task exits blocked state
     * so that delay time to be accurate
     */
    TickType_t xLastWakeTime = xTaskGetTickCount();

    /* variable used to track the previous time when cpu load was calculated*/
    uint32 PrevTimeStamp = 0;

    /* variable to hold current time */
    uint32 CurrentTimeStamp = 0;

    /* update prev time since task will be delayed */
    PrevTimeStamp = GetTimer0Ticks();
    for(;;)
    {

        /* Delay Task*/
        vTaskDelayUntil(&xLastWakeTime,pdMS_TO_TICKS(RUN_TIME_MEASURMENTS_TASK_DELAY_MS));

        xSemaphoreTake(UART_Mutex,portMAX_DELAY);

        /* Get current timer ticks*/
        CurrentTimeStamp = GetTimer0Ticks();

        TerminalDisplayString("CPU Load = ");

        /* display CPU load which calculated by using all times consumed by tasks in this interval
         * (tracked using trace hook macros ) multiplied by 100 to get percentage divided by
         * total time of this interval
         */
        TerminalDisplayNum(((((uint64)TotalTasksTicks * 100))/(CurrentTimeStamp - PrevTimeStamp)));
        TerminalDisplayString("%");
        TerminalDisplay_NewLine();

        /* update previous time variable */
        PrevTimeStamp = CurrentTimeStamp;

        /* clear time consumed by tasks to start new interval*/
        TotalTasksTicks = 0;

        xSemaphoreGive(UART_Mutex);
    }
}
#endif
/********************************************************
 * Function that will be called when button is pressed *
 *********************************************************/
void ButtonCallBack(uint8 Button_ID)
{
    /* variable updated by FrreRTOS to detect if an API woken up higher task priority than the task was running before ISR */
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    /* Send the pressed Button ID through Queue */
    xQueueSendFromISR(ButtonQueue, &Button_ID , &xHigherPriorityTaskWoken);

    /* if there a higher priority task was woken reschedule */
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

}

/********************************************************
 * Function that will be called when lm35 temp sensor reading is ready *
 *********************************************************/
void TempSensor_Callback(uint8 TempSensor_ID)
{
    /* variable updated by FrreRTOS to detect if an API woken up higher task priority than the task was running before ISR */
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    /* Send the LM35 sensor ID of the ready sensor through Queue */
    xQueueSendFromISR(TempSensorQueue, &TempSensor_ID , &xHigherPriorityTaskWoken);

    /* if there a higher priority task was woken reschedule */
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
