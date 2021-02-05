/*
 * pi_c.c
 *
 * Created: 18/01/2021 11:39:46 am
 *  Author: npat692
 */ 

#include "pi_c.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>

char output_buffer[20];
char input_buffer[20];
char error_buffer[20];

void setup(){
	setPoint = 2000; // Desired output
}

void pi_controller(){
	input = adc_read(); // Reads current input
	
	output = compute_pi(input); // Calculates PI 
	
	sprintf(input_buffer, "Input:	%i \n\r", input);
	usart0_transmit_string(input_buffer);
	
	// Anti-wind-up
	if(output > MAX_LIMIT){
		output = 5000;
	}
	else if (output < MIN_LIMIT){
		output = 0;
	}
	
	set_output = output + input; // Calculates the output value
	
	// Set output value
	analog_write(set_output);
}

int16_t compute_pi(uint16_t input){
	k_p = K_P;
	k_i = K_I;
	
	sampling_t = 0.001; // 1 ms interrupt
	
	error = setPoint - input; // Proportional 
	
	integrator = integrator + (0.5) * k_i * sampling_t * (error + prevError); // Integrator
	
	int16_t out = k_p * error + integrator; // PI Sum
	
	// Ignores minor errors
	/*if ((out < 100) && (out > -100)){
		out = 0;
	}*/
	
	prevError = error; // Saves error for integration
	return out;
}

void printval(){
	sprintf(input_buffer, "Input:	%i \n\r", input);
	usart0_transmit_string(input_buffer);
	sprintf(error_buffer, "Error:	%i \n\r", output);
	usart0_transmit_string(error_buffer);
	sprintf(output_buffer, "Set Output:	%i \n\r", set_output);
	usart0_transmit_string(output_buffer);
	usart0_transmit_string("\n");
}