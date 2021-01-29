/*
 * adc.c
 *
 * Created: 11/01/2021 10:04:51 am
 *  Author: npat692
 */ 

#include "adc.h"

void adc_init(){
	ADMUX |= (1 << REFS0); // AV_cc
	ADMUX |= (1 << MUX0); // ADC Channel 1
	//ADCSRA |= (1 << ADIE); // ADC Complete Interrupt 
	ADCSRA |= (1 << ADPS2)|(1 << ADPS1);
}



uint16_t adc_read(){
	ADCSRA |= (1 << ADSC);
	
	while ((ADCSRA & (1 << ADIF)) == 0){
		;
	}
	uint16_t adc_val = ((ADCL << 0) | (ADCH << 8));
	adc_val = (adc_val * VREF)/(ADC_RES);
	return adc_val;
}