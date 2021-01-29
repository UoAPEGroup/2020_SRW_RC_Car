/*
 * pi.c
 *
 * Created: 28/01`/2021 4:17:43 pm
 *  Author: npat692
 */ 

#include "pi_controller.h"
#include "adc.h"
#include "led.h"

void pi_controller(){
	led_toggle();
	
	setPoint = 3000;
	input = adc_read(); // Reads current input
	
	output = compute_pi(input); // Calculates PI
	
	set_output = output + input; // Calculates the output value
	IN_1_ON;
	// Anti-wind-up
	if(output > MAX_LIMIT){
		output = MAX_LIMIT;
	}
	else if (output < MIN_LIMIT){
		output = MIN_LIMIT;
	}
	
	
	
	if (output < input){
		IN_1_OFF;
		IN_2_ON;
	} else{
		IN_2_OFF;
		IN_1_ON;
	}
	
	// Set output value
	//set_duty(set_output);
}

int16_t compute_pi(uint16_t input){
	k_p = K_P;
	k_i = K_I;
	
	// 1 ms interrupt
	
	error = setPoint - input; // Proportional
	
	integrator = integrator + (1/2) * k_i * SAMPLING_TIME * (error + prevError); // Integrator
	
	int16_t out = k_p * error + integrator; // PI Sum
	
	// Ignores minor errors
	if ((out < 100) && (out > -100)){
		out = 0;
	}
	
	prevError = error; // Saves error for integration
	return out;
}
