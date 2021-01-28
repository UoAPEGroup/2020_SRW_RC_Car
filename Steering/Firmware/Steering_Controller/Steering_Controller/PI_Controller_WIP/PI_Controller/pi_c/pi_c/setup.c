/*
 * setup.c
 *
 * Created: 18/01/2021 10:56:30 am
 *  Author: npat692
 */ 

#include "setup.h"

void pwm_init() {
	TCCR0A |= (1 << COM0A1); //  Toggle OC0A on compare match
	TCCR0A |= (1 << WGM01); // Phase Correct PWM
	TCCR0A |= (1 << WGM00); // 
	TCCR0B |= (1 << CS02);
	OCR0A = 0; // Sets Duty Cycle to 0%
	OCR0B = 255;
}

void led_init(){
	DDRD |= (1 << PORTD6);
}

void adc_init(){
	ADMUX = 0x00;
	ADMUX |= (1 << REFS0); // AVCC
	DDRC &=~(1 << PINC2); // PC2
	ADMUX |= (1<< MUX1); // ADC2
	ADCSRA |= (1 << ADEN); // ADC Enable
	ADCSRA |= (1 << ADPS2)|(1 << ADPS1); // 125kHz Sampling time 
}

void timer2_init(){
	TCCR2A = 0x00;
	TCCR2A |= (1 << WGM21); // CTC
	TCCR2B |= (1 << CS22); // 64 Prescaler
	OCR2A = 124; // 1ms Interrupt
	TIMSK2 |= (1 << OCIE2A); // Output Compare A 
}