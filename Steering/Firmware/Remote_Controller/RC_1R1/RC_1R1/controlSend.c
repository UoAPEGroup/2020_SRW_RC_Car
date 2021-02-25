/*
 * controlSend.c
 *
 * Created: 18/01/2021 2:48:23 PM
 *  Author: htom380
 */ 

#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>

#include "controlSend.h"
#include "inputStates.h"
#include "adc.h"

volatile uint8_t sendValue = 0b00000000;
volatile bool RTS_flag = false;

volatile uint8_t str_data = 0;
volatile uint8_t accel_data = 0;
volatile uint8_t dir_data = 0;

volatile bool accel_sw_1 = false;
volatile bool accel_sw_2 = false;
volatile bool accel_sw_3 = false;
volatile bool accel_sw_4 = false;

ISR(INT0_vect) {
	if (PIND & (1 << PD2)) {
		dir_data = REVERSE;
	}
	else {
		dir_data = FORWARD;
	}
}

ISR(PCINT0_vect) {
	if (PINB & (1 << PB0)) {
		accel_sw_1 = true;
	}
	else {
		accel_sw_1 = false;
	}
	if (PINB & (1 << PB1)) {
		accel_sw_4 = true;
	}
	else {
		accel_sw_4 = false;
	}
	if (PIND & (1 << PD6)) {
		accel_sw_2 = true;
	}
	else {
		accel_sw_2 = false;
	}
	if (PIND & (1 << PD7)) {
		accel_sw_3 = true;
	}
	else {
		accel_sw_3 = false;
	}
}

void str_data_conversion() {
	uint32_t steering_adc_val = -1;
	//uint32_t steering_adc_val = return_adc_val();
	if (steering_adc_val > ADC_STR_FULL_L) {
		str_data = STR_FULL_L;
	}
	else if (steering_adc_val > ADC_STR_HALF_L) {
		str_data = STR_HALF_L;
	}
	else if (steering_adc_val > ADC_STR_STRGHT) {
		str_data = STR_STRGHT;
	}
	else if (steering_adc_val > ADC_STR_HALF_R) {
		str_data = STR_HALF_R;
	}
	else if (steering_adc_val > ADC_STR_FULL_R) {
		str_data = STR_FULL_R;
	}
}

void accel_data_conversion() {
	if (!accel_sw_1 && accel_sw_2) {
		accel_data = ACCEL_NONE;
	}
	else if (!accel_sw_1 && !accel_sw_2 && accel_sw_3) {
		accel_data = ACCEL_LOW;
	}
	else if (!accel_sw_1 && accel_sw_2) {
		accel_data = ACCEL_MEDIUM;
	}
	else if (!accel_sw_1 && accel_sw_4) {
		accel_data = ACCEL_HIGH;
	}
}

void instructionSend() {
	
	sendValue = 0b00000000;
	
	switch (str_data)
	{
		case STR_FULL_L:
			sendValue &= ~(1 << TURN);
			sendValue |= (1 << FULL);
			break;
		
		case STR_HALF_L:
			sendValue &= ~(1 << TURN);
			sendValue |= (1 << HALF);
			break;
		
		case STR_FULL_R:
			sendValue |= (1 << TURN);
			sendValue |= (1 << FULL);
			break;
		
		case STR_HALF_R:
			sendValue |= (1 << TURN);
			sendValue |= (1 << HALF);
			break;
			
		case STR_STRGHT:
			sendValue &= ~(1 << TURN);
			sendValue &= ~(1 << FULL);
			sendValue &= ~(1 << HALF);
			break;
	};
	
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
	};
	
	switch (dir_data)
	{
		case FORWARD:
			sendValue &= ~(1 << DRT);
			break;
			
		case REVERSE:
			sendValue |= (1 << DRT);
			break;
		
	};
}

uint8_t get_instruction_byte() {
	return sendValue;
}

void set_RTS_flag(bool flag_val) {
	RTS_flag = flag_val;
}


bool check_RTS_flag() {
	return RTS_flag;
}