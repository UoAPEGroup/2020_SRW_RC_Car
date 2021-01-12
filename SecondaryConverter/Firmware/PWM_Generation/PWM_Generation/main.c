/*
 * PWM_Generation.c
 *
 * Created: 14/12/2020 11:05:22 p.m.
 * Author : Pranav G & Manoj K
 */ 

#include <avr/io.h>
#include "timer.h"
#include "adc.h"

int main(void)
{
	//Need to make a duty cycle controlled PWM to drive the MOSFET.
	//Also develop the PI controller
	
	//Configuring PD6 as output for the PWM.
	DDRD |= (1<<PD6);
	
	timer0_init(80); //Made the PWM duty Cycle controlled. 0 to 100.
	
	
    while (1) 
    {
    }
}

