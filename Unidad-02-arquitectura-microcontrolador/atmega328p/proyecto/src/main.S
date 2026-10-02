#include <avr/io.h>
.equ LED_PIN, 0
.equ DIP_0, 1
.equ DIP_1, 2


.section .text
.global main

main:
    ; CONFIGURACION
    
    sbi _SFR_IO_ADDR(DDRB), LED_PIN
    cbi _SFR_IO_ADDR(PORTB), LED_PIN

    cbi _SFR_IO_ADDR(DDRB), DIP_0
    cbi _SFR_IO_ADDR(DDRB), DIP_1
    sbi _SFR_IO_ADDR(PORTB), DIP_0
    sbi _SFR_IO_ADDR(PORTB), DIP_1

    ldi R16, 0x00

MAIN_LOOP:
    in R16, _SFR_IO_ADDR(PINB)
    ror R16
    andi R16, 0x03

    cpi R16, 0x00
    breq SET_SLOW
    cpi R16, 0x01
    breq SET_MIDLOW
    cpi R16, 0x02
    breq SET_MIDHIGH
    cpi R16, 0x03
    breq SET_HIGH

TURN_ON:
    sbi _SFR_IO_ADDR(PORTB), LED_PIN
    rcall DELAY
    cbi _SFR_IO_ADDR(PORTB), LED_PIN
    rcall DELAY

    rjmp MAIN_LOOP

SET_SLOW:
    ldi R17, 0XFF
    rjmp TURN_ON
SET_MIDLOW:
    ldi R17, 0X80
    rjmp TURN_ON
SET_MIDHIGH:
    ldi R17, 0X40
    rjmp TURN_ON
SET_HIGH:
    ldi R17, 0X10
    rjmp TURN_ON
    
; ============================================================
;  Subrutina de retardo
; ============================================================
DELAY:
    mov R18, R17
DELAY1:
    ldi R19, 0xFF
DELAY2:
    ldi R20, 0xFF
DELAY3:
    subi R20, 1
    brne DELAY3
    subi R19, 1
    brne DELAY2
    subi R18, 1
    brne DELAY1
    ret