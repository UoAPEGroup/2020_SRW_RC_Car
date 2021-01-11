/*
 * uart.c
 *
 * Created: 11/01/2021 10:05:00 am
 *  Author: npat692
 */ 

#include "uart.h"
#include "avr/io.h"

void uart_init(){
	UCSR0B |= (1 << RXCIE0); // RX Complete Interrupt Enable
	UCSR0B |= (1 << RXEN0); // Receiver Enable
	UCSR0B |= (1 << TXEN0);	
	UBRR0 = 51; // 9600 BAUD RATE
	UCSR0C = (1 << 2)|(1 << 1); // 8 Bit Frame 
}