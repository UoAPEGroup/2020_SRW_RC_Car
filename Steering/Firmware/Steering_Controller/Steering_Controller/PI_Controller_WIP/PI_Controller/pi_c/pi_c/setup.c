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
	OCR0A = 0;
}

void led_init(){
	DDRD |= (1 << PORTD6);
}

void adc_init(){
	ADMUX = 0x00;
	DDRC &=~(1 << PINC2);
	DDRC &=~(1 << PINC5);
	//ADMUX |= (1 << MUX1);
	ADMUX |= (1 << MUX2)|(1 << MUX0);
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADPS2)|(1 << ADPS1);
}

void timer2_init(){
	TCCR2A = 0x00;
	TCCR2A |= (1 << COM2A0);
	TCCR2A |= (1 << WGM21); // CTC
	TCCR2B |= (1 << CS22); // 64 Prescale
	OCR2A = 124; // 1ms
	TIMSK2 |= (1 << OCIE2A); // Output Compare A 
	
}