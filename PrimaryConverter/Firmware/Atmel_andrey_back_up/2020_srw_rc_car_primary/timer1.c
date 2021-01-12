/*
 * timer1.c
 *
 * Created: 16/12/2020 10:14:26 am
 *  Author: achu072
 */ 

#include <avr/io.h>

void timer1_init()
{
	TCCR1B |= (1 << WGM12);					//CTC mode, TOP = OCR1A
	TCCR1B |= (1 << CS10);					//no prescale
	
	OCR1A = 799;							//period = 1/8MHz * (799 + 1) = 0.1ms					
}