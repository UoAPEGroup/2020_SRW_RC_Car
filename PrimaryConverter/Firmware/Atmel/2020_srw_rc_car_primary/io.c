/*
 * io.c
 *
 * Created: 17/12/2020 11:04:32 am
 *  Author: Andrey Chukhraev
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart0.h"

//set up DDR for io 
void io_init()
{
	//set up test led
	DDRB |= (1 << DDB5);
	
	//set up PWM
	DDRD |= (1 << DDD5);						//PWM for LHS
	DDRD |= (1 << DDD3);						//PWM for RHS
	
	//set up ADC input pins
	DDRC &= ~(1 << DDC5);						//isens  -> ADC2						 
	DDRC &= ~(1 << DDC4);						//temp2  -> ADC3
	DDRC &= ~(1 << DDC3);						//temp3	 -> ADC4
	DDRC &= ~(1 << DDC2);						//temp1  -> ADC5
	DDRE &= ~(1 << DDE2);						//vsens1 -> ADC6
	
	//set up external interrupt on INT0
	EICRA |= (1 << ISC01);						//falling edge at INT0 triggers interrupt
	EIMSK |= (1 << INT0);						//enable external interrupt at INT0
}

//on system start button press
ISR(INT0_vect)
{	
	//disable INT0
	EIMSK &= ~(1 << INT0);
	
	usart0_transmit_system_ready_msg();
	usart0_set_TX_system_active_flag();
}