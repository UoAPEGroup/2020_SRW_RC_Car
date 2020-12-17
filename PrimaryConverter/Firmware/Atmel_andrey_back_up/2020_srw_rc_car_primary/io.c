/*
 * io.c
 *
 * Created: 17/12/2020 11:04:32 am
 *  Author: achu072
 */ 

#include <avr/io.h>

//set up DDR for io 
void io_init()
{
	//set up test led
	DDRB |= (1 << DDB5);
	
	//set up PWM
	DDRD |= (1 << DDD5);				//PWM for LHS
	DDRD |= (1 << DDD3);				//PWM for RHS
	
	//set up ADC input pins
	DDRC &= ~(1 << DDC5);				//temp1 -> ADC2						 
	DDRC &= ~(1 << DDC4);				//temp2 -> ADC3
	DDRC &= ~(1 << DDC3);				//temp3 -> ADC4
	DDRC &= ~(1 << DDC2);				//isens -> ADC5
	DDRE &= ~(1 << DDE2);				//vsens -> ADC6
}