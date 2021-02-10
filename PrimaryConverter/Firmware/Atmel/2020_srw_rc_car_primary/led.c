/*
 * led.c
 *
 * Created: 17/12/2020 11:03:55 am
 *  Author: Andrey Chukhraev
 */ 

#include <avr/io.h>

void led_on()
{
	PORTB |= (1 << PORTB0);
}

void led_off()
{
	PORTB &= ~(1 << PORTB0);
}

void led_toggle()
{
	PORTB ^= (1 << PORTB0);
}