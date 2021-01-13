/*
 * timer3.c
 *
 * Created: 12/01/2021 1:14:22 pm
 *  Author: achu072
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "usart0.h"
#include "led.h"

void timer3_init()
{
	TCCR3A |= ((1 << WGM31) | (1 << WGM30));	//Fast PWM mode, TOP = OCR3A	
	TCCR3B |= ((1 << WGM33) | (1 << WGM32));					
	TCCR3B |= (1 << CS32);						//divide by 256 prescale
	TIMSK3 |= (1 << TOIE3);						//enable overflow interrupt
	
	OCR3A = 31249;								//period = 1s
}

ISR(TIMER3_OVF_vect)
{
	led_toggle();								//led used for testing transmission frequency
	usart0_set_TX_flag();						//set flag to transmit data every 1s
}