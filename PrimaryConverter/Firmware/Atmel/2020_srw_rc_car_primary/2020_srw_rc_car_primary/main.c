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
	DDRD |= ((1 << DDD3) | (1 << DDD5));					//Set PD3 and PD5 as output for PWM testing
	
	timer_control_init();
	
    while (1) 
    {
    }
}

