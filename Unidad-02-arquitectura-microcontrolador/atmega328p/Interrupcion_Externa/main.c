#define F_CPU 1600000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vect) {
    PORTD ^= (1 << PORTD4);   // Toggle LED en PD4
}

int main(void) {
    DDRD  |=  (1 << DDD4);
    DDRD  &= ~(1 << DDD2);
    PORTD |=  (1 << PORTD2);
    EICRA |= (1 << ISC01) | (1 << ISC00);  // Configura INT0 para activarse con flanco de bajada
    EIMSK |=  (1 << INT0);
    sei();
    while (1) { 
    
    }
}