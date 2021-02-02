/*
 * interrupt.c
 *
 * Created: 3/01/2021 9:59:54 AM
 *  Author: htom380
 */ 

#include <avr/interrupt.h>

void interrupt_init() {
	EIMSK |= (1 << INT1) | (1 << INT0);
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT0);
}