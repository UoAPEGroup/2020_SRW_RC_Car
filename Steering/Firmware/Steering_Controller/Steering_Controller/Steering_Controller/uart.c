/*
 * uart.c
 *
 * Created: 11/01/2021 10:05:00 am
 *  Author: npat692
 */ 

#include "uart.h"

// UART Initialization
void uart_init(){
	UCSR0B |= (1 << RXCIE0); // RX Complete Interrupt Enable
	UCSR0B |= (1 << RXEN0); // Receiver Enable
	UCSR0B |= (1 << TXEN0);	// Transmitter Enable
	UBRR0 = (F_CPU/((uint32_t)BAUD_RATE * 16)) - 1; // 9600 BAUD RATE
	UCSR0C = (1 << 2)|(1 << 1); // 8 Bit Frame 
}

// Echo function
void tx_debug(char output){
	UDR0 = output;
}

// Check timeout count
void check_timeout(){
	if (timeout_count > MAX_TIMEOUT_COUNT){
		stall_control(); 
	}
	else{
		timeout_count++; // 1ms increment
	}
}

// Reset timeout counter 
void reset_timeout(){
	timeout_count = 0;
}

// Stalls all motion
void stall_control(){
	set_no_speed();
	set_point_angle = straight_turn;
	STATE_INT_TOGGLE;
}