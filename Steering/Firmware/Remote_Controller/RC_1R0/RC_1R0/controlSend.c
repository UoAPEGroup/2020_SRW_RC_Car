/*
 * controlSend.c
 *
 * Created: 18/01/2021 2:48:23 PM
 *  Author: htom380
 */ 

#include <stdint.h>
#include <stdbool.h>

#include "controlSend.h"
#include "inputStates.h"

volatile uint8_t sendValue = 0b00000000;
volatile bool RTS_flag = false;
 
void instructionSend(uint8_t str_data, uint8_t accel_data, uint8_t dir_data) {
	
	sendValue = 0b00000000;
	
	switch (str_data)
	{
		case STR_FULL_L:
			sendValue &= ~(1 << TURN);
			sendValue |= (1 << FULL);
			break;
		
		case STR_MED_L:
			sendValue &= ~(1 << TURN);
			sendValue |= (1 << HALF);
			break;
		
		case STR_FULL_R:
			sendValue |= (1 << TURN);
			sendValue |= (1 << FULL);
			break;
		
		case STR_MED_R:
			sendValue |= (1 << TURN);
			sendValue |= (1 << HALF);
			break;
			
		case STR_STRGHT:
			sendValue &= ~(1 << TURN);
			sendValue &= ~(1 << FULL);
			sendValue &= ~(1 << HALF);
			break;
	}
	
	switch (accel_data) 
	{
		case ACCEL_HIGH:
			sendValue |= (1 << SPEED_HIGH);
			break;
		
		case ACCEL_MEDIUM:
			sendValue |= (1 << SPEED_MED);
			break;
			
		case ACCEL_LOW:
			sendValue |= (1 << SPEED_LOW);
			break;
			
		case ACCEL_NONE:
			sendValue &= ~(1 << SPEED_HIGH);
			sendValue &= ~(1 << SPEED_MED);
			sendValue &= ~(1 << SPEED_LOW);
			break;
	}
	
	switch (dir_data)
	{
		case FORWARD:
			sendValue &= ~(1 << DRT);
			break;
			
		case REVERSE:
			sendValue |= (1 << DRT);
			break;
		
	}
	
	
}

void set_RTS_flag(bool flag_val) {
	RTS_flag = flag_val;
}


bool check_RTS_flag() {
	return RTS_flag;
}