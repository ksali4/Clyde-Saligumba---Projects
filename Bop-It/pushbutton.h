/*
 * pushbutton.h
 *
 * Created by Jeremy Venegas and Clyde Saligumba
 *
 * Fall 2025
 * ECE 266
 *
 */


#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

#include <stdint.h>
#include <stdbool.h>
#include <inc/hw_memmap.h>
#include <inc/hw_ints.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/timer.h>
#include "launchpad.h"

//pushbutton direction definitions
typedef enum {
    BUTTON_UP = 0,
    BUTTON_DOWN = 1,
    BUTTON_LEFT = 2,
    BUTTON_RIGHT = 3,

    BUTTON_NONE
} Button;

//Initialize GPIO pins
void PushButtonsInit();

// for the button being pressed
Button PushButtonsGetPressed();

// wait for the return
Button PushButtonsWaitForPress();

#endif /* PUSHBUTTONS_H_ */
