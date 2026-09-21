
/*
 * music_buzzer.c
 *
 * Created by Jeremy Venegas and Clyde Saligumba
 *
 * Fall 2025
 * ECE 266
 *
 */

#include "music.h"
#include <stdbool.h>
#include <stdint.h>
#include <inc/hw_memmap.h>
#include <inc/hw_timer.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/timer.h>

//define port c pin 5 for buzzer
#define BUZZER_PORT GPIO_PORTC_BASE
#define BUZZER_PIN  GPIO_PIN_5

// Note frequencies
const uint32_t note_delays[4] = {
    9565,  // Up
    7580,  // Down
    6378,  // Left
    5060   // Right
};

//access pin and enable for output device
void MusicInitBuzzer() {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    GPIOPinTypeGPIOOutput(BUZZER_PORT, BUZZER_PIN);
    GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, 0);
}

//set volume and note
void MusicSetBuzzer(int pitch, int volume) {
    if (pitch < 0 || pitch > 3) return;

    uint32_t cycles;
    switch (volume) {
        case 0: cycles = 50; break;   // Short

        case 1: cycles = 100; break;  // Medium

        case 2: cycles = 200; break;  // Long

        default: cycles = 100;
    }

    uint32_t note_delay = note_delays[pitch];
    uint32_t i;

    // play specific note based on pitch input
    for ( i = 0; i < cycles; i++) {
        GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, BUZZER_PIN); // High
        SysCtlDelay(note_delay);
        GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, 0); // Low
        SysCtlDelay(note_delay);
    }
}

//shutdown function
/*void MusicTurnOffBuzzer() {
    // Ensure buzzer is off
    GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, 0);
}
*/
