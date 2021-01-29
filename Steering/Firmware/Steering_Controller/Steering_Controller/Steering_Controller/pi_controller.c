/*
 * pi.c
 *
 * Created: 28/01/2021 4:17:43 pm
 *  Author: npat692
 */ 

#include "pi_controller.h"

void pi_controller(){
	input = adc_read(); // Reads current input
	
	output = compute_pi(input); // Calculates PI
	
	set_output = output + input; // Calculates the output value
	
	// Anti-wind-up
	if(output > MAX_LIMIT){
		output = 5000;
	}
	else if (output < MIN_LIMIT){
		output = 0;
	}
	
	// Set output value
	//analog_write(set_output);
}

int16_t compute_pi(uint16_t input){
	k_p = K_P;
	k_i = K_I;
	
	sampling_t = 0.001; // 1 ms interrupt
	
	error = setPoint - input; // Proportional
	
	integrator = integrator + (1/2) * k_i * sampling_t * (error + prevError); // Integrator
	
	int16_t out = k_p * error + integrator; // PI Sum
	
	// Ignores minor errors
	if ((out < 100) && (out > -100)){
		out = 0;
	}
	
	prevError = error; // Saves error for integration
	return out;
}
