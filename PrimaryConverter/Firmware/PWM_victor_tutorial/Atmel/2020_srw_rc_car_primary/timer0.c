
/*
 * timer0.c
 *
 * Created: 9/12/2020 12:01:56 pm
 *  Author: achu072
 */ 

#include <avr/io.h>

#define DEAD_TIME 7
#define DUTY_CHANGE 0

void timer0_init(uint8_t duty_cycle) 
{
	TCCR0A |= ((1 << COM0A1) | (1 << COM0A0));	//Set OC0A when up, clear when down
	TCCR0A |= (1 << COM0B1);					//Clear OC0B when up, set when down
	TCCR0A |= (1 << WGM00);						//Phase correct with TOP = 0xFF
	TCCR0B |= (1 << CS00);						//Clock select no prescaling
	
	OCR0A = duty_cycle + DUTY_CHANGE;								
	OCR0B = duty_cycle - DEAD_TIME - DUTY_CHANGE;
}