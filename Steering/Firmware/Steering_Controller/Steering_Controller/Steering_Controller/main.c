/*
 * Steering_Controller.c
 *
 * Created: 11/01/2021 10:04:20 am
 * Author : Neil Patil 
 */ 

#include "global.h"
#include "adc.h"
#include "timer2.h"
#include "uart.h"
#include "control.h"
#include "instructions_macros.h"
#include "steering.h"
#include "pi_controller.h"
#include "pwm.h"

int main(void)
{
	// Initialization 
	
 	pin_init();
	uart_init();
	pwm0_init();
	pwm1_init(); 
	timer2_init();
	adc_init();	
	
	calibrate_steering(); 
	
	sei();
    while (1) {

	}
}

