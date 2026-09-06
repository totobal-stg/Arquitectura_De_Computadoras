#include <avr/io.h>

.section .text
.global main

main:
    ldi r16, 0x0A
    clr r17

MAIN_LOOP:
    inc r16           ; Incrementamos para ver cambios reales en el registro
    inc r16
    mov r17, r16
    rjmp MAIN_LOOP


