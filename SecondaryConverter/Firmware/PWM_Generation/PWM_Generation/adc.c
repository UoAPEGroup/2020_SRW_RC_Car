/*
 * adc.c
 *
 * Created: 17/12/2020 12:52:36 PM
 *  Author: Manoj
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"


#define REF_VOLTAGE 12
#define RESOLUTION 1024

static volatile int16_t data_array[100];
static volatile uint8_t count = 0; 

ISR(ADC_vect) {
	
	int16_t data = ADC;
	data_array[count] = (int32_t)data * REF_VOLTAGE/RESOLUTION;
	count++;
	
}

void adc_init() {
	ADMUX = 0b01000000;
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (1<<ADSC);
	ADCSRA |= (1<<ADATE);
	ADCSRA |= (1<<ADIE);
}