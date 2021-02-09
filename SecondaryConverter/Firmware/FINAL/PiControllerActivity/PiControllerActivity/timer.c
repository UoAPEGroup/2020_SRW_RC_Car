/*
 * timer.c
 *
 * Created: 2/02/2021 4:40:09 AM
 *  Author: Manoj Kumaraguru
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

ISR(TIMER1_OVF_vect) {
}

void timerInit(){ //Initialises timer. Should be used for sampling autotrigger but currently used for keeping time
	TCCR1A = 0;
	TCCR1B = 0b00001000;
	TIMSK1 |= (1<<TOIE1);
	OCR1A = 431;
}