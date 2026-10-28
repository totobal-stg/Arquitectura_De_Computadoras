#ifndef TABLAS_H
#define TABLAS_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>

#define A_V (1<<PD0)
#define A_R (1<<PD1)
#define B_V (1<<PD2)
#define B_R (1<<PD3)
#define P_V (1<<PD4)
#define LED_MASK (A_V | A_R | B_V | B_R | P_V)

#define SOL_MASK   (1<<PC0)
#define MODO_SHIFT 1
#define MODO_MASK  0x03

typedef struct {
    uint8_t sal_on;
    uint8_t sal_off;
    uint8_t fases;
    uint8_t sig[2];
} Estado_t;

enum { S0, S1, S2, S3, S4, S5 };
#define ESTADO_INICIAL S0

static const Estado_t tabla[] PROGMEM = {
    { A_V | B_R,       A_V | B_R,       1, { S1, S1 } },
    { A_V | B_R,       B_R,             4, { S2, S2 } },
    { A_R | B_V,       A_R | B_V,       1, { S3, S3 } },
    { A_R | B_V,       A_R,             4, { S4, S4 } },
    { A_R | B_R,       A_R | B_R,       1, { S0, S5 } },
    { A_R | B_R | P_V, A_R | B_R | P_V, 1, { S0, S0 } },
};

static const uint16_t tiempo_ms[] PROGMEM = { 0, 1000, 500, 2000 };

#endif