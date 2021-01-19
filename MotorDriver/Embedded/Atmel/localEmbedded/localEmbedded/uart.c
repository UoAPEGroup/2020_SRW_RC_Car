/*
 * uart.c
 *
 * Created: 19/01/2021 12:27:50 pm
 *  Author: Earlene
 */ 

#include <avr/io.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

// this function initialises the UART

void uart_init() {
	UCSR0A = 0b00000000;
	UCSR0B = 0b00001000;
	UCSR0C = 0b00000110;
	UBRR0 = 4;
}


// this function checks the flags and then transmits data to the terminal
void uart_transmit(uint8_t data){
	while(~UCSR0A & (1<<UDRE0))
	{
		;
	}
	if(UCSR0A & (1<<UDRE0)) {
		UDR0 = data;
	}
}