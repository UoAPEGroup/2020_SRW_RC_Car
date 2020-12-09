/*
 * timer_control.c
 *
 * Created: 9/12/2020 1:24:24 pm
 *  Author: achu072
 */ 

#include <avr/io.h>
#include <stdint.h>
#include "timer0.h"
#include "timer2.h"

#define OFFSET	25

static uint8_t duty_cycle = 26;
static uint8_t period = 52; 

//timer control is required to synchronize the timers
void timer_control_init()
{
	GTCCR |= ((1 << TSM) | (1 << PSRASY) | (1 << PSRSYNC));				//halt all timers
	
	timer0_init(period, duty_cycle);									//configure timer0
	timer2_init(period, duty_cycle);									//configure timer2
	
	TCNT0 = 0;															//zero timer0
	TCNT2 = OFFSET;														//zero timer2
	
	GTCCR = 0;															//release all timers
}