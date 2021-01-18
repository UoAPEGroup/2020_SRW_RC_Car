/*
 * control.c
 *
 * Created: 12/01/2021 6:46:09 p.m.
 *  Author: npat692
 */ 

#include "control.h"
#include "led.h"

void pin_init(){
	DDRC |= (1 << PORTC5)|(1 << PORTC2)|(1 << PORTC1);
	STATE_INT_L;
}

void read_data() {
	//led_toggle();
	set_direction(); 
	set_speed();
	STATE_INT_TOGGLE;
	set_turn_state();
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
	/*
	switch (input_data){
		case (MED_H):
		set_med_speed();
		break;
		
		case (HIGH_H):
		set_high_speed();
		break;
		
		default:
		
		break;
	}*/
}

void set_turn_set(){
	// RIGHT TURN
	if(RIGHT_H){
		if(HALF_TURN_H){
			turn_state = RIGHT_HALF;
		} 
		else if (FULL_TURN_H){
			turn_state = RIGHT_FULL;
		}
	} // LEFT TURN
	else{
		if(HALF_TURN_H){
			turn_state = LEFT_HALF;
		}
		else if (FULL_TURN_H){
			turn_state = LEFT_FULL;
		}
		else{
			turn_state = STRAIGHT;
		}
	}
}

void set_no_speed(){
	SPD_0_L;
	SPD_1_L;
}

void set_low_speed(){
	SPD_0_H;
	SPD_1_L;
}

void set_med_speed(){
	SPD_0_L;
	SPD_1_H;
}

void set_high_speed(){
	SPD_0_H;
	SPD_1_H;
}


