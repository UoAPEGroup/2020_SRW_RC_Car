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
	uint8_t periodHalf = 27;
	uint8_t dutyLHalf = 13;
	uint8_t dutyRHalf = 13;
	uint8_t offset = 0;

	//set output pins
	DDRD |= (1 << 3)|(1 << 5);

	//stop all the timers
	GTCCR = ((1<<TSM)|(1<<PSRASY)|(1<<PSRSYNC)); 
	
	//initialize timers
	timer0_init(periodHalf,dutyLHalf);  // PWm that controls the left FET driver
	timer2_init(periodHalf,dutyRHalf);  // PWM that controls the right FET driver
	
	GTCCR = 0;   // start all timers
	
	TCNT0 = 0;   // setting offset
	TCNT2 = offset;  // setting offset(set to period to)

    // Vout = Vin * ((dutyL - dutyR)/period)	
	
    while (1)
    {
    }
}

