/*
 * pwm.c
 *
 * Created: 2/02/2021 4:45:29 AM
 *  Author: Manoj Kumaraguru
 */ 

#include <avr/io.h>
#include "pwm.h"

#define setPoint 15000

void pwmInit(){
	
	TCCR0A |= (1<<COM0A1); //Clear OC0A on C match, set at Bottom. -Non-inverting.
	TCCR0A |= (1<<WGM01) | (1<<WGM00); //Fast PWM mode.
	TCCR0B |= (1<<CS00); //No prescaling.
	DDRD |= (1<<PD6);
	OCR0A = 255*0.5; //Set duty cycle to 50% to begin with
	OCR0B = 255;
	
}


void setPWM(uint16_t piError) {
	OCR0A = piError/setPoint * 255;
}