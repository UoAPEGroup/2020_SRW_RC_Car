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

void timer0_init(uint8_t period, uint8_t duty_cycle) {
	
	//Phase Correct PWM, clear OC0B on compare match(inverting)
	TCCR0A |= (1 << COM0B1)|(1 << WGM00);
	TCCR0B |= (1 << WGM02)|(1 << CS00);
	
	OCR0A = period;
	OCR0B = duty_cycle;
	
}

void timer2_init(uint8_t period, uint8_t duty_cycle) {
	//Phase Correct PWM, clear OC2B on compare match(inverting)
	TCCR2A |= (1 << COM2B1)|(1 << WGM20);
	TCCR2B |= (1 << WGM22)|(1 << CS20);
	
	OCR2A = period;
	OCR2B = duty_cycle;
}

void timer1_init() {
	//Toggle oc1a on compare match
	TCCR1A |= (1 << COM1A0);
	
	//Set timer1 to 64 prescaler, CTC mode with OCR1A as TOP
	TCCR1B |= (1 << CS10) | (1 << WGM12) | (1 << CS11);
	
	//Set the period of sampling to 0.5ms
	OCR1A = 63;
	OCR1B = 40;
	
}