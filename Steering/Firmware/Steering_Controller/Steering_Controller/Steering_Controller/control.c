/*
 * control.c
 *
 * Created: 12/01/2021 6:46:09 p.m.
 *  Author: npat692
 */ 

#include "control.h"

void read_data(char input_data) {
	if(input_data >= 65 && input_data <= 72){
		set_forward_left(input_data);
	}
}

void set_forward_left(char input_data){
	switch (input_data){
		case HALF_L_NO_S:
		
		break;
		
		case 0: 
		break;
	}
}
