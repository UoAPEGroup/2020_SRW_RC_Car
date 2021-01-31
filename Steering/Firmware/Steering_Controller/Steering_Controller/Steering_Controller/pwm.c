/*
 * pwm.c
 *
 * Created: 29/01/2021 1:33:43 pm
 *  Author: npat692
 */ 

#include "pwm.h"

// IN1 PWM Initialization
void pwm0_init(){
	DDRD |= (1 << PORTD6); // Output PD6
	TCCR0A |= (1 << WGM01)|(1 << WGM00); // Fast PWM
	TCCR0B |= (1 << CS00); // 33kHz
	OCR0A = 0; // Sets Duty Cycle to 0%
	OCR0B = 255;
	IN_1_OFF; //  Toggle OC0A on compare match
}

// IN2 PWM Initialization
void pwm1_init(){
	DDRB |= (1 << PORTB1); // Output PB1
	TCCR1A |= (1 << WGM10);  // Fast PWM
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS10); // 33kHz
	OCR1A = 0; // Sets Duty Cycle to 0%
	OCR1B = 255;
	IN_2_OFF; //  Toggle OC0A on compare match
}


void set_duty_cycle(int16_t value){
	t_on =	(((uint32_t)value*255)/VREF); // Calculates duty cycle
	
	if (t_on > 255){ // Prevent overflow
		t_on = 255;
	}
	
	// Checks which PWM output is ON
	if(CHECK_IN_1){
		OCR0A = t_on;// Sets Duty Cycle
	} else if(CHECK_IN_2){
		OCR1A = t_on;
	}
}