/*
 * pi.c
 *
 * Created: 28/01/2021 4:17:43 pm
 *  Author: npat692
 */ 

#include "global.h"

#include "pi_controller.h"
#include "adc.h"
#include "pwm.h"

// PI Controller Variables
static volatile int16_t error;
static volatile int16_t prev_error;
static volatile int16_t input;
static volatile int16_t integrator;
static volatile int16_t set_output;


#include <stdio.h> //
#include <string.h> //
char input_buffer[20]; //

// PI Controller Function
void pi_controller(){
	input = adc_read(); // Reads current input
	
	set_output = compute_pi(input); // Calculates PI
	
	// Disabled for Proteus (Uses calibration to find the range)
	// Anti-wind-up for integrator
 	if(set_output > turn_range){
 		set_output = turn_range;
 	}
 	else if (set_output < turn_range * (-1)){
 		set_output = turn_range * (-1);
 	}

	// Sets the duty cycle on IN_1 or IN_2
	if(set_output < 0){ // Turning Left (negative error)
		set_duty_cycle_IN1(set_output * (-1));
	}
	else{				// Turning Right (positive error)
 		set_duty_cycle_IN2(set_output);
	}
}

// PI Controller Function: Calculates Error
int16_t compute_pi(uint16_t input){	
	error = set_point_angle - input; // Proportional
	
	// Disabled for Proteus
	integrator += (0.5) * K_I * SAMPLING_TIME * (error + prev_error); // Integrator
	
	int16_t out = K_P * error + integrator; // PI Sum
	
	prev_error = error; // Saves error for integration
	
	return out;
}
