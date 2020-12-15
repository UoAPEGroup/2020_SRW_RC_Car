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
	DDRD |= (1 << 6);
	DDRD |= (1 << 5);
	//Set to forward mode
	//stop all the timers
	GTCCR = (1<<TSM)|(1<<PSRASY)|(1<<PSRSYNC); 
	//initalise timers
	timer0_init(); 
	GTCCR = 0; 
	
    while (1)
    {
		_delay_ms(200);
		PORTD ^= (1 << 5); 
		
    }
}

