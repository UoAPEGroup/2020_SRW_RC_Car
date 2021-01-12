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