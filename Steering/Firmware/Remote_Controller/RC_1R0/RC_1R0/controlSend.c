/*
 * controlSend.c
 *
 * Created: 18/01/2021 2:48:23 PM
 *  Author: htom380
 */ 

#include "controlSend.h"
#include "inputStates.h"

volatile uint8_t sendValue = 0b00000000;
 
void instructionSend(uint8_t str_data, uint8_t accel_data, uint8_t dir_data) {
	
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
		
	}
}