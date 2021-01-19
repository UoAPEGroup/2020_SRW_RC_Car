/*
 * adc.c
 *
 * Created: 16/12/2020 4:03:15 pm
 *  Author: yxin683
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "Calculations.h"


static volatile uint16_t checkADC = 0;

static volatile uint8_t channelReading = 0; //change the ADC channel to read from

ISR(ADC_vect) {
	
	//clear timer1 compare match B flag
	TIFR1 |= (1 << OCF1B);
	
	//toggle led
	//PORTD ^= (1 << 1);
	
	switch (channelReading) {
		
		case 0:
		//read and store the current values
			addCurrent(ADC);
			ADMUX &= 0xF0;
			ADMUX |= (1 << MUX0); //switch to reading from adc channel 1 (voltage)
			channelReading = 1;
		break;
		
		case 1:
		//read and store the voltage values
			addVoltage(ADC);
			ADMUX &= 0xF0;
			ADMUX &= ~(1 << MUX1); //switch to reading from adc channel 0 (current)
			channelReading = 0;
		break;
	}
	
}

void adc_init() {
	
	//Set reference to Vcc, initial channel to 0
	ADMUX |= (1 << REFS0);
	//enable the ADC and the interrupt
	//set ADC clock frequency to 125kh (64 prescale)
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1);
	//set trigger source to timer/timer1 compare match b
	ADCSRB |= (1 << ADTS2) | (1 << ADTS0);
	
}

