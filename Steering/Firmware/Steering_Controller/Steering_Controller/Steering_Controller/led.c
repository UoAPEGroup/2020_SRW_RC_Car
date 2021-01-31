/*
 * led.c
 *
 * Created: 16/01/2021 8:03:13 p.m.
 *  Author: npat692
 */ 

#include "led.h"

void led_init(){
	DDRB |= (1 << 5);
	PORTB |= (1 << 5);	
	DDRB |= (1 << 2);
	PORTB |= (1 << 2);
}

void led_toggle(){
	PORTB ^= (1 << 5);
	PORTB ^= (1 << 2);
}
