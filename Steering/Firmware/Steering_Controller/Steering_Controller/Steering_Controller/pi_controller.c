/*
 * pi.c
 *
 * Created: 28/01`/2021 4:17:43 pm
 *  Author: npat692
 */ 

#include "pi_controller.h"

#include "uart.h"
#include <stdio.h>//
#include <string.h>// For debugging
char input_buffer[20];//

volatile int16_t error;
volatile int16_t prev_error;
volatile int16_t input;
volatile int16_t integrator;
volatile int16_t set_output;

// PI Controller Function
void pi_controller(){
	//led_toggle();
	
	input = adc_read(); // Reads current input
	
	set_output = compute_pi(input); // Calculates PI
	
	// Anti-wind-up for integrator
	if(set_output > 5000){
		set_output = 5000;
	}
 	//sprintf(input_buffer, "Input:	%i \n\r", input);
 	//usart0_transmit_string(input_buffer);
	/*
	// Disabled for Proteus (Uses calibration to find the range)
	// Anti-wind-up for integrator
	if(set_output > turn_range){
		set_output = turn_range;
	}
	else if (set_output < turn_range * (-1)){
		set_output = turn_range * (-1);
	}*/
	
	//sprintf(input_buffer, "Input:	%i \n\r", input);
	//usart0_transmit_string(input_buffer);
	
	
	// Sets the duty cycle on IN_1 or IN_2
	if(set_output > 0){ // Turning Right (positive error)
		set_duty_cycle_IN2(set_output);
	}
	else{				// Turning Left (negative error)
		set_duty_cycle_IN1(set_output * (-1));
	}
	/*
	if (set_output > 0){ // Turning Right (positive error)
		IN_1_OFF;
		IN_2_ON;
		sprintf(input_buffer, "Input:	%i \n\r", (set_output));
		usart0_transmit_string(input_buffer);
		set_duty_cycle(set_output);
	}
	else{				// Turning Left (negative error)
		IN_2_OFF;
		IN_1_ON;
		sprintf(input_buffer, "Input:	%i \n\r", (set_output));
		usart0_transmit_string(input_buffer);
		set_duty_cycle(set_output * (-1));

	}*/
}

// PI Controller Function: Calculates Error
int16_t compute_pi(uint16_t input){	
	error = set_point_angle - input; // Proportional
	
	// Disabled for Proteus
	//integrator += (0.5) * K_I * SAMPLING_TIME * (error + prev_error); // Integrator
	
	int16_t out = K_P * error + integrator; // PI Sum
	
	// Ignores minor errors
 	if ((out < 100) && (out > -100)){
 		out = 0;
 	}
	
	prev_error = error; // Saves error for integration
	
	return out;
}
