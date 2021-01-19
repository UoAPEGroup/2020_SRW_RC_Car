/*
 * interrupt.c
 *
 * Created: 19/01/2021 10:10:13 pm
 *  Author: Earlene
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT0_vect) {
	
	DDRB |= (1 << DDB0);
	PORTB ^= (1 << 0);
	
	//read any state changes and set variables as needed
}

//set up external interrupt on INT0 pin
void interrupt_init() {
	
	EICRA |= (1 << ISC01) | (1 << ISC00);
	EIMSK |= (1 << INT0);
}