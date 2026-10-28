#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <util/delay.h>
#include "Tablas.h"


#define N_ESTADOS (sizeof(tabla) / sizeof(tabla[0]))
#define N_MODOS   (sizeof(tiempo_ms) / sizeof(tiempo_ms[0]))
#define DIP_MASK  (SOL_MASK | (MODO_MASK << MODO_SHIFT))

_Static_assert(N_ESTADOS >= 1 && N_ESTADOS <= 255, "N_ESTADOS fuera de rango");
_Static_assert(N_MODOS <= (MODO_MASK + 1), "Hay mas modos que combinaciones del DIP");

static volatile uint8_t modo;
static volatile uint8_t solicitud;

ISR(PCINT1_vect){
    uint8_t pines = ~PINC;
    modo = (pines >> MODO_SHIFT) & MODO_MASK;
    if (pines & SOL_MASK)
        solicitud = 1;
}

static uint16_t tiempo_actual(void){
    uint8_t m = modo;
    return (m < N_MODOS) ? pgm_read_word(&tiempo_ms[m]) : 0;
}

static void leds(uint8_t v){
    PORTD = (PORTD & ~LED_MASK) | (v & LED_MASK);
}

static uint8_t espera_ms(uint16_t ms){
    while (ms--) {
        if (tiempo_actual() == 0)
            return 1;
        _delay_ms(1);
    }
    return 0;
}

int main(void){
    uint8_t estado = ESTADO_INICIAL;

    DDRD  |= LED_MASK;
    DDRC  &= ~DIP_MASK;
    PORTC |= DIP_MASK;
    _delay_us(5);

    uint8_t pines = ~PINC;
    modo = (pines >> MODO_SHIFT) & MODO_MASK;
    solicitud = (pines & SOL_MASK) ? 1 : 0;

    PCMSK1 |= DIP_MASK;
    PCICR  |= (1 << PCIE1);
    sei();

    for (;;) {
        uint16_t t = tiempo_actual();

        if (t == 0) {
            leds(0);
            estado = ESTADO_INICIAL;
            solicitud = 0;
            continue;
        }

        uint8_t fases = pgm_read_byte(&tabla[estado].fases);
        if (fases == 0)
            fases = 1;
        uint16_t t_fase = t / fases;
        uint8_t apagar = 0;

        for (uint8_t f = 0; f < fases && !apagar; f++){
            leds((f & 1) ? pgm_read_byte(&tabla[estado].sal_off)
                         : pgm_read_byte(&tabla[estado].sal_on));
            apagar = espera_ms(t_fase);
        }

        if (apagar) {
            leds(0);
            estado = ESTADO_INICIAL;
            solicitud = 0;
            continue;
        }

        uint8_t sig0 = pgm_read_byte(&tabla[estado].sig[0]);
        uint8_t sig1 = pgm_read_byte(&tabla[estado].sig[1]);
        uint8_t nivel = (~PINC & SOL_MASK) ? 1 : 0;
        uint8_t sol;

        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            sol = solicitud | nivel;
            if (sol && sig0 != sig1)
                solicitud = 0;
        }

        uint8_t sig = sol ? sig1 : sig0;
        estado = (sig < N_ESTADOS) ? sig : ESTADO_INICIAL;
    }
}


//avrdude -c usbasp -p m328p -U lfuse:w:0xFF:m