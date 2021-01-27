/*
 * timer0.c
 *
 * Created: 9/12/2020 12:01:56 pm
 *  Author: Andrey Chukhraev
 */ 

#include <avr/io.h>

void timer0_init(uint8_t period) 
{
	TCCR0A |= (1 << COM0B1);					//Clear OC0B on compare match
	TCCR0A |= ((1 << WGM01) | (1 << WGM00));	//Fast PWM with TOP = OCR0A
	TCCR0B |= (1 << WGM02);
	TCCR0B |= (1 << CS00);						//Clock select no prescaling
	
	OCR0A = period;								
	OCR0B = 0;							
}

void timer0_set_OCR0B(uint8_t value)
{
	OCR0B = value;
}