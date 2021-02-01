/*
 * pi.c
 *
 * Created: 28/01`/2021 4:17:43 pm
 *  Author: npat692
 */ 

#include "pi_controller.h"


// PI Controller Setup 
void pi_setup(){
	k_p = K_P;
	k_i = K_I;
}

// PI Controller Function
void pi_controller(){
	//led_toggle();
	set_point_angle = 3000;
	input = adc_read(); // Reads current input
	
	set_output = compute_pi(input); // Calculates PI
	
	// Anti-wind-up for integrator
	if(set_output > 5000){
		set_output = turn_range;
	}
	
	/*
	// Disabled for Proteus
	// Anti-wind-up for integrator
	if(set_output > turn_range){
		set_output = turn_range;
	}
	else if (set_output < turn_range * (-1)){
		set_output = turn_range * (-1);
	}*/

	// Sets the duty cycle on IN_1 or IN_2
	if(set_output > 0){ // Turning Right (positive error)
		set_duty_cycle_IN2(set_output);
	}
	else{				// Turning Left (negative error)
		set_duty_cycle_IN1(set_output * (-1));
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
