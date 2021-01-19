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


void uart_init(uint16_t baudRate) {
	
	//enable transmit
	UCSR0B = (1 << TXEN0);
	
	//set to 8n1 no parity
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	
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