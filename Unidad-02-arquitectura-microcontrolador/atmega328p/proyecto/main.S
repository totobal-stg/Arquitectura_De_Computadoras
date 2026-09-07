#include <avr/io.h>

.section .text
.global main

main:
    ldi r16, 0x0A
    ldi r17, 0x3B
    ADD r16, r17
    NOP
    LDI r18, 0x7F
    LDI r19, 0x01
    LDI r20, 0xFF
    LDI r21, 0x10
    LDI r22, 0x20
    NOP
    MOV r23, r18
    ADD r23, r19
    MOV r24, r20
    ADD r24, r19
    MOV r25, r21
    ADD r25, r22
    NOP






    



