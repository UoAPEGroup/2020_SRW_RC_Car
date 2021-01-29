/*
 * usart0.c
 *
 * Created: 12/18/2020 10:32:24 AM
 *  Author: Kimsong Lor
 */ 

#include "usart0.h"

void uart0_init(uint32_t baud_rate) {
	UCSR0B |= (1<<RXCIE0); //RX Complete Interrupt Enable
	//UCSR0B |= (1<<TXCIE0); //TX Complete Interrupt Enable
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0); //Receiver and Transmitter Enable
	
	//UMSEL0[1,0]=00 Asynchronous USART mode
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00); //8-bit character size
	
	UBRR0 = (F_CPU / (16 * baud_rate) - 1);	//Set UBRR0 as per baud rate formula
}

void uart0_transmit_byte(char byte){
	while ((UCSR0A & (1 << UDRE0)) == 0){     //UDRE0 bit is checked to see if it is 0
		;									  //If UDRE0 bit is not 0, wait until it becomes 0
	}
	UDR0 = byte;	//Put the byte to be sent into the UDR0 register
}

void uart0_transmit_array(char* msg){
	//Loop through each byte in the array
	for (uint8_t i = 0; i < strlen(msg); i++){
		uart0_transmit_byte(msg[i]);			//Transmit each byte using uart0_transmit_byte(char byte)
	}
}