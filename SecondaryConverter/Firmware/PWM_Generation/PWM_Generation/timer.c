/*
 * timer.c
 *
 * Created: 14/12/2020 11:06:03 p.m.
 *  Author: Pranav G & Manoj K
 */ 

#include <avr/io.h>
#include "timer.h"

void timer0_init(uint8_t dutyCycle){
	
	TCCR0A |= (1<<COM0A1); //Clear OC0A on C match, set at Bottom. -Non-inverting.
	TCCR0A |= (1<<WGM01) | (1<<WGM00); //Fast PWM mode.
	TCCR0B |= (1<<CS00); //No prescalling.
	
	OCR0A = 255*((double)dutyCycle/100); //Set duty cycle
	
}