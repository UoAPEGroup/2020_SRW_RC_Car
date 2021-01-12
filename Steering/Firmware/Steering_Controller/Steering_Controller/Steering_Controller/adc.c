/*
 * adc.c
 *
 * Created: 11/01/2021 10:04:51 am
 *  Author: npat692
 */ 

#include "adc.h"

void adc_init(){
	ADMUX |= (1 << MUX0); // ADC Channel 1
	ADCSRA |= (1 << ADIE); // ADC Complete Interrupt 
}

// Convert ADC value into mV
uint32_t adc_convert(uint16_t adc_val) {
	
	uint32_t voltage_val = adc_val * (VREF/ADC_RES);					// Ref. voltage divided by ADC res. multiplied by input/ADC register value
	
	return voltage_val;
}