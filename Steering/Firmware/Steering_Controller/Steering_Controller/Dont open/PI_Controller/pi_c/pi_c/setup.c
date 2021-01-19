/*
 * setup.c
 *
 * Created: 18/01/2021 10:56:30 am
 *  Author: npat692
 */ 

#include "setup.h"

void pwm_init() {
	TCCR0A |= (1 << COM0A0);

	TCCR0A |= (1 << WGM00);
	TCCR0B |= (1 << WGM02);
	TCCR0B |= (1 << CS02);
	
}

void led_init(){
	DDRD |= (1 << PORTD6);
}

void adc_init(){
	ADCSRA |= (1 << ADIE); // ADC Complete Interrupt
	ADCSRA |= (1 << ADPS2)|(1 << ADPS1);
}