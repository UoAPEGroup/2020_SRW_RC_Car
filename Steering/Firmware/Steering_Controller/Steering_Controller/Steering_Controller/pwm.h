/*
 * pwm.h
 *
 * Created: 29/01/2021 1:33:30 pm
 *  Author: npat692
 */ 


#ifndef PWM_H_
#define PWM_H_

#include "global.h"

void pwm0_init();
void pwm1_init();
/*
void set_duty_cycle(int16_t value);*/

void set_duty_cycle_IN1(uint16_t value);
void set_duty_cycle_IN2(uint16_t value);
void calculate_t_on(uint16_t value);

#endif /* PWM_H_ */