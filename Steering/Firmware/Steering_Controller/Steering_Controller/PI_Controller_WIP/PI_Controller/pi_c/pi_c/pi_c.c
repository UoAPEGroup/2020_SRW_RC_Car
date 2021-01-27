/*
 * pi_c.c
 *
 * Created: 18/01/2021 11:39:46 am
 *  Author: npat692
 */ 

#include "pi_c.h"


void setup(){
	setPoint = 4000;
}

void loop(){
	input = adc_read();
	output = computePID(input);
	output_1 = output+input;
	
	// Anti-wind-up
	if(output_1 > MAX_LIMIT){
		output_1 = 5000;
	}
	else if (output_1 < MIN_LIMIT){
		output_1 = 0;
	}
	analog_write(output+input);
}

int16_t computePID(uint16_t input){
	k_p = 0.8;
	k_i = 2;
	/*if (input > setPoint){
		error = input - setPoint;
	}
	else {
		error = setPoint - input;
	}*/
	sampling_t = 1; // 1 ms interrupt
	error = setPoint - input;
	
	integrator = integrator + (1/2) * k_i * sampling_t * (error + prevError);
	
	int16_t out = k_p * error + integrator;
	if ((out < 100)&&(out > -100)){
		out = 0;
	}

	prevError = error;
	return out;
}