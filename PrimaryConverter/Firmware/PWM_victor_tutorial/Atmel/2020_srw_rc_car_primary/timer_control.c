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

uint8_t duty_cycle = 128;													//128 is 50% duty cycle count

//timer control is required to synchronize the timers in order to produce PWM signal 
void timer_control_init()
{
	GTCCR |= ((1 << TSM) | (1 << PSRASY) | (1 << PSRSYNC));					//halt all timers
	
	timer0_init(duty_cycle);												//configure timer0
	timer2_init(duty_cycle);												//configure timer2
	
	TCNT0 = 0;																//zero timer0
	TCNT2 = 0;																//zero timer2
	
	GTCCR = 0;																//release all timers
}