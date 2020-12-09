/*
 * timer0.c
 *
 * Created: 9/12/2020 12:01:56 pm
 *  Author: achu072
 */ 

#include <avr/io.h>

void timer0_init() 
{
	TCCR0A |= (1 << COM0B1);					//Clear OC0B on compare match
	TCCR0A |= ((1 << WGM01) | (1 << WGM00));	//Fast PWM with TOP = OCR0A
	TCCR0B |= (1 << WGM02);
	TCCR0B |= (1 << CS00);						//Clock select no prescaling
	
	OCR0A = 52;									//Actual count required for 150 kHz = 53.33
	OCR0B = 26;									//Duty cycle = 50%
}