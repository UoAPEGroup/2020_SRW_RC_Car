/*
 * adc.c
 *
 * Created: 12/10/2020 9:55:45 AM
 * Author: Kimsong Lor
 */ 

#include "adc.h"

//ADC read counters
uint8_t voltage_counter = 0;
uint8_t current_counter = 0;
uint8_t temp1_counter = 0;
uint8_t temp2_counter = 0;
uint8_t temp3_counter = 0;

//ADC transfer booleans
bool adc_full[ADC_used] = {false}; //set all booleans to false 

//ADC read arrays
uint8_t adc_voltage[SAMPLING_SIZE];
uint8_t adc_current[SAMPLING_SIZE];
uint8_t adc_temp1[SAMPLING_SIZE];
uint8_t adc_temp2[SAMPLING_SIZE];
uint8_t adc_temp3[SAMPLING_SIZE];

ISR(ADC_vect) {
	if (voltage_counter < SAMPLING_SIZE) {
		adc_voltage[voltage_counter] = adc_convert(adc_read(ADC0));
		voltage_counter++;
	}
	else if (current_counter < SAMPLING_SIZE) {
		adc_current[current_counter] = adc_convert(adc_read(ADC1));
		current_counter++;
	}
	else if (temp1_counter < SAMPLING_SIZE) {
		adc_temp1[temp1_counter] = adc_convert(adc_read(ADC2));
		temp1_counter++;
	}
	else if (temp2_counter < SAMPLING_SIZE) {
		adc_temp2[temp2_counter] = adc_convert(adc_read(ADC3));
		temp2_counter++;
	}
	else if (temp3_counter < SAMPLING_SIZE) {
		adc_temp3[temp3_counter] = adc_convert(adc_read(ADC4));
		temp3_counter++;
	}
	//reset all counters to 0
	else {
		voltage_counter = 0;
		current_counter = 0;
		temp1_counter = 0;
		temp2_counter = 0;
		temp3_counter = 0;
	}
}

void adc_init() {
	ADMUX |= (1<<REFS0); //Reference voltage selected to be AVCC
	
	ADCSRA |= (1<<ADEN); //ADC enabled
	ADCSRA |= (1<<ADATE); //ADC auto trigger enabled
	ADCSRA |= (1<<ADIE); //ADC interrupt enabled
	ADCSRA |= (1<<ADPS2) | (1<<ADPS0); //ADC prescaler = 32, system clock = 8Mhz, adc clock = 250kHz
	
	ADCSRB |= (1<<ADTS2) | (1<<ADTS0); //ADC auto trigger source = Timer/Counter1 compare match B
	
	sei(); //enable global interrupt
}

uint16_t adc_read(uint8_t channel) {
	ADMUX &= ~( (1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0) ); //clearing MUX register
	ADMUX |= channel; //select the adc channel
	
	return ADC; //return the ADC value from the ADCL and ADCH registers
}

//convert the raw adc value to original value by multiplying with Vstep in mV
uint32_t adc_convert(uint16_t raw_ADC) {  
	uint32_t original_V = raw_ADC*(V_ref/A_int);  //reference voltage, amplitude interval
	return original_V;							
}

void transmit_adc_average(uint8_t bool_arr[], uint8_t adc0_arr[], uint8_t adc1_arr[], uint8_t adc2_arr[], uint8_t adc3_arr[], uint8_t adc4_arr[],) {
	if (bool_arr[0] == true) {
		
	}
}