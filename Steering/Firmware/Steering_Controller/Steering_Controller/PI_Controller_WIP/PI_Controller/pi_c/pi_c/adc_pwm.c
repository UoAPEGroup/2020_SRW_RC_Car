/*
 * adc_pwm.c
 *
 * Created: 18/01/2021 11:52:03 am
 *  Author: npat692
 */ 

#include "adc_pwm.h"
volatile uint8_t t_on;
uint16_t adc_val;
int16_t analog_write_val;

double adc_read(){
	ADCSRA |= (1 << ADSC);
		
	while ((ADCSRA & (1 << ADIF)) == 0){
		;
	}
	adc_val = ((ADCL << 0) | (ADCH << 8));
	adc_val = ((uint32_t) adc_val * 5000)/(1023);
	return adc_val;
}

void analog_write(int16_t value){
	analog_write_val = value;
	t_on =	(((int32_t)value*255)/5000);
	if (value >= 5000){
		t_on = 255;
	}
	OCR0A = t_on;
	//OCR0B = 255;
}