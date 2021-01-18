/*
 * adc_pwm.c
 *
 * Created: 18/01/2021 11:52:03 am
 *  Author: npat692
 */ 

#include "adc_pwm.h"

double adc_read(){
	ADCSRA |= (1 << ADSC);
		
	while ((ADCSRA & (1 << ADIF)) == 0){
		;
	}
	double adc_val = ((ADCL << 0) | (ADCH << 8));
	
	return (adc_val * 5000)/(1023);
}

void analog_write(double value){
	OCR0A = 0xFF;
	OCR0B = 255;
}