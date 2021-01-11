/*
 * uart.c
 *
 * Created: 11/01/2021 10:05:00 am
 *  Author: npat692
 */ 

#include "uart.h"

void uart_init(){
	UCSR0B |= (1 << 7); // RX Complete Interrupt Enable
	UCSR0B |= (1 << 4); // Receiver Enable
	UBRR0 = (F_CPU)/(16*BAUD_RATE) - 1; // 9600 BAUD RATE
}