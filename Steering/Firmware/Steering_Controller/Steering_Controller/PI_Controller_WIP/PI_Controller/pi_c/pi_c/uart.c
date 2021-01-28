/*
 * uart.c
 *
 * Created: 28/01/2021 12:14:20 pm
 *  Author: npat692
 */ 

#include "uart.h"
#include <stdio.h>
#include <string.h>

//set up asynchronous USART0, 8N1, no parity
void usart0_init(uint32_t BAUD)
{
	UCSR0A |= 0x00;														//clear all bits
	UCSR0B |= (1 << RXCIE0);											//enable RX complete interrupt
	UCSR0B |= (1 << RXEN0);												//receiver enable
	UCSR0B |= (1 << TXEN0);												//transmitter enable
	UCSR0C |= ((1 << UCSZ01) | (1 << UCSZ00));							//8-bit packet size
	UCSR0C &= ~(1 << UCPOL0);											//clear polarity bit - not used
	UBRR0 = F_CPU / (16 * BAUD) - 1;									//set UBRR
}

//transmit one byte of data
void usart0_transmit_byte(uint8_t byte)
{
	while ((UCSR0A & (1 << UDRE0)) == 0) {
		;
	}
	
	UDR0 = byte;
}

//transmit string
void usart0_transmit_string(char *string)
{
	for (uint8_t i = 0; i < strlen(string); i++) {
		usart0_transmit_byte(string[i]);
	}
}