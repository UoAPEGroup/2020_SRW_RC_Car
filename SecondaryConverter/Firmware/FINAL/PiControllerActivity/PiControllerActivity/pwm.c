/*
 * pwm.c
 *
 * Created: 2/02/2021 4:45:29 AM
 *  Author: Manoj Kumaraguru
 */ 

#include <avr/io.h>
#include "pwm.h"

#define SETPOINT 15000
#define VREF 3.3

void pwmInit(){
	
	TCCR0A |= (1<<COM0A1); //Clear OC0A on C match, set at Bottom. -Non-inverting.
	TCCR0A |= (1<<WGM01) | (1<<WGM00); //Fast PWM mode.
	TCCR0B |= (1<<CS02); // 256x prescaling.
	DDRD |= (1<<PORTD6);
	OCR0A = 0; //Set duty cycle to 0% to begin with
	OCR0B = 255;
	
}


void setPWM(uint16_t piError) {
	OCR0A = OCR0A/OCR0B * 255 + piError/100000; //Adjusts pwm based on error. Needs to be improved
}