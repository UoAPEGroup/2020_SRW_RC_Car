/*
 * pi.c
 *
 * Created: 28/01`/2021 4:17:43 pm
 *  Author: npat692
 */ 

#include "pi_controller.h"


// PI Controller Setup 
void pi_setup(){
	IN_1_OFF;
	IN_2_OFF;
	k_p = K_P;
	k_i = K_I;
}

// PI Controller Function
void pi_controller(){
	//led_toggle();
	
	input = adc_read(); // Reads current input
	
	set_output = compute_pi(input); // Calculates PI
	
	// Anti-wind-up for integrator
	if(set_output > MAX_LIMIT){
		set_output = MAX_LIMIT;
	}
	/*
	else if (set_output < MIN_LIMIT){
		set_output = MIN_LIMIT;
	}
	*/
	
	// Sets the duty cycle on IN_1 or IN_2
	if (set_output > 0){ // Turning Right (positive error)
		IN_1_OFF;
		set_duty_cycle(set_output); 
		IN_2_ON;
	} 
	else{				// Turning Left (negative error)
		IN_2_OFF;
		set_duty_cycle(set_output * (-1)); 
		IN_1_ON;
	}
}

// PI Controller Function: Calculates Error
int16_t compute_pi(uint16_t input){	
	error = set_point_angle - input; // Proportional
	
	// Disabled for Proteus
	//integrator += (0.5) * k_i * SAMPLING_TIME * (error + prev_error); // Integrator
	
	int16_t out = k_p * error + integrator; // PI Sum
	
	// Ignores minor errors
	if ((out < 100) && (out > -100)){
		out = 0;
	}
	
	prev_error = error; // Saves error for integration
	return out;
}
