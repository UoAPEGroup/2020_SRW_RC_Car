/*
 * adc_pwm.c
 *
 * Created: 18/01/2021 11:52:03 am
 *  Author: npat692
 */ 

#include "adc_pwm.h"
#include "pi_c.h"

volatile uint16_t t_on;
volatile uint16_t adc_val;
int16_t analog_write_val;

uint16_t adc_read(){
	ADCSRA |= (1 << ADSC);
	while ((ADCSRA & (1 << ADIF)) == 0){
		;
	}
	adc_val = ((ADCL << 0) | (ADCH << 8));
	adc_val = ((uint32_t) adc_val * VREF)/(1024);
	return adc_val;
}

void analog_write(int16_t value){
	analog_write_val = value;
	t_on =	(((int32_t)value*255)/VREF);
	if (t_on > 255){
		t_on = 255;
	}
	OCR0A = t_on;
}