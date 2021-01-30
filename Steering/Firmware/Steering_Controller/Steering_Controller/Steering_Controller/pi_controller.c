/*
 * pi.c
 *
 * Created: 28/01`/2021 4:17:43 pm
 *  Author: npat692
 */ 

#include "pi_controller.h"
#include "adc.h"
#include "led.h"
#include "pwm.h"

void pi_controller(){
	led_toggle();
	
	set_point = 3000;
	
	input = adc_read(); // Reads current input
	
	output = compute_pi(input); // Calculates PI
	
	set_output = output; // Calculates the output value
	
	// Anti-wind-up for integrator
	if(set_output > MAX_LIMIT){
		set_output = MAX_LIMIT;
	}
	/*
	else if (set_output < MIN_LIMIT){
		set_output = MIN_LIMIT;
	}
	*/
	
	if (set_output > 0){
		IN_1_OFF;
		IN_2_ON;
		set_duty_cycle(set_output);
	} else{
		IN_2_OFF;
		IN_1_ON;
		set_duty_cycle(set_output * (-1));
	}
}

int16_t compute_pi(uint16_t input){
	k_p = K_P;
	k_i = 0.2;
	
	// 1 ms interrupt
	
	error = set_point - input; // Proportional
	
	//integrator += (0.5) * k_i * SAMPLING_TIME * (error + prev_error); // Integrator
	
	int16_t out = k_p * error + integrator; // PI Sum
	
	// Ignores minor errors
	if ((out < 100) && (out > -100)){
		out = 0;
	}
	
	prev_error = error; // Saves error for integration
	return out;
}
