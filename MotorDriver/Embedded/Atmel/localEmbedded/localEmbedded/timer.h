/*
 * timer.h
 *
 * Created: 9/12/2020 2:54:34 pm
 *  Author: Earlene
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include <stdbool.h>
#include <stdint.h>
#include <avr/interrupt.h>

timer0_init(uint8_t period, uint8_t duty_cycle);
timer1_init();
timer2_init(uint8_t period, uint8_t duty_cycle);


#endif /* TIMER_H_ */