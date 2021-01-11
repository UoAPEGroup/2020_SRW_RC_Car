/*
 * timer_control.h
 *
 * Created: 9/12/2020 1:24:39 pm
 *  Author: achu072
 */ 


#ifndef TIMER_CONTROL_H_
#define TIMER_CONTROL_H_

void timer_control_init();
void timer_control_set_duty_on_user(uint8_t duty_cycle);
uint8_t timer_control_get_duty();


#endif /* TIMER_CONTROL_H_ */