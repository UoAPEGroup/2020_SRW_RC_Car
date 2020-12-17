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
	
	int16_t data = ADC; //Grab data from ADC
	data_array[count] = (int32_t)data * REF_VOLTAGE/RESOLUTION; //Convert to actual voltage value
	count++; //Increment array slot
	
	if(count == 100) {
		//Do PID calculations/make function call to PID
		count = 0;
	}
	
}

void adc_init() {
	ADMUX = 0b01000000; //Set reference voltage to external
	ADCSRA |= (1<<ADEN); //Start ADC
	ADCSRA |= (1<<ADSC); //Start first conversion
	ADCSRA |= (1<<ADATE); //Set autotrigger (freerunning)
	ADCSRA |= (1<<ADIE); // Set interrupt enable
}