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

// Triggers when data is received
ISR(USART0_RX_vect){
	reset_timeout(); // Resets timeout counter
	input_data = UDR0; // Stores received data in variable
	tx_debug(); // Echoes back input data
	read_data(); // Reads data
}

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
	
	// Sets up PI Controller K values
	pi_setup();
	
	// Reads and sets up voltage reference values used for steering (Disabled for Proteus)
	//calibrate_steering(); 
	
	//****(Enabled for Proteus)
	//min_val = MAX_LIMIT;
	//max_val = MIN_LIMIT;
	
	sei();
    while (1) {
		//****(Enabled for Proteus)

	}
}

