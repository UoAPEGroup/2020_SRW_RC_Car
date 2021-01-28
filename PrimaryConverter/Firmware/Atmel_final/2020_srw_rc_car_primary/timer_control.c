/*
 * timer_control.c
 *
 * Created: 9/12/2020 1:24:24 pm
 *  Author: Andrey Chukhraev
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer0.h"
#include "timer1.h"
#include "timer2.h"
#include "timer3.h"
#include "timer4.h"
#include "calc.h"
#include "adc.h"

#define OFFSET	34														//180deg out of phase (26 + 4 * 2)													

#define RAMP_TIME_STEP	5												//5ms duty cycle ramp time step
#define RAMP_LIMIT		5
#define DUTY_STEP		5
#define BABY_STEP		1

static volatile uint8_t timer4_duty_cycle_ramp_counter = 0;
static volatile uint8_t current_duty_cycle = 0;							//initialise timers with 0% duty cycle
static volatile uint8_t next_duty_cycle = 0;							
static volatile uint8_t period = 53;
 
//duty cycle ramp control
ISR(TIMER4_COMPB_vect)
{
	timer4_duty_cycle_ramp_counter++;
	
	if (timer4_duty_cycle_ramp_counter == RAMP_TIME_STEP) {
		timer4_duty_cycle_ramp_counter = 0;
		
		if (next_duty_cycle > current_duty_cycle) {
			if ((next_duty_cycle - current_duty_cycle) > RAMP_LIMIT) {
				timer_control_set_duty_on_user(current_duty_cycle + DUTY_STEP);
				} else {
				timer_control_set_duty_on_user(current_duty_cycle + BABY_STEP);
			}
			} else if (current_duty_cycle > next_duty_cycle) {
			if ((current_duty_cycle - next_duty_cycle) > RAMP_LIMIT) {
				timer_control_set_duty_on_user(current_duty_cycle - DUTY_STEP);
				} else {
				timer_control_set_duty_on_user(current_duty_cycle - BABY_STEP);
			}
		}
	}
}

//synchronize timers
void timer_control_init()
{
	GTCCR |= ((1 << TSM) | (1 << PSRASY) | (1 << PSRSYNC));				//halt all timers
	
	timer0_init(period);												//configure timer0
	timer1_init();
	timer2_init(period);												//configure timer2
	timer3_init();
	timer4_init();
	
	GTCCR = 0;															//release all timers
	
	TCNT0 = 0;															//set value for timer0
	TCNT1 = 0;															//set value for timer1
	TCNT2 = OFFSET;														//set value for timer2
	TCNT3 = 0;															//set value for timer3
	TCNT4 = 0;
	
	//clear all adc overflow flags
	clr_overV_flag();
	clr_overC_flag();
	clr_overT1_flag();
	clr_overT2_flag();
	clr_overT3_flag();
	
	timer_control_update_current_duty(0);
}

//halt PWM timers
void timer_control_halt()
{
	GTCCR |= ((1 << TSM) | (1 << PSRASY) | (1 << PSRSYNC));				//halt all timers
}

//set duty cycle on user TX via usart0
void timer_control_set_duty_on_user(uint8_t duty_cycle)
{												
	timer0_set_OCR0B(calc_make_OCRnB(period, duty_cycle));
	timer2_set_OCR2B(calc_make_OCRnB(period, duty_cycle));	
	
	timer_control_update_current_duty(duty_cycle);
}

//get current duty cycle
uint8_t timer_control_get_current_duty()
{
	return current_duty_cycle;
}

//get next duty cycle
uint8_t timer_control_get_next_duty()
{
	return next_duty_cycle;
}

//update current duty cycle variable
void timer_control_update_current_duty(uint8_t value) 
{
	current_duty_cycle = value;
}

//update next duty cycle variable
void timer_control_update_next_duty(uint8_t value)
{
	next_duty_cycle = value;
}