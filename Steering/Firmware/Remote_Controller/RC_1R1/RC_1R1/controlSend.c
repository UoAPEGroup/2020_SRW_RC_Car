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
#include "uart.h"

// DEBUGGING
#include <stdio.h>//
#include <string.h>// For debugging
char input_buffer[20];//

#include "uart.h"

volatile uint8_t sendValue = 0b00000000;
volatile bool RTS_flag = false;

volatile uint8_t str_data = 0;
volatile uint8_t accel_data = 0;
volatile uint8_t dir_data = 0;

volatile bool accel_sw_1 = false;
volatile bool accel_sw_2 = false;
volatile bool accel_sw_3 = false;
volatile bool accel_sw_4 = false;

ISR(INT1_vect) {
	usart0_transmit_string("INT1 trigd\n");
	if (PIND & (1 << PD3)) {
		dir_data = REVERSE;
	}
	else {
		dir_data = FORWARD;
	}
}

ISR(INT0_vect) {
	//usart0_transmit_string("INT0 trigd\n");
}

ISR(PCINT0_vect) {
	if (READ_ACCEL_SW_1) {
		accel_sw_1 = true;
	}
	else {
		accel_sw_1 = false;
	}
	if (READ_ACCEL_SW_2) {
		accel_sw_2 = true;
	}
	else {
		accel_sw_2 = false;
	}
	if (READ_ACCEL_SW_3) {
		accel_sw_3 = true;
	}
	else {
		accel_sw_3 = false;
	}
	if (READ_ACCEL_SW_4) {
		accel_sw_4 = true;
	}
	else {
		accel_sw_4 = false;
	}
	
}

void str_data_conversion() {
	//uint32_t steering_adc_val = -1;
	uint32_t steering_adc_val = return_adc_val();
	//sprintf(input_buffer, "\n\r ADC:	%i \n\r", (int16_t)steering_adc_val);
	//usart0_transmit_string(input_buffer);
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
	if (accel_sw_1 && !accel_sw_2 && accel_sw_3 && accel_sw_4) {
		accel_data = ACCEL_NONE;
		//usart0_transmit_string("none");
	}
	else if (accel_sw_1 && !accel_sw_2 && accel_sw_3 && !accel_sw_4) {
		accel_data = ACCEL_LOW;
		//usart0_transmit_string("low");
	}
	else if (!accel_sw_1 && !accel_sw_2 && accel_sw_3 && !accel_sw_4) {
		accel_data = ACCEL_MEDIUM;
		//usart0_transmit_string("medium");
	}
	else if (accel_sw_1 && accel_sw_2 && !accel_sw_3 && !accel_sw_4) {
		accel_data = ACCEL_HIGH;
		//usart0_transmit_string("high");
	}
}

void instructionSend() {
	set_RTS_flag(false);
// 	sprintf(input_buffer, "\n\r ADC:	%i %i %i %i \n\r", (int16_t)accel_sw_1, (int16_t)accel_sw_2, (int16_t)accel_sw_3, (int16_t)accel_sw_4 );
// 	usart0_transmit_string(input_buffer);
	
	sendValue = 0b10000000;
	sendValue &=~ (1 << FUTURE);
	
	accel_data_conversion();

	switch (str_data)
	{
		case STR_FULL_L:
			sendValue &= ~(1 << TURN);
			sendValue |= (1 << FULL);
			//sendValue = 69; //E
			break;
		
		case STR_HALF_L:
			sendValue &= ~(1 << TURN);
			sendValue |= (1 << HALF);
			//sendValue = 70; //F
			break;
		
		case STR_FULL_R:
			sendValue |= (1 << TURN);
			sendValue |= (1 << FULL);
			//sendValue = 71; //G
			break;
		
		case STR_HALF_R:
			sendValue |= (1 << TURN);
			sendValue |= (1 << HALF);
			//sendValue = 72; //H
			break;
			
		case STR_STRGHT:
			sendValue &= ~(1 << TURN);
			sendValue &= ~(1 << FULL);
			sendValue &= ~(1 << HALF);
			//sendValue = 73; // I
			break;
	};
	
	switch (accel_data) 
	{
		case ACCEL_HIGH:
			//usart0_transmit_string("high");
			sendValue |= (1 << SPEED_HIGH); // CHANGE THESE!!!!!!!!!!
			//sendValue = 65;
			break;
		
		case ACCEL_MEDIUM:
			//usart0_transmit_string("medium");
			sendValue |= (1 << SPEED_MED);
			//sendValue = 66;
			break;
			
		case ACCEL_LOW:
			//usart0_transmit_string("low");
			sendValue |= (1 << SPEED_LOW);
			//sendValue = 67;
			break;
			
		case ACCEL_NONE:
			//usart0_transmit_string("none");
 			sendValue &= ~(1 << SPEED_HIGH);
 			sendValue &= ~(1 << SPEED_MED);
 			sendValue &= ~(1 << SPEED_LOW);
			//sendValue = 68;
			break;
	};
	
	switch (dir_data)
	{
		case FORWARD:
			sendValue &= ~(1 << DRT);
			//usart0_transmit_string("Fwd\n");
			break;
			
		case REVERSE:
			sendValue |= (1 << DRT);
			//usart0_transmit_string("Rev\n");
			break;
		
	};
	set_RTS_flag(true);
	
}

void get_instruction_byte() {
	if (check_RTS_flag()){
		usart0_transmit_byte(sendValue);
	}
}

void set_RTS_flag(bool flag_val) {
	RTS_flag = flag_val;
}


bool check_RTS_flag() {
	return RTS_flag;
}