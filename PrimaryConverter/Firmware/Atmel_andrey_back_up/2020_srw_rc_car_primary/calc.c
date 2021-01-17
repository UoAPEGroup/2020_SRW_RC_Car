/*
 * calc.c
 *
 * Created: 11/01/2021 11:25:03 am
 *  Author: achu072
 */ 

#include <stdint.h>
#include <string.h>
#include <math.h>

#include "calc.h"

#define ASCII_OFF		48
#define NEWLINE			10
#define 1_DIGIT_CUTOFF	67
#define 2_DIGIT_CUTOFF	124
#define DUTY_DIGIT_1	2
#define DUTY_DIGIT_2	3
#define DUTY_DIGIT_3	4

//calculate duty cycle from maximum of 3 digits received from user
uint8_t calc_make_duty_cycle(uint8_t *buffer) 
{
	uint8_t duty_cycle = 0;
	
	for (uint8_t i = 0; i < strlen(buffer); i++) {
		if (buffer[i] != NEWLINE) {
			switch () {
				case DUTY_DIGIT_1:
					duty cycle 
			}
			
	}
	
	return duty_cycle;
}

//calculate OCRnB value to be set for timer0 & timer2
uint8_t calc_make_OCRnB(uint8_t period, uint8_t duty_cycle) 
{	
	if (duty_cycle > 100) {
		return 53;
	} else if (duty_cycle == 0) {
		return 0;
	}
	
	return (((uint16_t)period * 100) / (10000 / (uint16_t)duty_cycle));
}

//convert an ASCII character to int
uint8_t calc_ascii_to_num(uint8_t ascii)
{
	return (ascii - ASCII_OFF);
}  