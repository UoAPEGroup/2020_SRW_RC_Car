/*
 * interrupt.c
 *
 * Created: 3/01/2021 9:59:54 AM
 *  Author: htom380
 */ 

#include <avr/interrupt.h>

#include "interrupt.h"
#include "global.h"

void interrupt_init() {
	EIMSK |= (1 << INT1) | (1 << INT0);
	EICRA |= (1 << ISC10) | (1 << ISC00);
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT0) | (1 << PCINT1);
	
	
	// Configure accel. switch input pins
	DDRD &= ~(1 << PORTD2) | ~(1 << PORTD3);
	DDRB &= ~(1 << PORTB0) | ~(1 <<PORTB1);
	DDRD &= ~(1 << PORTD6) | ~(1 << PORTD7);
	
	DDRD &= ~(1 << PORTC2);
	DDRD &= ~(1 << PORTD5);
}