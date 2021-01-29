/*
 * timer4.c
 *
 * Created: 28/01/2021 4:23:28 pm
 *  Author: Andrey Chukhraev
 */ 

#include <avr/io.h>

void timer4_init()
{
	TCCR4B |= (1 << WGM42);					//CTC mode, TOP = OCR4A
	TCCR4B |= (1 << CS40);					//no prescale
	TIMSK4 |= (1 << OCIE4B);				//OCR4B interrupt enable
	
	OCR4A = 7999;							//period = 1/8MHz * (7999 + 1) = 1ms
	OCR4B = 4000;
}
