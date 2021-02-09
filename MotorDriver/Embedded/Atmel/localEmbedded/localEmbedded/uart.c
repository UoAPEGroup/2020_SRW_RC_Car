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
#include <avr/interrupt.h>

#define ARRAYSIZE 10
#define F_CPU 8000000

// this function initializes the UART
void uart_init(uint32_t baudRate) {
	
	UCSR0A = 0;
	
	//enable transmit
	UCSR0B |= (1 << TXEN0);
	
	//set to 8n1 no parity
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
			
	//calculate the UBBR0 value required for the provided baudRate
	UBRR0 = F_CPU/(16 * baudRate) - 1;
}


// this function checks the flags and then transmits data to the terminal
void uart_transmit(uint8_t data){
	while( (UCSR0A & (1<<UDRE0)) == 0)
	{
		;
	}
	
	UDR0 = data;
	
}

//transmit multi-character data to uart using char array
void send_data(char data[]) {
	uint8_t count = 0;
	
	while (count < strlen(data) ) {
		uart_transmit(data[count]);
		count++;
	}
	
	//end the transmission with a newline
	uart_transmit(10);
	uart_transmit(13);
	
}

void uart_transmit_string(char *string) {
	for (uint8_t i = 0; i < strlen(string); i++) {
		uart_transmit(string[i]);
	}
}

//identify format of output