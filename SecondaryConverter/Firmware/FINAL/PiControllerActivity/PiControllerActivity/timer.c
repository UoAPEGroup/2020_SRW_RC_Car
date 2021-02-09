/*
 * timer.c
 *
 * Created: 2/02/2021 4:40:09 AM
 *  Author: Manoj Kumaraguru
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

static uint32_t overflowCount = 0;

ISR(TIMER1_OVF_vect) {
	overflowCount++; //Keeps count of time
}

void timerInit(){ //Initialises timer. Should be used for sampling autotrigger but currently used for keeping time
	TCCR1A = 0;
	TCCR1B = 0b00001000;
	TIMSK1 |= (1<<TOIE1);
	OCR1A = 65535;
}

//Returns the count overflow for time calculations
uint32_t returnOverflowCount() {
	return overflowCount;
}