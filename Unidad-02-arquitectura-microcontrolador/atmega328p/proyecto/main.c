#include <avr/io.h>     // Librería para registros de I/O
#include <util/delay.h> // Librería de AVR para retardos temporales

int main(void) {
    DDRB |= (1 << DDB5);
    while (1) {
        // Codigo Principal

        // Encender el LED
        PORTB |= (1 << PORTB5);
        _delay_ms(500); // Esperar 500 ms

        //Apagar el LED (poner en LOW el pin PORTB5)
        PORTB &= ~(1 << PORTB5);
        _delay_ms(500); // Esperar 500 ms
    }

    return 0;
}