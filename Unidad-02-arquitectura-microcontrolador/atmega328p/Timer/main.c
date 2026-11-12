#define F.CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

Volative uint_16 Contador_ms = 0;

ISR (TIMER1_COMPA_vect){

    Contador_ms++;

    if (contador-ms >=500) { PORTB  ^= (1<<PB5); Contador_ms = 0;

}   
}

int main () {

DDRB | = (1<<DDB5);

TCRIA=0;

TCCR1B=0;

TCNT1=0;

OCR1A = 249;

TCCR1B |= (1<<WGM12);

TCCR1B |= (1 <<(CS11) | (1<<CS10));

TIMSK1 |= (1<<OCIE1A);

sei();

while (1);
}