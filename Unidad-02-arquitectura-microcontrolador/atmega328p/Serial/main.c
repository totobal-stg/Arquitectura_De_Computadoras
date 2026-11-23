#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdint.h>

void UART_init (){
    uint16_t ubrr =103;
    UCSRA = 0;

UBRR0H = (uint8_t)(ubrr>>8);
UBRR0L = (uint8_t)(ubrr);
UCSR0B = (1<<RXEN0) | (1<<TXEN0);
UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
}

void UART_transmit (uint8_t data){

while(! (UCSR0SA & (1<<UDRE0))) {}

UDR0 = data;
}

uint8_t UART_Receive (){ 
    while (!(UCSR0A & (1<<RXC0))) 
    {} return UDR0; 
}