/*
 * pwm.c
 *
 * Created: 29/01/2021 1:33:43 pm
 *  Author: npat692
 */ 

#include "pwm.h"


#include <stdio.h>//
#include <string.h>// For debugging
char input_buffer[20];//

#include "uart.h"

// IN1 PWM Initialization (33kHz)
void pwm0_init(){
	DDRD |= (1 << PORTD6); // Output PD6
	TCCR0A |= (1 << WGM01)|(1 << WGM00); // Fast PWM
	TCCR0B |= (1 << CS00); // ~33kHz
	OCR0A = 0; // Sets Duty Cycle to 0%
	OCR0B = 255;
	IN_1_OFF; //  Toggle OC0A on compare match
	//IN_1_ON;
}

// IN2 PWM Initialization (33kHz)
void pwm1_init(){
	DDRB |= (1 << PORTB1); // Output PB1
	TCCR1A |= (1 << WGM10);  // Fast PWM
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS10); // ~33kHz
	OCR1A = 0; // Sets Duty Cycle to 0%
	OCR1B = 255;
	IN_2_OFF;
	//IN_2_ON; //  Toggle OC0A on compare match
}


void set_duty_cycle(int16_t value){
	//t_on =	(((uint32_t)value*255)/VREF); // Calculates duty cycle
	
	//if (t_on > 255){ // Prevent overflow
	//	t_on = 255;
	//}
	t_on = 255;
	// Checks which PWM output is ON
	if(CHECK_IN_1){
		OCR0A = t_on;// Sets Duty Cycle
		OCR1A = 0;
	} else if(CHECK_IN_2){
		OCR0A = 0;
		OCR1A = t_on;
	}
}


// Turns OFF IN2 and turns ON IN1 (Goes LEFT)
// Then sets the duty cycle
void set_duty_cycle_IN1(uint16_t value){
 	IN_2_OFF; // Turns OFF IN2
 	
 	//calculate_t_on(value); // Calculates the required duty cycle
 	
	 //sprintf(input_buffer, "Set Output IN1:	%i \n\r", t_on);
	 //usart0_transmit_string(input_buffer);

 	OCR0A = 200; // Sets Duty Cycle
 	OCR1A = 0;
 	
 	IN_1_ON; // Turns ON IN1
}
 
 
// Turns OFF IN1 and turns ON IN2 (Goes RIGHT)
// Then sets the duty cycle
 void set_duty_cycle_IN2(uint16_t value){
 	IN_1_OFF;
 	
 	calculate_t_on(value);
 	
	//sprintf(input_buffer, "Set Output IN2:	%i \n\r", t_on);
	//usart0_transmit_string(input_buffer);
	 
	OCR1A = 200; // Sets Duty Cycle
 	OCR0A = 0;
 	
 	IN_2_ON;
 }
 
 // Calculates the duty cycle 
 void calculate_t_on(uint16_t value){
 	t_on =	(((uint32_t)value*255)/VREF); // Calculates duty cycle
 	
 	if (t_on > 255){ // Prevent overflow
 		t_on = 255;
 	}
 }
