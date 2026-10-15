#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LEDS 0x0F  

static const uint16_t paso_ms[8] = {0, 600, 400, 280, 200, 130, 80, 40};

static const uint8_t secuencia[6] = {
    (1 << PD0), (1 << PD1), (1 << PD2), (1 << PD3), (1 << PD2), (1 << PD1)
};

static uint8_t leer_dip(void)
{
    return (~PINC) & 0x07;   
}

int main(void)
{
    DDRD  |= LEDS;           
    DDRC  &= ~0x07;          
    PORTC |= 0x07;           

    uint8_t i = 0;

    while (1)
    {
        uint8_t valor = leer_dip();

        if (valor == 0) {
            PORTD &= ~LEDS;  
            i = 0;
            continue;
        }

        PORTD = (PORTD & ~LEDS) | secuencia[i];
        i = (i + 1) % 6;

        uint16_t t = paso_ms[valor];
        while (t >= 10) {
            _delay_ms(10);
            t -= 10;
            if (leer_dip() != valor) break;
        }
    }
}