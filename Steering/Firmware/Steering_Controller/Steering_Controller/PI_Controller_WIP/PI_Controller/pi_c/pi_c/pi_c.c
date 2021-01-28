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
	setPoint = 3500;
}

void loop(){
	input = adc_read();
	output = computePID(input);
	set_output = output + input;
	// Anti-wind-up
	if(output > MAX_LIMIT){
		output = 5000;
	}
	else if (output < MIN_LIMIT){
		output = 0;
	}
	analog_write(set_output);
	//printval();
}

int16_t computePID(uint16_t input){
	k_p = 0.8;
	k_i = 2;
	
	sampling_t = 0.001; // 1 ms interrupt
	error = setPoint - input;
	
	integrator = integrator + (1/2) * k_i * sampling_t * (error + prevError);
	
	int16_t out = k_p * error + integrator;
	/*if ((out < 100)&&(out > -100)){
		out = 0;
	}
	*/
	sprintf(input_buffer, "Input:	%i \n\r", input);
	usart0_transmit_string(input_buffer);
	sprintf(input_buffer, "Set:	%i \n\r", setPoint);
	usart0_transmit_string(input_buffer);
	sprintf(error_buffer, "Error:	%i \n\r", out);
	usart0_transmit_string(error_buffer);
	prevError = error;
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