/*
 * localEmbedded.c
 *
 * Created: 9/12/2020 2:54:10 pm
 * Author : Earlene
 */ 

#include <avr/io.h>
#include "timer.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#define MAX_VOLTAGE 9.5
#define MID_VOLTAGE 7
#define MIN_VOLTAGE 5
#define STOP 0

int main(void)
{
    /* Replace with your application code */

	//set output pins
	DDRD |= (1 << 3)|(1 << 5);

	//stop all the timers
	GTCCR = (1<<TSM)|(1<<PSRASY)|(1<<PSRSYNC); 
	
	//initialize timers
	timer0_init(79,39);  // (period,duty_cycle)
	timer2_init(79,39);
	
	GTCCR = 0; 
	
	TCNT0 = 0;
	TCNT2 = 83;
	
    while (1)
    {
    }
}

