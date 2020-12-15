/*
 * timer.c
 *
 * Created: 9/12/2020 2:54:23 pm
 *  Author: Earlene
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>

timer0_init() {
	
	TCCR0A = 0b10000011;
	TCCR0B = 0b00000001;
	OCR0A = 30;
	
}

timer2_init() {
	
}
