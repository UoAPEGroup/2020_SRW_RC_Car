/*
 * pi_c.c
 *
 * Created: 18/01/2021 11:39:46 am
 *  Author: npat692
 */ 

#include "pi_c.h"


void setup(){
	setPoint = 4500;
}

void loop(){
	input = adc_read();
	output = computePID(input);
	output_1 = output;

	/*if(input > setPoint){
		output_1 = input + output;
	}
	else{
		output_1 = output + input;
	}*/

	analog_write(output_1);
	_delay_ms(1000);
}

uint16_t computePID(uint16_t  input){
	k_p = 3;
	k_i = 2;
	/*if (input > setPoint){
		error = input - setPoint;
	}
	else {
		error = setPoint - input;
	}*/
	sampling_t = 1000;
	error = setPoint - input;
	integrator = 0;//integrator + (1/2) * k_i * sampling_t * (error + prevError);
	
	int16_t out = k_p * error + integrator;
	/*
	if ((input + out) > 5000){
		out = 5000;
	} else if ((input + out) < 0){
		out = 0;
	}*/
	
	prevError = error;
	return out;
}