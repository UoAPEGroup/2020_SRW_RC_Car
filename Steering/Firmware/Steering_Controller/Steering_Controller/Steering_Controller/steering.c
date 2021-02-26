/*
 * steering.c
 *
 * Created: 21/01/2021 11:22:30 am
 *  Author: npat692
 */ 

#include "global.h"
#include "adc.h"
#include "pwm.h"
#include "led.h"
#include "steering.h"
#include <util/delay.h>

// Stores the input value
static volatile uint16_t input;

// DEBUGGING
#include <stdio.h>//
#include <string.h>// For debugging
char input_buffer[20];//

#include "uart.h"

// Stores max/min value
static volatile uint16_t min_val;
static volatile uint16_t max_val;

// Flag
static uint8_t calibration_flag;

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
// - BLACK Wire -> OUT1, and RED Wire -> OUT2
void calibrate_steering(){
	//  Sets maximum and minimum voltage ranges (Disabled for Proteus)
	min_val = MAX_LIMIT;
	max_val = MIN_LIMIT;

	set_duty_cycle_IN2(MAX_LIMIT * 0.7);
	find_ref();
	IN_2_OFF;
	
	set_duty_cycle_IN1(MAX_LIMIT * 0.7);
	find_ref();
	IN_1_OFF;
	
	set_reference_values();
	
	//Straightens wheel
	set_straight_turn();
}

// Reads and sets maximum and minimum values
void find_ref(){
	_delay_ms(1000);
	while(calibration_flag == 0){
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
	
	straight_turn = full_r_turn - full_l_turn;
}

void print_refs(){
	 sprintf(input_buffer, "Min value:	%i \n\r", min_val);
	 usart0_transmit_string(input_buffer);
	  	
	 sprintf(input_buffer, "Max value:	%i \n\r", max_val);
	 usart0_transmit_string(input_buffer);
	
	sprintf(input_buffer, "straight_turn:	%i \n\r", straight_turn);
	usart0_transmit_string(input_buffer);
	
	sprintf(input_buffer, "half_l_turn:	%i \n\r", half_l_turn);
	usart0_transmit_string(input_buffer);
	
	sprintf(input_buffer, "half_r_turn:	%i \n\r", half_r_turn);
	usart0_transmit_string(input_buffer);
	
	sprintf(input_buffer, "turn_range:	%i \n\r", turn_range);
	usart0_transmit_string(input_buffer);
}

// Setters for the PI Controller
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
