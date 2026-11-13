#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define T_BASE 500   // ms, ningún switch activo
#define T_SW1  100   // PD1
#define T_SW2  250   // PD2
#define T_SW3  1000  // PD3

volatile uint16_t Contador_ms = 0;
volatile uint16_t limite_ms = T_BASE;

ISR(TIMER1_COMPA_vect) {
    Contador_ms++;
    if (Contador_ms >= limite_ms) {
        PORTD ^= (1 << PD4);
        Contador_ms = 0;
    }
}

uint16_t leer_dip(void) {
    // con pull-up, switch activo = 0
    if (!(PIND & (1 << PD1))) return T_SW1;
    if (!(PIND & (1 << PD2))) return T_SW2;
    if (!(PIND & (1 << PD3))) return T_SW3;
    return T_BASE;
}

int main(void) {
    DDRD |= (1 << DDD4);                                 // LED
    DDRD &= ~((1 << DDD1) | (1 << DDD2) | (1 << DDD3));  // entradas
    PORTD |= (1 << PD1) | (1 << PD2) | (1 << PD3);       // pull-ups

    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1  = 0;
    OCR1A  = 249;
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS11) | (1 << CS10);
    TIMSK1 |= (1 << OCIE1A);

    sei();

    while (1) {
        uint16_t nuevo = leer_dip();
        if (nuevo != limite_ms) {
            cli();
            limite_ms = nuevo;
            Contador_ms = 0;   // reinicia la cuenta al cambiar de velocidad
            sei();
        }
    }
}