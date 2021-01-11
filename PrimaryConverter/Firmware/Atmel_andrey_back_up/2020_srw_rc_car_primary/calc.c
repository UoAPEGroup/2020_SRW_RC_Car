/*
 * calc.c
 *
 * Created: 11/01/2021 11:25:03 am
 *  Author: achu072
 */ 

#include <stdint.h>
#include <string.h>

#include "calc.h"

//calculate duty cycle from maximum of 3 digits received from user
uint8_t calc_make_duty_cycle(char *buffer) 
{
	uint8_t duty_cycle = 0;
	
	for (uint8_t i = 0; i < strlen(buffer); i++) {
		switch (i) {
			case 0:
				duty_cycle += buffer[i] * 100;
				break;
			case 1:
				duty_cycle += buffer[i] * 10;
				break;
			case 2:
				duty_cycle += buffer[i];
				break;
		}	
	}
	return duty_cycle;
}

//calculate OCRnB value to be set for timer0 & timer2
uint8_t calc_make_OCRnB(uint8_t period, uint8_t duty_cycle) 
{	
	if (duty_cycle > 100) {
		return 0;
	} else if (duty_cycle == 0) {
		return 0;
	}
	
	return (period / (100 / duty_cycle));
}