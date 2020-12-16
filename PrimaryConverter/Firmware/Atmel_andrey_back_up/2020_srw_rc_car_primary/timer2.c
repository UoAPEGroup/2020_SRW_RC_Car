/*
 * timer2.c
 *
 * Created: 9/12/2020 12:03:15 pm
 *  Author: achu072
 */ 

#include <avr/io.h>

void timer2_init(uint8_t period, uint8_t duty_cycle) 
{
	TCCR2A |= (1 << COM0B1);					//Clear OC2B on compare match
	TCCR2A |= ((1 << WGM21) | (1 << WGM20));	//Fast PWM with TOP = OCR2A
	TCCR2B |= (1 << WGM22);
	TCCR2B |= (1 << CS20);						//Clock select no prescaling
	
	OCR2A = period;								
	OCR2B = duty_cycle;							
}
