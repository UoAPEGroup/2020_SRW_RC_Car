/*
 * timer.c
 *
 * Created: 9/12/2020 2:54:23 pm
 *  Author: Earlene
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>

#include "global.h"

void timer0_init(uint8_t periodHalf, uint8_t onTimeHalf) {
	// generates pwm wave for left FET
	
	// phase Correct PWM, clear OC0B on compare match(inverting), with prescaler of 8
	TCCR0A |= (1 << COM0B1)|(1 << WGM00);
	TCCR0B |= (1 << WGM02)|(1 << CS01);
	
	OCR0A = periodHalf; //note that the duty cycle of the PWM wave is given by OCR0B/OCR0A, however, the frequency is 1/(OCR0A * 2 * PRESCALE/CLK_FREQ)
	OCR0B = onTimeHalf; //effectively, the switching frequency will be 1/2 of the frequency of the wave through the motor
	
}

void timer2_init(uint8_t periodHalf, uint8_t onTimeHalf) {
	// generates pwm for right FET 
	
	// phase Correct PWM, clear OC2B on compare match(inverting), prescaler of 8
	TCCR2A |= (1 << COM2B1)|(1 << WGM20);
	TCCR2B |= (1 << WGM22)|(1 << CS21);
	
	OCR2A = periodHalf;
	OCR2B = onTimeHalf;
}

void timer1_init() {
	//Toggle oc1a on compare match
	//TCCR1A |= (1 << COM1A0);
	
	//Set timer1 to 64 prescaler, CTC mode with OCR1A as TOP
	TCCR1B |= (1 << CS10) | (1 << WGM12) | (1 << CS11);
	
	//Set the period of sampling to 0.5ms
	OCR1A = 63;
	OCR1B = 40;
	
}

void timer3_init() {
	
	//64 prescaler, with 8MHz, (125000MHz, 8us per count)
	TCCR3B |= (1 << CS30) | (1 << WGM32) | (1 << CS31);
	
	//period = 40ms
	OCR3A = 5000;
	//OCR3B = 50;
	
	//enable interrupt on compare match B
	TIMSK3 |= (1 << OCIE3A); 
}