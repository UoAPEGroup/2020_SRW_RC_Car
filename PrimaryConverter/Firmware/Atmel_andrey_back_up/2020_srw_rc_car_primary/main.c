/*
 * 2020_srw_rc_car_primary.c
 *
 * Created: 9/12/2020 10:48:31 am
 * Author : Andrey Chukhraev
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer_control.h"
#include "adc.h"

#define F_CPU 8000000UL

int main(void)
{
	//IO set up
	DDRD |= ((1 << DDD3) | (1 << DDD5));								//set PD3 and PD5 as output for PWM testing
	DDRC &= ~((1 << DDC5) | (1 << DDC4) | (1 << DDC3) | (1 << DDC2));	//set PC5, PC4, PC3, PC2 and PE2 as inputs to ADC
	DDRE &= ~(1 << DDE2);
	
	timer_control_set_duty(26);
	timer_control_init();
	adc_init();
	sei();
	
    while (1) 
    {
    }
}

