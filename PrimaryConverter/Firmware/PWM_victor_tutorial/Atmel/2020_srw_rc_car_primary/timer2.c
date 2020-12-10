/*
 * timer2.c
 *
 * Created: 9/12/2020 12:03:15 pm
 *  Author: achu072
 */ 

#include <avr/io.h>

#define DEAD_TIME 7
#define DUTY_CHANGE 0

void timer2_init(uint8_t duty_cycle) 
{
	TCCR2A |= ((1 << COM2A1) | (1 << COM0A0));	//Set OC0A when up, clear when down
	TCCR2A |= (1 << COM2B1);					//Clear OC0B when up, set when down
	TCCR2A |= (1 << WGM20);						//Phase correct with TOP = 0xFF
	TCCR2B |= (1 << CS20);						//Clock select no prescaling
	
	OCR2A = duty_cycle + DUTY_CHANGE;
	OCR2B = duty_cycle - DEAD_TIME - DUTY_CHANGE;
}
