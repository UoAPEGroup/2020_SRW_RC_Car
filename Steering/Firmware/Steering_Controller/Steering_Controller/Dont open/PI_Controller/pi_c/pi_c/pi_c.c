/*
 * pi_c.c
 *
 * Created: 18/01/2021 11:39:46 am
 *  Author: npat692
 */ 

#include "pi_c.h"


void setup(){
	setPoint = 0;
}

void loop(){
	input = adc_read();
	output = computePID(input);
	_delay_ms(1000);
	analog_write(output);
}

double computePID(double input){
	k_p = 2;
	error = setPoint - input;
	double out = k_p * error;
	return out;
}