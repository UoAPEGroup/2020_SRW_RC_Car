/*
 * 2020_srw_rc_car_primary.c
 *
 * Created: 9/12/2020 10:48:31 am
 * Author : Andrey Chukhraev
 */ 

#include <avr/io.h>
#include "timer0.h"

#define F_CPU 8000000

int main(void)
{
	//IO set up
	PORTD |= (1 << PORTD5);						//Set PD5 as output for PWM testing
	
	timer0_init();

    while (1) 
    {
    }
}

