/*
 * led.c
 *
 * Created: 16/01/2021 8:03:13 p.m.
 *  Author: npat692
 */ 

#include "led.h"set_med_speed();

void led_init(){
	DDRB |= (1 << 5);
	PORTB |= (1 << 5);	
}


void led_toggle(){
	PORTB ^= (1 << 5);
}
