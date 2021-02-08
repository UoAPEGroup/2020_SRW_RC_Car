/*
 * adc.c
 *
 * Created: 2/02/2021 4:20:43 AM
 *  Author: Manoj Kumaraguru
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"
#include "PI_Control.h"

#define VOLTREF 3.3

ISR(ADC_vect){
	uint16_t measuredVolt = ADC;
	measuredVolt = (uint32_t)(measuredVolt) * VOLTREF/1024;
	calculateError(measuredVolt);
}

void adcInit(){
	DDRC &= ~(1<<PORTC0);
	ADMUX = 0b01000000;
	ADCSRA = 0b10111000;
	ADCSRB = 0;
}