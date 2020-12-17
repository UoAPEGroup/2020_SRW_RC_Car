/*
 * timer_control.c
 *
 * Created: 9/12/2020 1:24:24 pm
 *  Author: achu072
 */ 

#include <avr/io.h>
#include <stdint.h>

#include "timer0.h"
#include "timer1.h"
#include "timer2.h"

#define OFFSET				34											//180deg out of phase (26 + 4 * 2)													

static volatile uint8_t duty_cycle = 0;
static volatile uint8_t period = 53; 

//synchronize timers
void timer_control_init()
{
	GTCCR |= ((1 << TSM) | (1 << PSRASY) | (1 << PSRSYNC));				//halt all timers
	
	timer0_init(period, duty_cycle);									//configure timer0
	timer1_init();
	timer2_init(period, duty_cycle);									//configure timer2
	
	GTCCR = 0;															//release all timers
	
	TCNT0 = 0;															//set value for timer0
	TCNT1 = 0;															//set value for timer1
	TCNT2 = OFFSET;														//set value for timer2
}

//set duty cycle for PWM
void timer_control_set_duty(uint8_t duty_cycle_input)
{
	duty_cycle = duty_cycle_input;
}

//set duty cycle according to user input via usart0 (1->0/0%; 2->13/25%; 3->26/50%)
void timer_control_set_duty_on_user(uint8_t instruction)
{
	switch (instruction) {
		case 1:
			OCR0B = 0;
			OCR2B = 0;
			break;
		case 2:
			OCR0B = 13;
			OCR2B = 13;
			break;
		case 3:
			OCR0B = 26;
			OCR2B = 26;
			break;
	}
}