/*
 * adc.c
 *
 * Created: 16/12/2020 10:13:38 am
 *  Author: achu072
 */ 
#include "adc.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define ARRAY_SIZE 10

//global variables
static volatile uint8_t adc_read_count = 0;

static volatile uint32_t temp1_adc[ARRAY_SIZE];
static volatile uint32_t temp2_adc[ARRAY_SIZE];
static volatile uint32_t temp3_adc[ARRAY_SIZE];
static volatile uint32_t isens_adc[ARRAY_SIZE];
static volatile uint32_t vsens_adc[ARRAY_SIZE];

//initial set up of ADC
void adc_init()
{
	ADMUX |= (1 << REFS0);												//select AVcc reference
	ADC_CH_TEMP1;														//start reading from TEMP1
	ADC_ENABLE;															//enable ADC
	ADCSRA |= (1 << ADATE);												//enable auto-triggering
	ADCSRA |= (1 << ADIE);												//enable conversion complete interrupt
	ADCSRA |= ((1 << ADPS2) | (1 << ADPS0));							//set /32 prescaler -> ADC clk = 250kHz
	ADCSRB |= ((1 << ADTS2) | (1 << ADTS0));							//start conversion on timer1 overflow
}

//ADC conversion complete ISR
ISR(ADC_vect)
{	
	if (adc_read_count < 10) {
		TIMER1_COMPB_CLR;
		temp1_adc[adc_read_count] = ADC;								
		adc_read_count++;
	} else if (adc_read_count == 10) {
		TIMER1_COMPB_CLR;
		ADC_CH_CLR;
		ADC_CH_TEMP2;													
		adc_read_count++;
	} else if ((adc_read_count > 10) && (adc_read_count < 21)) {
		TIMER1_COMPB_CLR;
		temp2_adc[adc_read_count - 11] = ADC;
		adc_read_count++;
	} else if (adc_read_count == 21) {
		TIMER1_COMPB_CLR;
		ADC_CH_CLR;
		ADC_CH_TEMP3;
		adc_read_count++;
	} else if ((adc_read_count > 21) && (adc_read_count < 32)) {
		TIMER1_COMPB_CLR;
		temp3_adc[adc_read_count - 22] = ADC;
		adc_read_count++;
	} else if (adc_read_count == 32) {
		TIMER1_COMPB_CLR;
		ADC_CH_CLR;
		ADC_CH_ISENS1;
		adc_read_count++;
	} else if ((adc_read_count > 32) && (adc_read_count < 43)) {
		TIMER1_COMPB_CLR;
		isens_adc[adc_read_count - 33] = ADC;
		adc_read_count++;
	} else if (adc_read_count == 43) {
		TIMER1_COMPB_CLR;
		ADC_CH_CLR;
		ADC_CH_VSENS1;
		adc_read_count++;
	} else if ((adc_read_count > 43) && (adc_read_count < 54)) {
		TIMER1_COMPB_CLR;
		vsens_adc[adc_read_count - 44] = ADC;
		adc_read_count++;
	} else if (adc_read_count == 54) {
		TIMER1_COMPB_CLR;
		ADC_CH_CLR;
		ADC_CH_TEMP1;
		adc_read_count = 0;
	} 
}