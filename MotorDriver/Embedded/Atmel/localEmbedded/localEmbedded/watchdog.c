/*
 * watchdog.c
 *
 * Created: 21/01/2021 11:38:53 pm
 *  Author: Earlene
 */ 

#include <avr/io.h>

void watchdog_init() {
	
	//set to reset mode after two seconds of non-responsiveness
	 WDTCSR |= (1 << WDE) | (1 << WDP0) | (1 << WDP1) | (1 << WDP2);
}