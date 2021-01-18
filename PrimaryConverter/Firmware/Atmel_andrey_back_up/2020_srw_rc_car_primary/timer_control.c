/*
 * timer_control.c
 *
 * Created: 9/12/2020 1:24:24 pm
 *  Author: achu072
 */ 

#include <avr/io.h>

#include "timer0.h"
#include "timer1.h"
#include "timer2.h"
#include "timer3.h"
#include "calc.h"

#define OFFSET	34														//180deg out of phase (26 + 4 * 2)													

static volatile uint8_t current_duty_cycle = 0;							//initialise timers with 0% duty cycle
static volatile uint8_t period = 53; 

//synchronize timers
void timer_control_init()
{
	GTCCR |= ((1 << TSM) | (1 << PSRASY) | (1 << PSRSYNC));				//halt all timers
	
	timer0_init(period);												//configure timer0
	timer1_init();
	timer2_init(period);												//configure timer2
	timer3_init();
	
	GTCCR = 0;															//release all timers
	
	TCNT0 = 0;															//set value for timer0
	TCNT1 = 0;															//set value for timer1
	TCNT2 = OFFSET;														//set value for timer2
	TCNT3 = 0;															//set value for timer3
}

//set duty cycle on user TX via usart0
void timer_control_set_duty_on_user(uint8_t duty_cycle)
{												
	timer0_set_OCR0B(calc_make_OCRnB(period, duty_cycle));
	timer2_set_OCR2B(calc_make_OCRnB(period, duty_cycle));	
}

//get current duty cycle
uint8_t timer_control_get_duty()
{
	return current_duty_cycle;
}

//manually set duty cycle variable, will affect the PWM *ONLY* if used before timer_control_init()
void timer_control_update_current_duty(uint8_t value) 
{
	current_duty_cycle = value;
}