/*
 * Steering_Controller.c
 *
 * Created: 11/01/2021 10:04:20 am
 * Author : npat692
 */ 

#include "global.h"
#include "adc.h"
#include "timer2.h"
#include "uart.h"
#include "control.h"
#include "led.h"
#include "instructions_macros.h"
#include "steering.h"
#include "pi_controller.h"
#include "pwm.h"

#include "uart.h" //
#include <stdio.h>//
#include <string.h>//
char input_buffer[20];//

int main(void)
{
	// Initialization 
	pin_init();
	led_init();
	uart_init();
	pwm0_init();
	pwm1_init(); 
	timer2_init();
	adc_init();	
	
	sprintf(input_buffer, "RESET");
	usart0_transmit_string(input_buffer);
	
	// For testing
	//set_point_angle = 1700;

	calibrate_steering(); 
	
	sei();
    while (1) {
		//****(Enabled for Proteus)

	}
}

