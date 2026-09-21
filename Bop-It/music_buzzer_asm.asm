;******************************************************************************
; ECE 266, fall 2025
; Assembly functions related to buzzer
;
;Tiva C Series Pg. 658-659,
;port c memory address: 0x40006000
;pin 5 memeory address: 0x00000020
;GPIO data register address: 0x000003FC
;******************************************************************************

        .cdecls "music.h"
        .text

_GPIO_PORTC_BASE .field 0x40006000 ; Actual address for GPIO port C
_GPIO_PIN_5      .field 0x00000020 ; actual address for Pin 5

;******************************************************************************
; C prototype: void MusicTurnOffBuzzer()
; Turn off the buzzer.
;******************************************************************************
        .global MusicTurnOffBuzzer
        .asmfunc
MusicTurnOffBuzzer:
    ; Set buzzer output to low (turn buzzer off)
    LDR R0, _GPIO_PORTC_BASE ; load GPIO port C
    LDR R2, _GPIO_PIN_5 ; load GPIO_PIN_5 value
    LDR R1, [R0, #0x000003FC] ; Read GPIODATA register

    BIC R1, R1, R2 ; clear bit 5 to set Pin 5 low
    STR R1, [R0, #0x000003FC] ; write back to GPIODATA

    BX LR ; return
        .endasmfunc
