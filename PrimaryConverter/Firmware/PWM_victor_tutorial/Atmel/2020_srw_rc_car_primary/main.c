/*
 * 2020_srw_rc_car_primary.c
 *
 * Created: 9/12/2020 10:48:31 am
 * Author : Andrey Chukhraev
 */ 

#include <avr/io.h>
#include "timer_control.h"

#define F_CPU 16000000UL

int main(void)
{
	//IO set up
	DDRD |= ((1 << DDD6) | (1 << DDD5) | (1 << DDD3));					//Set PB3, PD3, PD5, PD6 as output for PWM testing
	DDRB |= (1 << DDB3);
	
	timer_control_init();
	
    while (1) 
    {
    }
}

