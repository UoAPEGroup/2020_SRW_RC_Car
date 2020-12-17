/*
 * led.c
 *
 * Created: 17/12/2020 11:03:55 am
 *  Author: achu072
 */ 

#include <avr/io.h>

void led_on()
{
	PORTB |= (1 << PORTB5);
}

void led_off()
{
	PORTB &= ~(1 << PORTB5);
}

void led_toggle()
{
	PORTB ^= (1 << PORTB5);
}