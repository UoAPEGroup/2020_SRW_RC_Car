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

void timer0_init(uint8_t period, uint8_t duty_cycle);
void timer1_init();
void timer2_init(uint8_t period, uint8_t duty_cycle);
void timer3_init_1();


#endif /* TIMER_H_ */