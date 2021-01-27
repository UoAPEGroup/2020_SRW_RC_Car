/*
 * timer_control.h
 *
 * Created: 9/12/2020 1:24:39 pm
 *  Author: Andrey Chukhraev
 */ 


#ifndef TIMER_CONTROL_H_
#define TIMER_CONTROL_H_

void timer_control_init();
void timer_control_halt();
void timer_control_set_duty_on_user(uint8_t duty_cycle);
void timer_control_update_current_duty(uint8_t value);
uint8_t timer_control_get_duty();


#endif /* TIMER_CONTROL_H_ */