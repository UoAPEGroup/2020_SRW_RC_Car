/*
 * pi_c.c
 *
 * Created: 18/01/2021 11:39:46 am
 *  Author: npat692
 */ 

#include "pi_c.h"


void setup(){
	setPoint = 5000;
}

void loop(){
	input = adc_read();
	output = computePID(input);
	_delay_ms(100);
	/*if(input > setPoint){
		output_1 = input + output;
	}
	else{
		output_1 = output + input;
	}*/
	output_1 = output + input;
	analog_write(output_1);
}

uint16_t computePID(uint16_t  input){
	k_p = 0.5;
	/*if (input > setPoint){
		error = input - setPoint;
	}
	else {
		error = setPoint - input;
	}*/
	sampling_t = 100;
	error = setPoint - input;
	integrator = integrator + (1/2) * k_i * sampling_t * (error + prevError);
	int16_t out = k_p * error + integrator;
	prevError = error;
	return out;
}