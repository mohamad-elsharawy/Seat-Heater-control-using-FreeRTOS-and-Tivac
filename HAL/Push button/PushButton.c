/*
 * PushButton.c
 *
 *  Created on: Apr 23, 2025
 *      Author: mohamed
 */
#include"PushButton_internal.h"
/* variable used if general call back mode is used to hold ptr to callback function */
#if(PUSH_BUTTON_CALLBACK_CONFIG == GENERAL_CALLBACK)
static void ( * Callback_Ptr)(uint8 Button_ID) = Null;
#endif

/* button init function loops over all buttons in array in lcfg file and
 * configure its pin direction,ISR,Mode,setting pull up resistance and setting pin callback
 * to be PushButton_Press_Handle function
 */

void PushButton_init(void)
{
    uint8 counter = BUTTON_ZERO;
    for ( ; counter < NUMBER_OF_BUTTONS; counter++)
    {
        Port_SetPinMode(buttons[counter].port,buttons[counter].pin,PORT_PIN_GPIO_MODE);
        Port_SetPinDirection(buttons[counter].port,buttons[counter].pin,PORT_PIN_IN);
        Port_Set_InternalResistance(buttons[counter].port,buttons[counter].pin,PULL_UP_RESISTANCE);
        Port_EnablePin_Interrupt(buttons[counter].port,buttons[counter].pin,PORT_PIN_FALLING_EDGE_INTERRUPT);
        buttons[counter].status = BUTTON_UNPRESSED;
        Port_Pin_Set_CallBack(buttons[counter].port,buttons[counter].pin,PushButton_Press_Handle);
#if(PUSH_BUTTON_CALLBACK_CONFIG == CALLBACK_PER_PIN)
        buttons[counter].Callback_ptr = Null;
#endif

    }
}

/*********************************************************************************
 * this function set callback function that will be excuted when button is pressed
 *********************************************************************************/
void Set_PushButton_CallBack(void(* ptr)(uint8 ),uint8 Button_ID)
{
#if(PUSH_BUTTON_CALLBACK_CONFIG == GENERAL_CALLBACK)
    Callback_Ptr = ptr;
#elif(PUSH_BUTTON_CALLBACK_CONFIG == CALLBACK_PER_PIN)
    uint8 Button_ID = BUTTON_ZERO;
    while( (!( (buttons[Button_ID].port == Port) && (buttons[Button_ID].pin == Pin)) && (Button_ID < NUMBER_OF_BUTTONS)))
    {
        Button_ID ++;
    }
    if(NUMBER_OF_BUTTONS == Button_ID)
    {

    }
    else
    {
        buttons[Button_ID].Callback_ptr = ptr;
    }
#endif
}

/*************************************************************************************
 * this function is called when Button pin ISR is called and
 *  captures the button press and calls button callback function
 *************************************************************************************/
void PushButton_Press_Handle(uint8 Port,uint8 Pin)
{
    uint8 Button_ID = BUTTON_ZERO;

    /* loop over all buttons and compare there Port and Pin with button Port and pin
     * to get button ID (loop ends when button is found or all buttons are checked
     */
    while( (!( (buttons[Button_ID].port == Port) && (buttons[Button_ID].pin == Pin)) && (Button_ID < NUMBER_OF_BUTTONS)))
    {
        Button_ID ++;
    }
    /* if loop is finished because all buttons are checked do nothing and exit */
    if(NUMBER_OF_BUTTONS == Button_ID)
    {

    }
    /* else if port and pin are for valid button ID */
    else
    {
        /* check if the button has valid callback function if it is not valid do nothing */
#if(PUSH_BUTTON_CALLBACK_CONFIG == GENERAL_CALLBACK)
        if(Null == Callback_Ptr)
        {

        }
        else
#elif(PUSH_BUTTON_CALLBACK_CONFIG == CALLBACK_PER_PIN)
            if(Null == buttons[Button_ID].Callback_Ptr)
            {

            }
            else
#endif

            {
                /* if button previous status was initial state or
                 * falling edge(button unpressed) call callback function, assign  button status to
                 * button pressed and change ISR to capture falling edge to detect
                 * when button is unpressed
                 */
                if(BUTTON_UNPRESSED == buttons[Button_ID].status)
                {
#if(PUSH_BUTTON_CALLBACK_CONFIG == GENERAL_CALLBACK)
                    Callback_Ptr(Button_ID);
#elif(PUSH_BUTTON_CALLBACK_CONFIG == CALLBACK_PER_PIN)
                    buttons[Button_ID].Callback_ptr(buttons[Button_ID].port,buttons[Button_ID].pin);
#endif
                    Port_EnablePin_Interrupt(buttons[Button_ID].port,buttons[Button_ID].pin,PORT_PIN_RISING_EDGE_INTERRUPT);
                    buttons[Button_ID].status = BUTTON_PRESSED;
                }
                else
                {
                    /* if button previous status was rising edge (button pressed)
                     *  assign  button status to button unpressed
                     *  and change ISR to capture Rising edge to detect
                     * when button is pressed
                     */

                    Port_EnablePin_Interrupt(buttons[Button_ID].port,buttons[Button_ID].pin,PORT_PIN_FALLING_EDGE_INTERRUPT);
                    buttons[Button_ID].status = BUTTON_UNPRESSED;
                }
            }
    }
}
