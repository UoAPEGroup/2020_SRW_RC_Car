/*
 * PWM_Generation.c
 *
 * Created: 14/12/2020 11:05:22 p.m.
 * Author : Pranav G & Manoj K
 */ 

#include <avr/io.h>
#include "timer.h"

#define F_CPU 16000000UL

int main(void)
{
	//Need to make a duty cycle controlled PWM to drive the MOSFET.
	//Also develop the PI controller
	
	//Configuring PD5 as output for the PWM.
	DDRD |= (1<<PD5);
	
	timer0_init();
	
	
    while (1) 
    {
    }
}

