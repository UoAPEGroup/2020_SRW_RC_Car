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
#define VOLTDIVRATIO 6.1

ISR(ADC_vect){
	PINC ^= (1<<PORTC2); //debug led
	TIMSK1 &= ~(1<<TOIE1);
	uint16_t measuredVolt = ADC; //Get value from ADC 
	measuredVolt = (uint32_t)(measuredVolt) * VOLTREF/1024; //Calculate actual voltage value. Still need to add resistor voltage ratios
	measuredVolt = measuredVolt * VOLTDIVRATIO;
	calculateError(measuredVolt); //Calculate error for PI
	
}

void adcInit(){ //Initialise ADC
	DDRC &= ~(1<<PORTC0);
	ADMUX = 0b01000000;
	ADCSRA = 0b11101000;
	ADCSRB = 0;
	ADCSRB |= (1<<ADTS1);
	ADCSRB |= (1<<ADTS2);
	DIDR0 = 0b0000000;
	//PINC |= (1<<PORTC2); //Debugging led
}