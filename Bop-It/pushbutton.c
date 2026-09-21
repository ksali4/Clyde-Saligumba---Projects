/*
 * pushbutton.c
 *
 * Created by Jeremy Venegas and Clyde Saligumba
 *
 * Fall 2025
 * ECE 266
 *
 */

#include "pushbutton.h"

//Define GPIO port and pins for each button
#define BUTTON_PORT        GPIO_PORTB_BASE
#define BUTTON_PINS        (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3)
#define BUTTON_UP_PIN      GPIO_PIN_0
#define BUTTON_DOWN_PIN    GPIO_PIN_1
#define BUTTON_LEFT_PIN    GPIO_PIN_2
#define BUTTON_RIGHT_PIN   GPIO_PIN_3


// Initialize GPIO pins for the buttons
void PushButtonsInit()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    // gpio pin, input type requiring 2 mili amps and a pull up resistor for external pushbuttons
    GPIOPinTypeGPIOInput(BUTTON_PORT, BUTTON_PINS);
    GPIOPadConfigSet(BUTTON_PORT, BUTTON_PINS, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

Button PushButtonsGetPressed()
{
    uint8_t state = GPIOPinRead(BUTTON_PORT, BUTTON_PINS); //set to read

    //inverse for pushbutton hardware
    if (!(state & BUTTON_UP_PIN))      return BUTTON_UP;
    if (!(state & BUTTON_DOWN_PIN))    return BUTTON_DOWN;
    if (!(state & BUTTON_LEFT_PIN))    return BUTTON_LEFT;
    if (!(state & BUTTON_RIGHT_PIN))   return BUTTON_RIGHT;
    return BUTTON_NONE;
}

Button PushButtonsWaitForPress()
{
    //set initial
    Button pressed = BUTTON_NONE;

        while (pressed == BUTTON_NONE)
            pressed = PushButtonsGetPressed();
            //checks if button is pressed

        // Debounce delay (~1 ms)
        SysCtlDelay(SysCtlClockGet() / 3000);

        // Wait for release
        while (PushButtonsGetPressed() != BUTTON_NONE);

        //return specific button pressed
        return pressed;
}
