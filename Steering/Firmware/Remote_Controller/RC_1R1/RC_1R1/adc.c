/*
 * adc.c
 *
 * Created: 12/01/2021 11:13:15 AM
 *  Author: htom380
 */ 

#include "adc.h"

#include <avr/interrupt.h>

volatile uint32_t steering_val = 0;

ISR(ADC_vect) {
	steering_val = adc_convert(return_adc_reg());
}

// ADC Initialisation (Boot)
void adc_init() {
	
	ADCSRA |= (1 << ADEN);											// Enable ADC
	ADCSRA |= (1 << ADATE);											// Enable Auto Trigger conversion mode
	ADCSRA |= (1 << ADIE);											// Enable ADC interrupt when conversions are complete
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS0);							// Set input clock frequency prescaler value of 32 (8MHz/64 = 250KHz)
	
	ADMUX |= (1 << REFS0);											// Set AVcc as ADC reference voltage
	
	ADCSRB |= (1 << ADTS1) | (1 << ADTS0);							// Set Timer0 Compare Match A as event for ADC Auto trigger
	
	DIDR0 = 0xff;													// Disable digital input buffer (Must be written to logic 1)
	
	
	ADMUX |= (1 << MUX1);														// Select channel 2 for steering ADC input
}


uint16_t return_adc_reg() {
	return ADC;
}

// Convert ADC value into mV
uint32_t adc_convert(uint16_t adc_val) {	
		
	uint32_t voltage_val = adc_val * (AREF/ADC_RES);					// Ref. voltage divided by ADC res. multiplied by input/ADC register value
	
	return voltage_val;
}

uint32_t return_adc_val() {
	return adc_convert(return_adc_reg());
}

/******************************** OBSOLETE FUNCTIONS ********************************/

// Manual ADC read function
uint16_t adc_read(uint8_t channel) {
	
	ADMUX &= ~( (1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0) );		// Clear channel selection
	ADMUX |= channel;												// Select ADC channel for conversion
	
	while (!(ADCSRA & ( 1 << ADIF)) ) {								// Wait for conversion to finish
	}
	
	return ADC;
}

/************************************************************************************/