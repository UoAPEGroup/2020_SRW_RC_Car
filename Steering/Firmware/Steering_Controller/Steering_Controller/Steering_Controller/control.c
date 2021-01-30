/*
 * control.c
 *
 * Created: 12/01/2021 6:46:09 p.m.
 *  Author: npat692
 */ 

#include "control.h"
#include "led.h"
#include "steering.h"

void pin_init(){
	DDRC |= (1 << PORTC5)|(1 << PORTC2)|(1 << PORTC1);
	STATE_INT_L;
}

void read_data() {
	//led_toggle();
	set_direction(); 
	set_speed();
	STATE_INT_TOGGLE;
	set_turn_angle();
}

void set_direction(){
	if (BACKWARD_H){ 
		DRT_BCK;
	}
	else{
		DRT_FWD;
	}
}


void set_speed(){
	if (MED_H){
		set_med_speed();
	}
	else if (HIGH_H){
		set_high_speed();
	}
	else{
		set_no_speed();
	}
}

void set_turn_angle(){
	// RIGHT TURN
	if(RIGHT_H){
		if(HALF_TURN_H){
			set_point_angle = half_r_turn;
		} 
		else if (FULL_TURN_H){
			set_point_angle = full_r_turn;
		}
	} // LEFT TURN
	else{
		if(HALF_TURN_H){
			set_point_angle = half_l_turn;
		}
		else if (FULL_TURN_H){
			set_point_angle = full_l_turn;
		}
		else{
			set_point_angle = straight_turn;
		}
	}
}

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


