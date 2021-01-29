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

#define OFFSET	43														//180deg out of phase

static volatile uint8_t duty_cycle = 39;
static volatile uint8_t period = 79; 

//timer control is required to synchronize the timers in order to produce PWM signal 
void timer_control_init()
{
	GTCCR |= ((1 << TSM) | (1 << PSRASY) | (1 << PSRSYNC));				//halt all timers
	
	timer0_init(period, duty_cycle);									//configure timer0
	timer2_init(period, duty_cycle);									//configure timer2
	
	GTCCR = 0;															//release all timers
	
	TCNT0 = 0;															//set value for timer0
	TCNT2 = OFFSET;														//set value for timer2
}