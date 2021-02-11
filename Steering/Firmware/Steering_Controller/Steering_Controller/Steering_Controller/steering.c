/*
 * steering.c
 *
 * Created: 21/01/2021 11:22:30 am
 *  Author: npat692
 */ 

#include "steering.h"
#include <util/delay.h>

static volatile uint16_t input;

// DEBUGGING
#include <stdio.h>//
#include <string.h>// For debugging
char input_buffer[20];//

#include "uart.h"

// Reference Angle Voltage values
static uint16_t half_r_turn;
static uint16_t full_r_turn;
static uint16_t half_l_turn;
static uint16_t full_l_turn;
static uint16_t straight_turn;

// Finds reference voltage values for each angle
// Works on two assumptions:
// - Low voltage = Left, High voltage = Right
// - Input pins to motor are correctly connected (E.G so IN1 High = Motor goes left)
void calibrate_steering(){
	//  Sets maximum and minimum voltage ranges (Disabled for Proteus)
	 min_val = MAX_LIMIT;
	 max_val = MIN_LIMIT;
	 
	calibration_flag = 0;
	//sprintf(input_buffer, "Point	%i \n\r", 1);
	//usart0_transmit_string(input_buffer);
	
	//sprintf(input_buffer, "Min value:	%i \n\r", min_val);
	//usart0_transmit_string(input_buffer);
	
	//sprintf(input_buffer, "Max value:	%i \n\r", max_val);
	//usart0_transmit_string(input_buffer);
	
	set_duty_cycle_IN1(MAX_LIMIT-1);
	find_ref();
	IN_1_OFF;
	
	sprintf(input_buffer, "Min value:	%i \n\r", min_val);
	usart0_transmit_string(input_buffer);
	
	sprintf(input_buffer, "Max value:	%i \n\r", max_val);
	usart0_transmit_string(input_buffer);
	
	
	//sprintf(input_buffer, "Passed:	%i \n\r", 1);
	//usart0_transmit_string(input_buffer);
	
	set_duty_cycle_IN2(MAX_LIMIT-1);
	find_ref();
	IN_2_OFF;
	
 	sprintf(input_buffer, "Min value:	%i \n\r", min_val);
 	usart0_transmit_string(input_buffer);
 	
 	sprintf(input_buffer, "Max value:	%i \n\r", max_val);
 	usart0_transmit_string(input_buffer);
	
	set_reference_values();
	
	//Straightens wheel
	set_point_angle = straight_turn;
	
}

// Reads and sets maximum and minimum values
void find_ref(){
	//set_duty_cycle(MAX_LIMIT);
	input = adc_read();  
	while(calibration_flag == 0){
		_delay_ms(1000);
		input = adc_read();
		if(input < min_val){
			min_val = input;
		}
		else if (input > max_val){
			max_val = input;
		}
		else {
			calibration_flag = 1; // If steering motor has turned its maximum angle
		}
	}
	calibration_flag = 0; // Clears flag
}

// Sets up the reference values that are used as set points for the PI Controller
void set_reference_values(){
	full_l_turn = min_val;
	full_r_turn = max_val;
	
	// Reference voltage for moving straight
	straight_turn = (max_val - min_val)/2 + min_val;
	
	// Reference voltage for half left turn
	half_l_turn = (straight_turn - full_l_turn)/2 + full_l_turn;
	
	// Reference voltage for half right turn
	half_r_turn = (full_r_turn - straight_turn)/2 + straight_turn;
	
	// Voltage range for turn
	turn_range = full_r_turn - full_l_turn;
	
	sprintf(input_buffer, "straight_turn:	%i \n\r", straight_turn);
	usart0_transmit_string(input_buffer);
	
	sprintf(input_buffer, "half_l_turn:	%i \n\r", half_l_turn);
	usart0_transmit_string(input_buffer);
	
	sprintf(input_buffer, "half_r_turn:	%i \n\r",half_r_turn);
	usart0_transmit_string(input_buffer);
	
	sprintf(input_buffer, "turn_range:	%i \n\r", turn_range);
	usart0_transmit_string(input_buffer);
}

void set_half_r_turn(){
	set_point_angle = half_r_turn;
}

void set_full_r_turn(){
	set_point_angle = full_r_turn;
}

void set_half_l_turn(){
	set_point_angle = half_l_turn;
}

void set_full_l_turn(){
	set_point_angle = full_l_turn;
}

void set_straight_turn(){
	set_point_angle = straight_turn;
}
