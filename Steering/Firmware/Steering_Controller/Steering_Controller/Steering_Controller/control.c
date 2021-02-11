/*
 * control.c
 *
 * Created: 12/01/2021 6:46:09 p.m.
 *  Author: npat692
 */ 

#include "global.h"
#include "uart.h"
#include "led.h"
#include "steering.h"
#include "control.h"

#include <stdio.h>
#include <string.h>
char input_buffer[20];

// Stores input data
static volatile char input_data;

void pin_init(){
	DDRC |= (1 << PORTC5); // State Interrupt
	DDRC |= (1 << PORTC2)|(1 << PORTC3); // SPD_0 and SPD_1
	DDRC |= (1 << PORTC4); // Direction 
	STATE_INT_L;
}

// Decodes data in the Receiver Buffer
void read_data() {
	
	input_data = UDR0;
	set_direction(); // Sets Direction 
	set_speed(); // Sets Speed 
	
	set_turn_angle(); // Sets turn angle
	
	STATE_INT_TOGGLE; // Triggers state interrupt
	
	tx_debug(input_data); // Echoes back input data (Enabled for testing)
}

// Reads data and sets Direction 
void set_direction(){
	if (BACKWARD_H){  
		DRT_BCK;
	}
	else{
		DRT_FWD;
	}
}

// Reads data and sets Direction
void set_speed(){
	if (LOW_H){
		set_low_speed();
	}
	else if (MED_H){
		set_med_speed();
	}
	else if (HIGH_H){
		set_high_speed();
	}
	else{
		set_no_speed();
	}
}

// Reads data and sets angle for PI controller set point
void set_turn_angle(){
	// RIGHT TURN
	if(RIGHT_H){
		if(HALF_TURN_H){
			set_half_l_turn();
		} 
		else if (FULL_TURN_H){
			set_full_r_turn();
			//set_point_angle = 2700;//
			led_toggle();//
		}
	} // LEFT TURN
	else{
		if(HALF_TURN_H){
			//set_half_l_turn();
			
			set_point_angle = 1700; //
			//led_toggle();// 
			//sprintf(input_buffer, "Set Output:	%i \n\r", set_point_angle); //
			//usart0_transmit_string(input_buffer); //
		}
		else if (FULL_TURN_H){
			set_full_l_turn();
		}
		else{
			set_straight_turn();
		}
	}
}

// Speed setters 
void set_no_speed(){
	SPD_0_H;
	SPD_1_H;
}

void set_low_speed(){
	SPD_0_L;
	SPD_1_H;
}

void set_med_speed(){
	SPD_0_H;
	SPD_1_L;
}

void set_high_speed(){
	SPD_0_L;
	SPD_1_L;
}
