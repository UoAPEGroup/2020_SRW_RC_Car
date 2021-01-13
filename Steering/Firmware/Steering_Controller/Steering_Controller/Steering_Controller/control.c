/*
 * control.c
 *
 * Created: 12/01/2021 6:46:09 p.m.
 *  Author: npat692
 */ 

#include "control.h"

void read_data() {
	set_direction(); 
	set_speed();
	toggle_st_int();
	set_turn_state();
}

void set_direction(){
	if (BACKWARD_H){ 
		DRT_BCK;
		tx_debug(48);
	}
	else{
		DRT_FWD;
		tx_debug(49);
	}
}

void set_speed(){
	switch (input_data){
		/*
		case LOW_H:
		set_low_speed();
		break;
		*/
		case MED_H:
		set_med_speed();
		tx_debug(50);
		break;
		
		case HIGH_H:
		set_high_speed();
		tx_debug(51);
		break;
		
		default:
		set_no_speed();
		tx_debug(52);
		break;
	}
}

void set_turn_set(){
	// RIGHT TURN
	if(RIGHT_H){
		if(HALF_TURN_H){
			turn_state = RIGHT_HALF;
			tx_debug(54);
		} 
		else if (FULL_TURN_H){
			turn_state = RIGHT_FULL;
		}
	} // LEFT TURN
	else{
		if(HALF_TURN_H){
			turn_state = LEFT_HALF;
		}`
		else if (FULL_TURN_H){
			turn_state = LEFT_FULL;
		}
		else{
			tx_debug(55);
			turn_state = STRAIGHT;
		}
	}
}













/*
void set_speed_left(char input_data){
	DRT_FWD;
	
	if (UDR0 && (1 << 0)){
		
	}
	switch (input_data){
		
		// HALF 
		case HALF_L_NO_S:
		set_no_speed();
		turn_state = LEFT_HALF;
		break;
		
		case HALF_L_FMED_S:
		set_med_speed();
		turn_state = LEFT_HALF;
		break;
		
		case HALF_L_FHIGH_S:
		set_high_speed();
		turn_state = LEFT_HALF;
		break;
		
	    // FULL
		case FULL_L_NO_S:
		set_no_speed();
		turn_state = LEFT_FULL;
		break;
		
		case FULL_L_FMED_S:
		set_med_speed();
		turn_state = LEFT_FULL;
		break;
		
		case FULL_L_FHIGH_S:
		set_high_speed();
		turn_state = LEFT_FULL;
		break;
	}
}


void set_forward_left(char input_data){
	DRT_BCK;
	switch (input_data){
		
		// HALF
		case HALF_L_NO_S:
		set_no_speed();
		turn_state = LEFT_HALF;
		break;
		
		case HALF_L_FMED_S:
		set_med_speed();
		turn_state = LEFT_HALF;
		break;
		
		case HALF_L_FHIGH_S:
		set_high_speed();
		turn_state = LEFT_HALF;
		break;
		
		// FULL
		case FULL_L_NO_S:
		set_no_speed();
		turn_state = LEFT_FULL;
		break;
		
		case FULL_L_FMED_S:
		set_med_speed();
		turn_state = LEFT_FULL;
		break;
		
		case FULL_L_FHIGH_S:
		set_high_speed();
		turn_state = LEFT_FULL;
		break;
	}
}

*/
void toggle_st_int(){
	STATE_INT_H;
	STATE_INT_L;
}

void set_no_speed(){
	SPD_0_L;
	SPD_1_L;
	toggle_st_int();
}

void set_low_speed(){
	SPD_0_H;
	SPD_1_L;
	toggle_st_int();
}

void set_med_speed(){
	SPD_0_L;
	SPD_1_H;
	toggle_st_int();
}

void set_high_speed(){
	SPD_0_H;
	SPD_1_H;
	toggle_st_int();
}


