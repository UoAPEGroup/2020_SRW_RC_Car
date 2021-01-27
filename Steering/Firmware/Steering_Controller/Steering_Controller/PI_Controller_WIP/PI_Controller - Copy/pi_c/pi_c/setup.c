/*
 * setup.c
 *
 * Created: 18/01/2021 10:56:30 am
 *  Author: npat692
 */ 

#include "setup.h"

void pwm_init() {
	TCCR0A |= (1 << COM0A1);
	TCCR0A |= (1 << WGM01);
	TCCR0A |= (1 << WGM00);
	TCCR0B |= (1 << CS02);
	//TCCR0B |= (1 << CS00);
	
}

void led_init(){
	DDRD |= (1 << PORTD6);
}

void adc_init(){
	ADMUX |= (1 << MUX1);
	ADCSRA |= (1 << ADEN);
	
	ADCSRA |= (1 << ADPS2)|(1 << ADPS1);
}